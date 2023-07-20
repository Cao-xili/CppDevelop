#pragma once
#include <iostream>
#include <vector>
using namespace std;


class Node
{
public:
	int val;
	vector<Node*> next;
	
	Node(int _val, int size) :val(_val), next(vector<Node*>(size,nullptr)){}
};

class Skiplist
{
public:

	Skiplist()
	{
		head = new Node(-1,Maxlevel);
	}

	~Skiplist()
	{
		delete head;
	}
	
	void find(int target, vector<Node*>& node)	//找到每一层中雄安与target的最大节点
	{
		auto p = head;
		for (int i = Maxlevel - 1; i >= 0; i--)
		{
			while (p->next[i] && p->next[i]->val < target)
			{
				p = p->next[i];
			}
			node[i] = p;
		}
	}

	bool search(int target)
	{
		vector<Node*> tempnode(Maxlevel);
		find(target, tempnode);		//先找到每一层小于target的最大节点

		auto p = tempnode[0]->next[0];	//底层是最全的，只需要看底层有没有
		return p && p->val == target;
	}

	void add(int target)
	{
		vector<Node*> tempnode(Maxlevel);
		find(target, tempnode);

		auto p = new Node(target, Maxlevel);	//创建要插入的新节点
		for (int i = 0; i < Maxlevel; i++)
		{
			p->next[i] = tempnode[i]->next[i];
			tempnode[i]->next[i] = p;
			if (rand() % 2)	//每一层有50%的几率不插入新节点
			{
				break;
			}
		}
	}

	bool erase(int target)
	{
		vector<Node*> tempnode(Maxlevel);
		find(target, tempnode);

		auto p = tempnode[0]->next[0];
		if (!p || p->val != target)	//判断target是否存在，不存在直接返回false
		{
			return false;
		}

		for (int i = 0; i < Maxlevel && tempnode[i]->next[i] == p; i++) //删除每一层的target，如果tempnode[i]->next[i] == p，说明第i层有target
		{
			tempnode[i]->next[i] = p->next[i];
		}

		delete p;

		return true;
	}
private:
	const static int Maxlevel = 8; //层数定义成8层
	Node* head;	//头节点
};