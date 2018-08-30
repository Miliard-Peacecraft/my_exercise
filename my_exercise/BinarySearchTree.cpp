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
		if ((*node)->value > value) {
			node = &(*node)->leftChild;
		}
		else if ((*node)->value < value) {
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
	Node **targetNode = &_root;

	while (*targetNode) {
		if (value < (*targetNode)->value) {
			targetNode = &(*targetNode)->leftChild;
		}
		else if (value > (*targetNode)->value) {
			targetNode = &(*targetNode)->rightChild;
		}
		else {
			break;
		}
	}

	if (nullptr == (*targetNode)) {
		return false;
	}
	else {
		if ((nullptr == (*targetNode)->leftChild) && (nullptr == (*targetNode)->rightChild)) {
			delete *targetNode;
			*targetNode = nullptr;
		}
		else if (nullptr == (*targetNode)->rightChild) {
			Node *temp = (*targetNode);
			*targetNode = (*targetNode)->leftChild;
			delete temp;
		}
		else if (nullptr == (*targetNode)->leftChild) {
			Node *temp = (*targetNode);
			*targetNode = (*targetNode)->rightChild;
			delete temp;
		}
		else {
			Node **leftMax = &(*targetNode)->leftChild;

			while (nullptr != (*leftMax)->rightChild) {
				leftMax = &(*leftMax)->rightChild;
			}

			Node *temp = *leftMax;
			*leftMax = (*leftMax)->leftChild;
			temp->leftChild = (*targetNode)->leftChild;
			temp->rightChild = (*targetNode)->rightChild;
			delete *targetNode;
			*targetNode = temp;
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

void BinarySerachTree::_Print(Node *node) const {
	if (nullptr == node) {
		return;
	}
	_Print(node->leftChild);
	std::cout << node->value << std::endl;
	_Print(node->rightChild);
}
