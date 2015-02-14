#ifndef TNODE_H
#define TNODE_H

#include "DLList.h"
#include "File.h"

class TNode
{
public:
	TNode(TNode* par) : parent(par), data(NULL) {   }
	TNode(File *, TNode *);
	~TNode();

	std::string toString() const;

	TNode* parent;
	DLList<TNode*> children;
	File* data;

private:
	TNode(const TNode &);
	TNode& operator=(const TNode &);
};

#endif // TNODE_H