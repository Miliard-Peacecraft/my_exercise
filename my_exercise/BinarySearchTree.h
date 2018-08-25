#pragma once

class Node {
public:
	Node(const int initValue) : value(initValue), rightChild(nullptr), leftChild(nullptr) {}
	const int value;
	Node *rightChild;
	Node *leftChild;
};

class BinarySerachTree {
public:
	BinarySerachTree() : _root(nullptr) {}
	~BinarySerachTree();
	bool Insert(const int value);
	bool Remove(const int value);
	int GetHeight() const;
	int GetNodeNum() const;
	void Print();

private:
	void _Relase(Node *node);
	int _GetHeight(const Node *node) const;
	int _GetNodeNum(const Node *node) const;
	void _Print(Node *node);

	Node *_root;
};
