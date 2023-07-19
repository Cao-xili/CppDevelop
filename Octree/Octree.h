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

	//�жϵ�ǰ���ڰ˲������ĸ�����
	int getOctantContainingPoint(const Vec3& point) const {
		int oct = 0;
		if (point.x >= origin.x)
		{
			oct |= 4;	//���point.x>=origin.x,��ô�ͽ�oct�Ķ����Ʊ�ʾ�ĵ���λ����Ϊ1�������Դ�����
		}
		if (point.y >= origin.y)
		{
			oct |= 2;
		}
		if (point.z >= origin.z)
		{
			oct |= 1;
		}
		return oct;	//oct�ķ�Χ��0��7����Ӧ�˸�����
	}

	bool isLeafNode() const {
		// �жϸýڵ��Ƿ���Ҷ�ӽڵ㣨û���ӽڵ�Ľڵ㣩
		return ocp[0] == nullptr;
	}

	void insert(OctreePoints* point)
	{
		if (isLeafNode())
		{
			//��ǰҶ�ӽڵ�û�����ݣ����µĵ�洢�����Ҷ�ӽڵ��ϣ��������������
			if (data == nullptr)
			{
				data = point;
				return;
			}
			//�������ݣ�����ǰ�ڵ���ѳ�8���ӽڵ㣬���µĵ�洢��Ҷ�ӽڵ���
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
		//����Ҷ�ӽڵ㣬��ô�ҵ��µĵ������ĸ��˷�����Ȼ��ݹ���ڶ�Ӧ���ӽڵ��в���
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
			//��鵱ǰ���ݵ��Ƿ��ڲ�ѯ�ı߽��У�����ھ���ӵ�reslut��
			if (data != nullptr)
			{
				const Vec3& p = data->getposition();
				if (p.x > bmax.x || p.y > bmax.y || p.z > bmax.z) return;
				if (p.x < bmin.x || p.y < bmin.y || p.z < bmin.z) return;
				results.push_back(data);
			}
		}
		//����ѯ�ı߽���Ƿ��ڴ˽ڵ�İ˸��ӽڵ�֮�⡣��ÿ���ӽڵ㣬���Ƕ������������С�������䣨ͨ��ԭ��Ͱ�ߴ磩��������ѯ�ı߽���Ƿ����ӽڵ�ı߽��֮�⡣����߽�����ӽڵ�֮�⣬���ǿ�����������ӽڵ㣬���������һ�������ǣ������ѯ�ı߽����ӽڵ�ı߽���н��������Ǿ���Ҫ������ӽڵ��ϵݹ���� getPointsInsideBox ������
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