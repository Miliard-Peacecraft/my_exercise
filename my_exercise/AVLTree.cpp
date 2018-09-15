#include "pch.h"
#include "AVLTree.h"

#include <iostream>

AVLNode::AVLNode(const int initValue) : Node(initValue), balance(0) {
}

bool AVLTree::Insert(const int value) {
	bool updateBalance = false;
	return _Insert(_root, value, updateBalance);
}

bool AVLTree::Delete(const int value) {
	bool updateBalance = false;
	return _Delete(_root, value, updateBalance);
}

bool AVLTree::_Insert(Node* &node, const int value, bool &updateBalance) {
	if (nullptr == node) {
		node = new AVLNode(value);
		updateBalance = true;
		return true;
	}

	if (value < node->value) {
		if (_Insert(node->leftChild, value, updateBalance)) {
			if (updateBalance) {
				if (-1 > --dynamic_cast<AVLNode*>(node)->balance) {
					const int leftChildBalance = dynamic_cast<AVLNode*>(node->leftChild)->balance;
					switch (leftChildBalance)
					{
					case -1:
						_RotateRight(node);
						break;
					case 1:
						_RotateLeft(node->leftChild);
						_RotateRight(node);
						break;
					default:
						std::cout << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << "error: balance = " << leftChildBalance << std::endl;
						break;
					}
				}

				updateBalance = (0 != dynamic_cast<AVLNode*>(node)->balance);
			}
		}
		else {
			return false;
		}
	}
	else if (value > node->value) {
		if (_Insert(node->rightChild, value, updateBalance)) {
			if (updateBalance) {
				if (1 < ++dynamic_cast<AVLNode*>(node)->balance) {
					const int rightChildBalance = dynamic_cast<AVLNode*>(node->rightChild)->balance;
					switch (rightChildBalance)
					{
					case 1:
						_RotateLeft(node);
						break;
					case -1:
						_RotateRight(node->rightChild);
						_RotateLeft(node);
						break;
					default:
						std::cout << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << "error: balance = " << rightChildBalance << std::endl;
						break;
					}
				}

				updateBalance = (0 != dynamic_cast<AVLNode*>(node)->balance);
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}

bool AVLTree::_Delete(Node* &node, const int value, bool &updateBalance) {
	if (nullptr == node) {
		return false;
	}

	if (value < node->value) {
		bool ret = _Delete(node->leftChild, value, updateBalance);
		_UpdateBalanceForDeleteFromLeftSubtree(node, updateBalance);
		return ret;

	}
	else if (value > node->value) {
		bool ret = _Delete(node->rightChild, value, updateBalance);
		_UpdateBalanceForDeleteFromRightSubtree(node, updateBalance);
		return ret;
	}
	else {
		if ((nullptr == node->leftChild) && (nullptr == node->rightChild)) {
			delete node;
			node = nullptr;
			updateBalance = true;
		}
		else if (nullptr == node->rightChild) {
			Node *temp = node;
			node = node->leftChild;
			delete temp;
			updateBalance = true;
		}
		else if (nullptr == node->leftChild) {
			Node *temp = node;
			node = node->rightChild;
			delete temp;
			updateBalance = true;
		}
		else {
			AVLNode *temp = _GetMaxSubtree(node->leftChild, updateBalance);
			temp->leftChild = node->leftChild;
			temp->rightChild = node->rightChild;
			temp->balance = dynamic_cast<AVLNode*>(node)->balance;
			delete node;
			node = temp;
			_UpdateBalanceForDeleteFromLeftSubtree(node, updateBalance);
		}
	}

	return true;
}

/*
*      A                    C
*     / \                  / \
*    B   C       =>       A   E
*       / \              / \
*      D   E            B   D
*/
void AVLTree::_RotateLeft(Node* &node) {
	AVLNode *nodeA = dynamic_cast<AVLNode*>(node);
	AVLNode *nodeC = dynamic_cast<AVLNode*>(nodeA->rightChild);
	const int nodeEHeight = nodeC->balance;												// relative to nodeDHeight = 0
	const int nodeBHeight = (0 > nodeEHeight ? 0 : nodeEHeight) + 1 - nodeA->balance;	// relative to nodeDHeight = 0

	nodeA->rightChild = nodeC->leftChild;
	nodeC->leftChild = nodeA;
	node = nodeC;

	nodeA->balance = -nodeBHeight;
	nodeC->balance = nodeEHeight - (0 > nodeBHeight ? 0 : nodeBHeight) - 1;
}

/*
*      A                    B
*     / \                  / \
*    B   C       =>       D   A
*   / \                      / \
*  D   E                    E   C
*/
void AVLTree::_RotateRight(Node* &node) {
	AVLNode *nodeA = dynamic_cast<AVLNode*>(node);
	AVLNode *nodeB = dynamic_cast<AVLNode*>(nodeA->leftChild);
	const int nodeDHeight = -nodeB->balance;											// relative to nodeEHeight = 0
	const int nodeCHeight = (0 > nodeDHeight ? 0 : nodeDHeight) + 1 + nodeA->balance;	// relative to nodeEHeight = 0

	nodeA->leftChild = nodeB->rightChild;
	nodeB->rightChild = nodeA;
	node = nodeB;

	nodeA->balance = nodeCHeight;
	nodeB->balance = (0 > nodeCHeight ? 0 : nodeCHeight) + 1 - nodeDHeight;
}

void AVLTree::_UpdateBalanceForDeleteFromLeftSubtree(Node* &node, bool &updateBalance) {
	if (updateBalance) {
		if (1 < ++dynamic_cast<AVLNode*>(node)->balance) {
			if (-1 < dynamic_cast<AVLNode*>(node->rightChild)->balance) {
				_RotateLeft(node);
			}
			else {
				_RotateRight(node->rightChild);
				_RotateLeft(node);
			}
		}

		updateBalance = (0 == dynamic_cast<AVLNode*>(node)->balance);
	}
}

void AVLTree::_UpdateBalanceForDeleteFromRightSubtree(Node* &node, bool &updateBalance) {
	if (updateBalance) {
		if (-1 > --dynamic_cast<AVLNode*>(node)->balance) {
			if (1 > dynamic_cast<AVLNode*>(node->leftChild)->balance) {
				_RotateRight(node);
			}
			else {
				_RotateLeft(node->leftChild);
				_RotateRight(node);
			}
		}

		updateBalance = (0 == dynamic_cast<AVLNode*>(node)->balance);
	}
}

AVLNode *AVLTree::_GetMaxSubtree(Node* &node, bool &updateBalance) {
	if (nullptr == node->rightChild) {
		AVLNode *temp = dynamic_cast<AVLNode*>(node);
		node = node->leftChild;
		temp->leftChild = nullptr;
		temp->balance = 0;
		updateBalance = true;
		return temp;
	}
	else {
		AVLNode *temp = _GetMaxSubtree(node->rightChild, updateBalance);
		_UpdateBalanceForDeleteFromRightSubtree(node, updateBalance);
		return temp;
	}
}
