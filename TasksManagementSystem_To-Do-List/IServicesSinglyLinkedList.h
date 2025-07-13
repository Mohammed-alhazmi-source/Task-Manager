#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class IServicesSinglyLinkedList
{
public:
	bool virtual IsEmpty() const = 0;
	void virtual InsertFirst(T Item) = 0;
	void virtual InsertLast(T Item) = 0;
	void virtual InsertBefore(T Item, T Index) = 0;
	void virtual InsertAfter(T Item, T Index) = 0;
	void virtual DeleteFirst() = 0;
	void virtual DeleteLast() = 0;
	void virtual DeleteNode(T Item) = 0;
	void virtual Update(T Item, T NewItem) = 0;
	void virtual Pop() = 0;
	void virtual Clear() = 0;
	bool virtual IsFound(T Item) const = 0;
	int virtual Count() const = 0;
	T virtual FirstData() const = 0;
	T virtual LastData() const = 0;
	virtual Node<T>* FirstNode() const = 0;
	virtual Node<T>* LastNode()  const = 0;

	~IServicesSinglyLinkedList() {};
};