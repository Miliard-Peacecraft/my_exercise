#pragma once

class Node {
public:
	Node(const int initValue);
	virtual ~Node();
	const int value;
	Node *leftChild;
	Node *rightChild;
};

class BinarySerachTree {
public:
	BinarySerachTree();
	virtual ~BinarySerachTree();
	virtual bool Insert(const int value);
	virtual bool Delete(const int value);
	virtual int GetHeight() const;
	virtual int GetNodeNum() const;
	virtual void Print() const;

protected:
	Node *_root;

private:
	void _Relase(Node *node);
	int _GetHeight(const Node *node) const;
	int _GetNodeNum(const Node *node) const;
	void _Print(const Node *node) const;
};
