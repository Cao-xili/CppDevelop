#include"iostream"
#pragma once

class CustomArray
{
public:
	CustomArray();

	~CustomArray();

	void reserve(int size);

	void push(int item);

	void insert(int index,int item);

	void remove(int index);
	
	void pop();

	void clear();

	int findindex(int item);

	void print();

private:
	int m_size;
	int m_capacity;
	int* m_p;

};