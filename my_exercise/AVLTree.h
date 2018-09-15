#pragma once

#include "BinarySearchTree.h"

class AVLNode : public Node {
public:
	AVLNode(const int initValue);
	int balance;
};

class AVLTree : public BinarySerachTree {
public:
	bool Insert(const int value);
	bool Delete(const int value);

private:
	bool _Insert(Node* &node, const int value, bool &updateBalance);
	bool _Delete(Node* &node, const int value, bool &updateBalance);
	void _RotateLeft(Node* &node);
	void _RotateRight(Node* &node);
	void _UpdateBalanceForDeleteFromLeftSubtree(Node* &node, bool &updateBalance);
	void _UpdateBalanceForDeleteFromRightSubtree(Node* &node, bool &updateBalance);
	AVLNode *_GetMaxSubtree(Node* &node, bool &updateBalance);
};
