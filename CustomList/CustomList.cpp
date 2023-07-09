#include "CustomList.h"

CustomNode::CustomNode() :prev(nullptr),next(nullptr),data(0)
{

}

CustomNode::CustomNode(int item)
{
	data = item;
	prev = nullptr;
	next = nullptr;
}

CustomList::CustomList():head(nullptr)
{

}

CustomList::~CustomList()
{
	CustomNode* temp = head;
	while(head)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}

CustomNode* CustomList::push(int item)
{
	CustomNode* node = new CustomNode(item);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	return tail;
}

CustomNode* CustomList::insert(CustomNode* node, int item)
{
	CustomNode* newnode = new CustomNode(item);

	CustomNode* temp = new CustomNode();

	newnode->next = node->next;
	newnode->prev = node;
	node->next = newnode;

	return newnode;
}

CustomNode* CustomList::find(int item)
{
	CustomNode* temp = new CustomNode();
	temp = head;
	while (temp!=NULL)
	{
		if (temp->data == item)
		{
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

void CustomList::remove(CustomNode* node) 
{
	if (node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else 
	{
		tail = node->prev;
		node->prev->next = nullptr;
	}
}

void CustomList::popAll()
{
	CustomNode* temp = new CustomNode();
	temp = head;
	while (head)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}

void CustomList::print()
{
	CustomNode* temp = new CustomNode();
	temp = head;
	while (temp)
	{
		std::cout << temp->data << ' ';
		temp = temp->next;
	}
	std::cout << std::endl;
}