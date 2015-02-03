#include "Tree.h"
#include "Tools.h"

Tree::Tree() : root(NULL)
{  }

Tree::~Tree()
{
	if (root)
		deleteTree(root);
}

void Tree::setRoot()
{
	if (!root)
		root = new TNode(new File(std::string("/")), NULL);
}

void Tree::deleteTree(TNode*& node)
{
	for (ListIterator iter = node->children.begin(); iter; ++iter)
		deleteTree(*iter);

	delete node;
	node = NULL;
}

TNode* Tree::getNode(const std::string& path)
{
	TNode* node = NULL;
	getNodeAt(path, root, node);

	return node;
}

void Tree::insert(const std::string& path, File* file)
{
	TNode* node = NULL;
	getNodeAt(path, root, node);

	if (node)
		node->children.pushBack(new TNode(file, node));
}

void Tree::remove(const std::string& path)
{
	TNode* node = NULL;
	getNodeAt(path, root, node);

	if (node)
	{
		ListIterator iter = node->parent->children.begin();
		for (; iter; ++iter) // Not cool at all
		{
			if ((*iter) == node)
				node->parent->children.popAt(iter);
		}
	}

}

void Tree::getNodeAt(const std::string& path, TNode*& currentNode, TNode*& result)
{
	if (currentNode->data == path)
		result = currentNode;

	std::string& pathLeft = getSecondPart(path);

	if (!pathLeft.empty())
	{
		for (ListIterator iter = currentNode->children.begin(); iter; ++iter)
			getNodeAt(pathLeft, *iter, result);
	}
}