#pragma once
#include <iostream>
#include "Node.h"
#include "IServicesSinglyLinkedList.h"
#include "clsTask.h"
using namespace std;

template <typename T>
class SinglyLinkedList : public IServicesSinglyLinkedList<T>
{
private:
	Node<T>* Head;
	Node<T>* Tail;

	void _DeleteLinkedNode()
	{
		if (IsEmpty())
		{
			cout << "Singly Linked List Is Empty\n";
			return;
		}

		else if (Head->Next == nullptr && Tail->Next == nullptr)
		{
			delete Head;
			Head = Tail = nullptr;
		}

		else
		{
			if (Head == Tail)
			{
				delete Head;
				Head = Tail = nullptr;
			}
			else
			{
				Node<T>* Temp = Head;
				Head = Head->Next;
				delete Temp;
				Temp = nullptr;
			}
		}
	}
	void _ExecuteInsertAfter(T& NewItem, T& OldItem)
	{
		Node<T>* newNode = new Node<T>();
		newNode->Data = NewItem;
		Node<T>* Temp = Head;

		while (Temp != nullptr)
		{
			if (Temp->Next == nullptr)
			{
				Tail->Next = newNode;
				Tail = newNode;
				break;
			}
			else if (Temp->Data == OldItem)
			{
				newNode->Next = Temp->Next;
				Temp->Next = newNode;
				break;
			}
			Temp = Temp->Next;
		}
	}
	void _ExecuteInsertBefore(Node<T>*& Temp, T& NewItem, T& OldItem)
	{
		Node<T>* newNode = new Node<T>();
		newNode->Data = NewItem;
		while (Temp->Next->Data != OldItem)
		{
			Temp = Temp->Next;
		}


		newNode->Next = Temp->Next;
		Temp->Next = newNode;
	}
	bool _NotReferenceEquals(SinglyLinkedList<T>& Other)
	{
		if (this != &Other)
		{
			if (!this->IsEmpty())
			{
				this->Clear();
			}
			return true;
		}
		return false;
	}
public:
	SinglyLinkedList() : Head(nullptr), Tail(nullptr) {}	

	SinglyLinkedList(SinglyLinkedList<T>& Other) : Head(nullptr), Tail(nullptr)
	{
		Node<T>* Temp = Other.FirstNode();
		while (Temp != nullptr)
		{
			this->InsertLast(Temp->Data);
			Temp = Temp->Next;
		}
	}

	SinglyLinkedList& operator=(SinglyLinkedList<T>& Other)
	{
		if (this->_NotReferenceEquals(Other))
		{
			Node<T>* Temp = Other.FirstNode();
			while (Temp != nullptr)
			{
				this->InsertLast(Temp->Data);
				Temp = Temp->Next;
			}			
		}
		return *this;
	}

	Node<T>* FirstNode()const override { return Head; }

	Node<T>* LastNode() const override { return Tail; }

	bool IsEmpty() const override { return (Head == nullptr && Tail == nullptr); }

	void InsertFirst(T Item) override
	{
		Node<T>* NewNode = new Node<T>();
		NewNode->Data = Item;

		if (IsEmpty())
			Head = Tail = NewNode;

		else
		{
			NewNode->Next = Head;
			Head = NewNode;
		}
	}

	void InsertLast(T Item) override
	{
		Node<T>* NewNode = new Node<T>();
		NewNode->Data = Item;

		if (IsEmpty())
			Head = Tail = NewNode;

		else
		{
			Tail->Next = NewNode;
			Tail = NewNode;
		}
	}

	void InsertAfter(T NewItem, T OldItem) override
	{
		if (IsFound(OldItem))
		{
			if (IsEmpty())
				InsertFirst(NewItem);

			else if (Head->Next == nullptr && Tail->Next == nullptr)
				InsertLast(NewItem);

			else
				_ExecuteInsertAfter(NewItem, OldItem);
		}

		//else
		//	cout << "Old Item " << OldItem << " Not Found...\n";
	}

	void InsertBefore(T NewItem, T OldItem) override
	{
		if (IsFound(OldItem))
		{
			if (IsEmpty())
				InsertFirst(NewItem);

			else if (Head->Next == nullptr)
				InsertFirst(NewItem);

			else
			{
				Node<T>* Temp = Head;

				if (Head == Temp && Temp->Data == OldItem)
					InsertFirst(NewItem);

				else
					_ExecuteInsertBefore(Temp, NewItem, OldItem);
			}
		}
		//else
		//	cout << "Old Item " << OldItem << " Not Found...\n";
	}

	void DeleteFirst() override
	{
		Pop();
	}

	void DeleteLast() override
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		else
		{
			Node<T>* Temp = Head;
			Node<T>* DeletePointer = Tail;

			while (Temp->Next->Next != nullptr)
			{
				Temp = Temp->Next;
			}

			Tail = Temp;
			Tail->Next = nullptr;
			delete DeletePointer;
		}
	}

	void DeleteNode(T Item) override
	{
		if (IsFound(Item))
		{
			if (Head == Tail)
				DeleteFirst();

			else
			{
				Node<T>* Prev = nullptr;
				Node<T>* Current = Head;

				// ÇÐÇ ßÇäÊ ÇáÚÞÏÉ Ýí ÇáÈÏÇíÉ
				if (Current->Data == Item && Current == Head)
					DeleteFirst();

				else
				{
					while (Current->Data != Item)
					{
						Prev = Current;
						Current = Current->Next;
					}

					// ÇÐÇ ßÇäÊ ÇáÚÞÏÉ Ýí ÇáÇÎíÑ ÍÊì äÍÏË ãÄÔÑ ÇáÐíá
					if (Current->Next == nullptr && Current->Data == Item)
						DeleteLast();

					else
					{
						Prev->Next = Current->Next;
						delete Current;
					}
				}
			}
		}
		else
			cout << "\nItem Not Found\n";
	}

	void Update(T Item, T NewItem) override
	{
		if (IsEmpty())
			return;

		else if (IsFound(Item))
		{
			Node<T>* Temp = Head;
			while (Temp != nullptr)
			{
				if (Temp->Data == Item)
				{
					Temp->Data = NewItem;
					break;
				}
				Temp = Temp->Next;
			}
		}
	}

	bool IsFound(T Item) const override
	{
		if (IsEmpty())
			return false;

		Node<T>* Temp = Head;
		while (Temp != nullptr)
		{
			if (Temp->Data == Item)
				return true;

			Temp = Temp->Next;
		}

		return false;
	}

	void Pop() override { _DeleteLinkedNode(); }

	int Count() const override
	{
		int ItemsCount = 0;
		Node<T>* Temp = Head;

		while (Temp != nullptr)
		{
			ItemsCount++;
			Temp = Temp->Next;
		}

		return ItemsCount;
	}

	T FirstData() const override
	{
		if (IsEmpty())
			return T();

		return Head->Data;
	}

	T LastData() const override
	{
		if (IsEmpty())
			return T();

		return Tail->Data;
	}

	void Clear() override
	{
		while (!IsEmpty())
			Pop();
	}

	~SinglyLinkedList()
	{
		Clear();
	}
};