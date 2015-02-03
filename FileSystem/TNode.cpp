#include "TNode.h"

TNode::TNode(File* item, TNode* par) : data(item), parent(par)
{  }

TNode::~TNode()
{
	delete data;
}