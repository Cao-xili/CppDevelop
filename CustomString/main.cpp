#include "CustomString.h"

int main()
{
	auto str1 = CustomString("test1");
	auto str2 = CustomString("test2,test3");
	std::cout << str1;
	std::cout << str2;

	str1 = "test3";
	std::cout << str1;

	int len = str1.len();
	std::cout << len << std::endl;

	CustomString sub1 = str1.sub(1, 2);
	std::cout << sub1;

	str1.append("append");
	std::cout << str1;

	bool equal = str1 == str2;
	std::cout << equal << std::endl;

	int index = str1.find("es");
	std::cout << index << std::endl;

	CustomString* ret =	str2.split(",");
	std::cout << "split1:" << ret[0] << "split2:" << ret[1];
}