#include "Skiplist.h"

int main()
{
	Skiplist skiplist;
	skiplist.add(1);
	skiplist.add(2);
	skiplist.add(3);
	cout << skiplist.search(0) << endl; // ���� false
	skiplist.add(4);
	cout << skiplist.search(1) << endl; // ���� true 
	cout << skiplist.erase(0) << endl; // ���� false��0 ����������
	cout << skiplist.erase(1) << endl; // ���� true  
	cout << skiplist.search(1) << endl; // ���� false��1 �ѱ�����
}