#include "Tree.h"
#include "Tools.h"
#include "FileSystemException.h"

Tree::Tree() : root(NULL)
{  }

Tree::Tree(const Tree& other) : root(NULL)
{
	copyTree(other.root, root);
}

Tree& Tree::operator=(const Tree& other)
{
	if (this != &other)
	{
		deleteTree(root);
		copyTree(other.root, root);
	}

	return *this;
}

Tree::~Tree()
{
	deleteTree(root);
}

void Tree::setRoot()
{
	if (!root)
		root = new TNode(new File(std::string("/")), NULL);
}

// Not Tested yet
void Tree::copyTree(const TNode* source, TNode*& destination)
{
	if (!source)
		return;

	destination->data = new File(*source->data);
	TNode* child = NULL;

	for (ListIterator iter = source->children.begin(); iter; ++iter)
	{
		child = new TNode(NULL, destination);
		copyTree(*iter, child);
		destination->children.pushBack(child);
	}
}

void Tree::deleteTree(TNode*& node)
{
	if (node)
	{
		for (ListIterator iter = node->children.begin(); iter; ++iter)
			deleteTree(*iter);

		delete node;
		node = NULL;
	}
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

	if (!node)
		throw InvalidFilePath("File not found!");

	if (node == root)
		throw InvalidFileOperation("You can't delete the root directory!");

	ListIterator iter = node->parent->children.begin();
	for (; iter; ++iter) // Not cool at all
	{
		if ((*iter) == node)
		{
			ListIterator deleter = iter;
			++iter;
			delete node->parent->children.popAt(deleter);
			--iter;
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