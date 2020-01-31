#pragma once

#include <iostream>
#include <stdio.h>
#include <tuple>

using namespace std;

class Node
{
private:
	int h;
	Node* parent;
	Node* root;
	int x = -1; int y = -1;

public:
	Node(int height = 0, Node* parent = NULL)
	{
		this->h = height;
		this->parent = parent;
	}

	void SetHeight(int height)
	{
		this->h = height;
	}

	int GetHeight()
	{
		return h;
	}

	void SetParent(Node* parent)
	{
		this->parent = parent;
	}

	Node* GetParent()
	{
		return parent;
	}

	bool HasParent()
	{
		if (parent != NULL)
			return true;
		return false;
	}

	void SetRoot(Node* node)
	{
		root = node;
	}
	
	Node* GetRoot()
	{
		Node* walker = this;

		while (walker->GetParent() != NULL)
			walker = walker->GetParent();

		return walker;
	}

	bool FindUnion(Node* node)
	{
		if (this->GetRoot() == node->GetRoot())
			return true;
		return false;
	}

	bool MergeUnions(Node* node)
	{
		Node* root1 = this->GetRoot();
		Node* root2 = node->GetRoot();

		if (root1 == root2)
			return false;

		if (root1->GetHeight() < root2->GetHeight())
		{
			root1->SetRoot(root2);
			root1->SetParent(node);
		}
		else
		{
			root2->SetRoot(root1);
			root2->SetParent(this);

			if (root1->GetHeight() == root2->GetHeight())
				root1->SetHeight(root1->GetHeight() + 1);
		}

		return true;
	}

	void SetCoords(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	tuple<int, int> GetCoords()
	{
		return make_tuple(x, y);
	}
};

