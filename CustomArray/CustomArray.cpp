#include "CustomArray.h"


CustomArray::CustomArray() :m_p(nullptr), m_size(0), m_capacity(0)
{

}

CustomArray::~CustomArray()
{
	delete[] m_p;
}


void CustomArray::reserve(int capacity)
{
	if (capacity > m_capacity)
	{
		int* temp = new int[capacity];
		for (int i = 0; i < m_size; i++)
		{
			temp[i] = m_p[i];
		}
		delete[] m_p;
		m_p = temp;
		m_capacity = capacity;
	}
}

void CustomArray::push(int item)
{
	if (m_size == m_capacity)
	{
		reserve(2 * m_capacity);
	}
	int* p = m_p + m_size;
	*p = item;
	m_size++;
}

void CustomArray::insert(int index, int item)
{
	if (index == m_size)
	{
		push(item);
	}
	else if (index < m_size)
	{
		if (m_size == m_capacity)
		{
			reserve(2 * m_capacity);
		}
		int* p = m_p + m_size;
		for (int i = this->m_size; i > index; i--)
		{
			*p = *(p - 1);
			p--;
		}
		*p = item;
		m_size++;
	}
}

void CustomArray::remove(int index)
{
	if (index < m_size)
	{
		int* p = m_p + index;
		for (int i = index; i < m_size-1; i++)
		{
			*p = *(p + 1);
			p++;
		}
		*p = NULL;
		m_size--;
	}
}

void CustomArray::pop() 
{
	if (m_size > 0)
	{
		remove(m_size - 1);
	}
}

void CustomArray::clear()
{
	delete[] m_p;
	m_size = 0;
}

int CustomArray::findindex(int item) 
{
	int* p = m_p;
	for (int i = 0; i < m_size; i++)
	{
		if (*p == item)
		{
			return i;
		}
		p++;
	}
	return -1;
}

void CustomArray::print()
{
	for (int i = 0; i < m_size; i++)
	{
		std::cout << *(m_p + i) << ' ';
	}
	std::cout << std::endl;
}