#include "pch.h"
#include "AVLTree.h"

#include <iostream>

AVLNode::AVLNode(const int initValue) : Node(initValue), balance(0) {

}

bool AVLTree::Insert(const int value) {
	bool updateBalance = false;
	return _Insert(_root, value, updateBalance);
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
				int &nodeBalance = dynamic_cast<AVLNode*>(node)->balance;

				if (-1 > --nodeBalance) {
					const int leftChildBalance = dynamic_cast<AVLNode*>(node->leftChild)->balance;
					switch (leftChildBalance)
					{
					case -1:
						_RotateRight(node);
						break;
					case 1:
						_RotateLeft(node);
						_RotateRight(node);
						break;
					default:
						std::cout << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << "error: balance = " << leftChildBalance << std::endl;
						break;
					}
				}

				if (0 == nodeBalance) {
					updateBalance = false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (value > node->value) {
		if (_Insert(node->rightChild, value, updateBalance)) {
			if (updateBalance) {
				int &nodeBalance = dynamic_cast<AVLNode*>(node)->balance;

				if (1 < ++nodeBalance) {
					const int rightChildBalance = dynamic_cast<AVLNode*>(node->rightChild)->balance;
					switch (rightChildBalance)
					{
					case 1:
						_RotateLeft(node);
						break;
					case -1:
						_RotateRight(node);
						_RotateLeft(node);
						break;
					default:
						std::cout << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << "error: balance = " << rightChildBalance << std::endl;
						break;
					}
				}

				if (0 == nodeBalance) {
					updateBalance = false;
				}
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

/*
		A                      C
	   / \                    / \
	  B   C                 A     E
		 / \     =>        / \
		D   E             B   D
*/
void AVLTree::_RotateLeft(Node* &node) {
	AVLNode *nodeA = dynamic_cast<AVLNode*>(node);
	AVLNode *nodeC = dynamic_cast<AVLNode*>(nodeA->rightChild);
	int nodeEHeight = nodeC->balance;											// relative to nodeDHeight = 0
	int nodeBHeight = (0 > nodeEHeight ? 0 : nodeEHeight) + 1 - nodeA->balance;	// relative to nodeDHeight = 0

	nodeA->rightChild = nodeC->leftChild;
	nodeC->leftChild = nodeA;
	node = nodeC;

	nodeA->balance = -nodeBHeight;
	nodeC->balance = nodeEHeight - (0 > nodeBHeight ? 0 : nodeBHeight) - 1;
}

/*
		A                      B
	   / \                    / \
	  B   C                 D     A
	 / \         =>              / \
	D   E                       E   C
*/
void AVLTree::_RotateRight(Node* &node) {
	AVLNode *nodeA = dynamic_cast<AVLNode*>(node);
	AVLNode *nodeB = dynamic_cast<AVLNode*>(nodeA->leftChild);
	
	int nodeDHeight = -nodeB->balance;											// relative to nodeEHeight = 0
	int nodeCHeight = (0 > nodeDHeight ? 0 : nodeDHeight) + 1 + nodeA->balance;	// relative to nodeEHeight = 0

	nodeA->leftChild = nodeB->rightChild;
	nodeB->rightChild = nodeA;
	node = nodeB;

	nodeA->balance = nodeCHeight;
	nodeB->balance = (0 > nodeCHeight ? 0 : nodeCHeight) + 1 - nodeDHeight;
}
