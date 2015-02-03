#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "TreeException.h"

class Tree
{
	typedef DLList<TNode*>::Iterator ListIterator;

public:
	Tree();
	~Tree();

public:
	void setRoot();
	void insert(const std::string &, File *);
	void remove(const std::string &);
	TNode* getNode(const std::string &);

private:
	Tree(const Tree &);
	Tree& operator=(const Tree &);

private:
	TNode* root;

private:
	void getNodeAt(const std::string &, TNode *&, TNode *&);

private:
	void deleteTree(TNode *&);
	void copyTree(TNode *, TNode *&);
};


#endif // TREE_H