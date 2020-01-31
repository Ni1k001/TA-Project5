#pragma once

#include <iostream>
#include <stdio.h>
#include <tuple>

#include "Node.h"

using namespace std;

class Edge
{
private:
	Node* first;
	Node* second;
	int value;
	bool destroy;

public:
	Edge(Node* first = NULL, Node* second = NULL, int value = 0)
	{
		this->first = first;
		this->second = second;
		this->value = value;
		destroy = false;
	}

	void SetFirst(Node* first)
	{
		this->first = first;
	}

	Node* GetFirst()
	{
		return first;
	}

	void SetSecond(Node* second)
	{
		this->second = second;
	}

	Node* GetSecond()
	{
		return second;
	}
	
	void SetValue(int value)
	{
		this->value = value;
	}

	int GetValue()
	{
		return value;
	}

	void SetDestroy(bool destroy)
	{
		this->destroy = destroy;
	}

	bool GetDestroy()
	{
		return destroy;
	}
};

