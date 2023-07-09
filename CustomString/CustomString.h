#pragma once
#include <iostream>

class CustomString
{
public:
	CustomString();

	CustomString(const char* str);

	CustomString(const CustomString& str);

	~CustomString();

	CustomString& operator=(const CustomString& str);

	int	len();

	CustomString sub(int pos, int len);

	CustomString append(const char* str);

	bool operator==(const CustomString& str);

	int find(const char* str);

	CustomString* split(const char* str);

	friend std::ostream& operator<<(std::ostream& os,const CustomString& str);

private:
	char* m_str;
	int m_len;

};