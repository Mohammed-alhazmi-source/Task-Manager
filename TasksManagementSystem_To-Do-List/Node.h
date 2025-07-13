#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T Data;
	Node* Next;

	Node() : Data(T{}), Next(nullptr) {}
};