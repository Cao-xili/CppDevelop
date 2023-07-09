#include "CustomString.h"
#include <vector>

CustomString::CustomString()
{
}

CustomString::CustomString(const char* str)
{
	const char* temp = str;

	while (*temp++ != '\0')
	{
		this->m_len++;
	}

	this->m_str = new char[this->m_len+1];

	for (int i = 0; i < this->m_len+1; i++)
	{
		this->m_str[i] = str[i];
	}
}

CustomString::CustomString(const CustomString& cstr)
{
	this->m_str = new char[cstr.m_len + 1];
	this->m_len = cstr.m_len;
	for (int i = 0; i < this->m_len+1; i++)
	{
		this->m_str[i] = cstr.m_str[i];
	}
}

CustomString::~CustomString()
{
	delete[] m_str;
}


CustomString& CustomString::operator=(const CustomString& cstr)
{
	this->m_len = cstr.m_len;
	this->m_str = new char[this->m_len + 1];
	for (int i = 0; i < this->m_len + 1; i++)
	{
		this->m_str[i] = cstr.m_str[i];
	}
	return *this;
}


int	CustomString::len()
{
	return this->m_len;
}

CustomString CustomString::sub(int pos, int len)
{
	CustomString temp;
	temp.m_len = len;
	temp.m_str = new char[temp.m_len+1];
	for (int i=pos; i<pos+len; i++)
	{
		temp.m_str[i - pos] = this->m_str[i];
	}
	temp.m_str[temp.m_len] = '\0';
	return temp;
}

CustomString CustomString::append(const char* str)
{
	CustomString result;
	const char* temp = str;
	int temp_len = 0;
	while (*temp++ != '\0')
	{
		temp_len++;
	}
	result.m_len = temp_len + this->m_len;
	result.m_str = new char[result.m_len+1];
	for (int i = 0; i<this->m_len; i++)
	{
		result.m_str[i] = this->m_str[i];
	}
	for (int i = 0; i < temp_len; i++)
	{
		result.m_str[i + this->m_len] = str[i];
	}
	*this = result;
	this->m_str[this->m_len] = '\0';

	return *this;
}

bool CustomString::operator==(const CustomString& str)
{
	if (this->m_len != str.m_len)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->m_len; i++)
		{
			if (this->m_str[i] != str.m_str[i])
			{
				return false;
			}
		}
	}
	return true;
}

int CustomString::find(const char* str)
{

	int str_len = 0;
	while (str[str_len] != '\0')
	{
		str_len++;
	}

	if (this->m_len < str_len)
		return -1;

	for (int i = 0; i < this->m_len - str_len+1; i++)
	{
		int j;
		for (j = 0; j < str_len; j++)
		{
			if (this->m_str[i + j] != str[j])
				break;
		}
		if (j == str_len)
			return i;
	}

	return -1;

}

CustomString* CustomString::split(const char* str)
{
	CustomString Splitstr = *this;
	std::vector<CustomString> cstrvec;
	while(Splitstr.find(str) != -1)
	{
		int index = Splitstr.find(str);
		int split_len = Splitstr.m_len - index;
		cstrvec.push_back(Splitstr.sub(0, index));
		Splitstr = Splitstr.sub(index+1, split_len);
	}
	cstrvec.push_back(Splitstr);

	int size = cstrvec.size();

	CustomString *Split_str = new CustomString[size];


	for (int i = 0; i < size; i++)
	{
		Split_str[i] = cstrvec[i];
	}

	return Split_str;
}


std::ostream& operator<<(std::ostream& os, const CustomString& str)
{
	for (int i = 0; i < str.m_len; i++)
	{
		os << str.m_str[i];
	}
	os << std::endl;
	return os;
}