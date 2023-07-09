#include "CustomList.h"

int main()
{
	auto list1 = new CustomList();
	
	auto node1 = list1->push(1);
	list1->print();

	auto node2 = list1->push(2);
	list1->print();

	auto node3 = list1->insert(node2, 3);
	list1->print();

	auto ret = list1->find(2);

	list1->remove(node2);
	list1->print();

	list1->popAll();
	list1->print();
}