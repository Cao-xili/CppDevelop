#include "Skiplist.h"

int main()
{
	Skiplist skiplist;
	skiplist.add(1);
	skiplist.add(2);
	skiplist.add(3);
	cout << skiplist.search(0) << endl; // 返回 false
	skiplist.add(4);
	cout << skiplist.search(1) << endl; // 返回 true 
	cout << skiplist.erase(0) << endl; // 返回 false，0 不在跳表中
	cout << skiplist.erase(1) << endl; // 返回 true  
	cout << skiplist.search(1) << endl; // 返回 false，1 已被擦除
}