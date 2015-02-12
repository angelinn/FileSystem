#include "TNode.h"

typedef DLList<TNode*>::Iterator ListIterator;

TNode::TNode(File* item, TNode* par) : data(item), parent(par)
{  }

TNode::~TNode()
{
	delete data;
}

std::string TNode::toString() const
{
	std::string result;
	result += data->toString() + '\n';

	for (ListIterator iter = children.begin(); iter; ++iter)
		result += (*iter)->data->toString() + '\n';

	return result;
}