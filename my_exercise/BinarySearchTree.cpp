#include "pch.h"
#include "BinarySearchTree.h"

#include <iostream>

Node::Node(const int initValue) : value(initValue), leftChild(nullptr), rightChild(nullptr) {
}

Node::~Node() {
}

BinarySerachTree::BinarySerachTree() : _root(nullptr) {
}

BinarySerachTree::~BinarySerachTree() {
	_Relase(_root);
}

bool BinarySerachTree::Insert(const int value) {
	Node **node = &_root;

	while (nullptr != *node) {
		if (value < (*node)->value) {
			node = &(*node)->leftChild;
		}
		else if (value > (*node)->value) {
			node = &(*node)->rightChild;
		}
		else {
			return false;
		}
	}
	(*node) = new Node(value);

	return true;
}

bool BinarySerachTree::Remove(const int value) {
	Node **node = &_root;

	while (nullptr != *node) {
		if (value < (*node)->value) {
			node = &(*node)->leftChild;
		}
		else if (value > (*node)->value) {
			node = &(*node)->rightChild;
		}
		else {
			break;
		}
	}

	if (nullptr == *node) {
		return false;
	}
	else {
		if ((nullptr == (*node)->leftChild) && (nullptr == (*node)->rightChild)) {
			delete *node;
			*node = nullptr;
		}
		else if (nullptr == (*node)->rightChild) {
			Node *temp = *node;
			*node = (*node)->leftChild;
			delete temp;
		}
		else if (nullptr == (*node)->leftChild) {
			Node *temp = (*node);
			*node = (*node)->rightChild;
			delete temp;
		}
		else {
			Node **leftMax = &(*node)->leftChild;

			while (nullptr != (*leftMax)->rightChild) {
				leftMax = &(*leftMax)->rightChild;
			}

			Node *temp = *leftMax;
			*leftMax = (*leftMax)->leftChild;
			temp->leftChild = (*node)->leftChild;
			temp->rightChild = (*node)->rightChild;
			delete *node;
			*node = temp;
		}
	}

	return true;
}

int BinarySerachTree::GetHeight() const {
	return _GetHeight(_root);
}

int BinarySerachTree::GetNodeNum() const {
	return _GetNodeNum(_root);
}

void BinarySerachTree::Print() const {
	_Print(_root);
}

void BinarySerachTree::_Relase(Node *node) {
	if (nullptr == node) {
		return;
	}

	_Relase(node->leftChild);
	_Relase(node->rightChild);
	delete node;
}

int BinarySerachTree::_GetHeight(const Node *node) const {
	if (nullptr == node) {
		return 0;
	}

	const int lHeight = _GetHeight(node->leftChild);
	const int rHeight = _GetHeight(node->rightChild);
	return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

int BinarySerachTree::_GetNodeNum(const Node *node) const {
	if (nullptr == node) {
		return 0;
	}

	return _GetNodeNum(node->leftChild) + _GetNodeNum(node->rightChild) + 1;
}

void BinarySerachTree::_Print(const Node *node) const {
	if (nullptr == node) {
		return;
	}

	_Print(node->leftChild);
	std::cout << node->value << std::endl;
	_Print(node->rightChild);
}
