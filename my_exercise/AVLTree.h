#pragma once

#include "BinarySearchTree.h"

class AVLNode : public Node {
public:
	AVLNode(const int initValue);
	int balance;
};

class AVLTree :	public BinarySerachTree {
public:
	bool Insert(const int value);

private:
	bool _Insert(Node* &node, const int value, bool &updateBalance);
	void _RotateLeft(Node* &node);
	void _RotateRight(Node* &node);
};
