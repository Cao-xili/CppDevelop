#include"iostream"
#pragma once

class CustomNode
{
public:

	CustomNode();
	CustomNode(int item);


	CustomNode* prev;
	CustomNode* next;
	int data;
};

class CustomList
{
public:
	CustomList();

	~CustomList();

	 CustomNode* push(int item);

	 CustomNode* insert(CustomNode* node, int item);

	 CustomNode* find(int item);

	 void remove(CustomNode* node);

	 void popAll();

	 void print();

private:
	CustomNode* head;
	CustomNode* tail;
};