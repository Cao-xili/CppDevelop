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
	
	void find(int target, vector<Node*>& node)	//�ҵ�ÿһ�����۰���target�����ڵ�
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
		find(target, tempnode);		//���ҵ�ÿһ��С��target�����ڵ�

		auto p = tempnode[0]->next[0];	//�ײ�����ȫ�ģ�ֻ��Ҫ���ײ���û��
		return p && p->val == target;
	}

	void add(int target)
	{
		vector<Node*> tempnode(Maxlevel);
		find(target, tempnode);

		auto p = new Node(target, Maxlevel);	//����Ҫ������½ڵ�
		for (int i = 0; i < Maxlevel; i++)
		{
			p->next[i] = tempnode[i]->next[i];
			tempnode[i]->next[i] = p;
			if (rand() % 2)	//ÿһ����50%�ļ��ʲ������½ڵ�
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
		if (!p || p->val != target)	//�ж�target�Ƿ���ڣ�������ֱ�ӷ���false
		{
			return false;
		}

		for (int i = 0; i < Maxlevel && tempnode[i]->next[i] == p; i++) //ɾ��ÿһ���target�����tempnode[i]->next[i] == p��˵����i����target
		{
			tempnode[i]->next[i] = p->next[i];
		}

		delete p;

		return true;
	}
private:
	const static int Maxlevel = 8; //���������8��
	Node* head;	//ͷ�ڵ�
};