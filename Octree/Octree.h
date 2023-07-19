#include <cstddef>
#include <vector>

class Vec3
{
public:
	float x, y, z;
	Vec3(){}
	Vec3(float a,float b, float c) : x(a), y(b), z(c){}

	float& operator[](unsigned int i){
		// Assuming 'i' can only be 0, 1 or 2.
		return i == 0 ? x : (i == 1 ? y : z);
	}

	const float& operator[](unsigned int i) const {
		// Assuming 'i' can only be 0, 1 or 2.
		return i == 0 ? x : (i == 1 ? y : z);
	}

	Vec3 operator+(const Vec3& r)
	{
		return Vec3(x + r.x, y + r.y, z + r.z);
	}

	Vec3 operator-(const Vec3& r) const 
	{
		return Vec3(x - r.x, y - r.y, z - r.z);
	}

	Vec3 operator*(float r) const 
	{
		return Vec3(x * r, y * r, z * r);
	}
};

class OctreePoints
{
public:
	OctreePoints(){}
	OctreePoints(const Vec3& _position): position(_position){}
	inline const Vec3& getposition() const
	{
		return position;
	}

	inline void setPosition(const Vec3& p) 
	{
		position = p; 
	}
private:
	Vec3 position;
};

class Octree
{
public:
	Octree(const Vec3& _origin,const Vec3& _halfdimension) : origin(_origin), halfdimension(_halfdimension),data(nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			ocp[i] = nullptr;
		}
	}

	Octree(const Octree& _octree) :origin(_octree.origin), halfdimension(_octree.halfdimension), data(_octree.data){}

	~Octree()
	{
		for (int i = 0; i < 8; i++)
		{
			delete ocp[i];
		}
	}

	//判断当前点在八叉树的哪个分区
	int getOctantContainingPoint(const Vec3& point) const {
		int oct = 0;
		if (point.x >= origin.x)
		{
			oct |= 4;	//如果point.x>=origin.x,那么就将oct的二进制表示的第三位设置为1，下面以此类推
		}
		if (point.y >= origin.y)
		{
			oct |= 2;
		}
		if (point.z >= origin.z)
		{
			oct |= 1;
		}
		return oct;	//oct的范围是0到7，对应八个区域
	}

	bool isLeafNode() const {
		// 判断该节点是否是叶子节点（没有子节点的节点）
		return ocp[0] == nullptr;
	}

	void insert(OctreePoints* point)
	{
		if (isLeafNode())
		{
			//当前叶子节点没有数据，把新的点存储在这个叶子节点上，并结束插入操作
			if (data == nullptr)
			{
				data = point;
				return;
			}
			//已有数据，将当前节点分裂成8个子节点，将新的点存储在叶子节点上
			else
			{
				OctreePoints* oldPoint = data;
				data = nullptr;

				for (int i = 0; i < 8; i++)
				{
					Vec3 newOrigin = origin;
					newOrigin.x += halfdimension.x * (i & 4 ? .5f : -.5f);
					newOrigin.y += halfdimension.y * (i & 2 ? .5f : -.5f);
					newOrigin.z += halfdimension.z * (i & 1 ? .5f : -.5f);
					ocp[i] = new Octree(newOrigin, halfdimension * .5f);
				}
				ocp[getOctantContainingPoint(oldPoint->getposition())]->insert(oldPoint);
				ocp[getOctantContainingPoint(point->getposition())]->insert(point);
			}
		}
		//不是叶子节点，那么找到新的点属于哪个八分区，然后递归地在对应的子节点中插入
		else
		{
			int octant = getOctantContainingPoint(point->getposition());
			ocp[octant]->insert(point);
		}
	}

	void getPointInsideBox(const Vec3& bmin, const Vec3& bmax, std::vector<OctreePoints*>& results)
	{
		if (isLeafNode()) 
		{
			//检查当前数据点是否在查询的边界中，如果在就添加到reslut中
			if (data != nullptr)
			{
				const Vec3& p = data->getposition();
				if (p.x > bmax.x || p.y > bmax.y || p.z > bmax.z) return;
				if (p.x < bmin.x || p.y < bmin.y || p.z < bmin.z) return;
				results.push_back(data);
			}
		}
		//检查查询的边界框是否在此节点的八个子节点之外。对每个子节点，我们都会计算它的最小和最大角落（通过原点和半尺寸），并检查查询的边界框是否在子节点的边界盒之外。如果边界框在子节点之外，我们可以跳过这个子节点，继续检查下一个。但是，如果查询的边界框和子节点的边界盒有交集，我们就需要在这个子节点上递归调用 getPointsInsideBox 函数。
		else 
		{
			for (int i = 0; i < 8; ++i) 
			{
				Vec3 cmax = ocp[i]->origin + ocp[i]->halfdimension;
				Vec3 cmin = ocp[i]->origin - ocp[i]->halfdimension;

				if (cmax.x < bmin.x || cmax.y < bmin.y || cmax.z < bmin.z) continue;
				if (cmin.x > bmax.x || cmin.y > bmax.y || cmin.z > bmax.z) continue;

				ocp[i]->getPointInsideBox(bmin, bmax, results);
			}
		}
	}

private:
	Vec3 origin;
	Vec3 halfdimension;
	Octree* ocp[8];
	OctreePoints* data;
};