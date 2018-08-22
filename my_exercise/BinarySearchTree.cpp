#include "BinarySearchTree.h"

BinarySerachTree::~BinarySerachTree() {
	_Relase(_root);
}

bool BinarySerachTree::Insert(const int value) {
	Node **node = &_root;

	while (*node) {
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
	(*node) = new Node();
	(*node)->value = value;
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

int BinarySerachTree::GetHeight() {
	int height = 0;
	_GetHeight(_root, 0, height);
	return height;
}

int BinarySerachTree::GetNodeNum() {
	int n = 0;
	_GetNodeNum(_root, n);
	return n;
}

void BinarySerachTree::Print() {
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

void BinarySerachTree::_GetHeight(Node *node, int height, int &maxHeight) {
	if (nullptr == node) {
		if (height > maxHeight) {
			maxHeight = height;
		}
		return;
	}
	_GetHeight(node->leftChild, height + 1, maxHeight);
	_GetHeight(node->rightChild, height + 1, maxHeight);
}

void BinarySerachTree::_GetNodeNum(Node *node, int &n) {
	if (nullptr == node) {
		return;
	}
	_GetNodeNum(node->leftChild, n);
	_GetNodeNum(node->rightChild, n);
	++n;
}

void BinarySerachTree::_Print(Node *node) {
	if (nullptr == node) {
		return;
	}
	_Print(node->leftChild);
	std::cout << node->value << std::endl;
	_Print(node->rightChild);
}
