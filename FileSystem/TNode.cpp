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
	result += "\nContents of " + data->toString() + "\n\n";

	for (ListIterator iter = children.begin(); iter; ++iter)
		result += (*iter)->data->toString() + '\n';

	result += "\nTotal of (" + std::to_string(children.getSize()) + ") files.\n";
	return result;
}