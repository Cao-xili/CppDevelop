#include"CustomArray.h"


int main()
{
	auto arr = new CustomArray();

	arr->reserve(4);

	arr->push(1);
	arr->print();

	arr->push(2);
	arr->print();

	arr->insert(1, 3);
	arr->print();

	arr->remove(1);
	arr->print();

	arr->pop();
	arr->print();

	int index = arr->findindex(1);
	std::cout << index << std::endl;
	
	arr->clear();
	arr->print();

}