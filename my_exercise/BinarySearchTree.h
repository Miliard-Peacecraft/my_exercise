#pragma once

class Node {
public:
	Node() : value(0), rightChild(nullptr), leftChild(nullptr) {}
	int value;
	Node *rightChild;
	Node *leftChild;
};

class BinarySerachTree {
public:
	BinarySerachTree() : _root(nullptr) {}
	~BinarySerachTree();
	bool Insert(const int value);
	bool Remove(const int value);
	int GetHeight();
	int GetNodeNum();
	void Print();

private:
	void _Relase(Node *node);
	void _GetHeight(Node *node, int height, int &maxHeight);
	void _GetNodeNum(Node *node, int &n);
	void _Print(Node *node);

	Node *_root;
};
