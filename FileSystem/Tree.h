#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "TreeException.h"

class Tree
{
	typedef DLList<TNode*>::Iterator ListIterator;

public:
	Tree();
	Tree(const Tree &);
	Tree& operator=(const Tree &);
	~Tree();

public:
	void setRoot();
	void insert(const std::string &, File *);
	void remove(const std::string &);
	TNode* getNode(const std::string &);

public:
	void DFS() const;
	void DFSR(TNode *) const;
	void serialize(std::fstream &) const;
	void deserialize(std::fstream &, int);

private:
	TNode* root;
	void getNodeAt(const std::string &, TNode *&, TNode *&);
	void serializeRecursive(std::fstream &, TNode *) const;
	void deserializeRecursive(std::fstream &, TNode *&);

private:
	void deleteTree(TNode *&);
	void copyTree(const TNode *, TNode *&);
};


#endif // TREE_H