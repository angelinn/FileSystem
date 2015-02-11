#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "TreeException.h"

class Tree
{
public:
	Tree();
	Tree(const Tree &);
	Tree& operator=(const Tree &);
	~Tree();

public:
	void setRoot();
	void insert(const std::string &, File *);
	TNode* remove(const std::string &);
	TNode* getNode(const std::string &);

public:
	void DFS() const;
	void DFSR(TNode *) const;
	void serialize(std::ostream &) const;
	void deserialize(std::istream &, std::streamoff);
	void moveTree(TNode *, TNode *);

private:
	TNode* root;
	void getNodeAt(const std::string &, TNode *&, TNode *&);
	void serializeRecursive(std::ostream &, TNode *) const;
	void deserializeRecursive(std::istream &, TNode *&);

private:
	void deleteTree(TNode *&);
	void copyTree(const TNode *, TNode *&);
};


#endif // TREE_H