#include "Tree.h"
#include "Tools.h"
#include "FileSystemException.h"
#include <iostream>
#include "Directory.h"

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
		root = new TNode(new Directory(BACKSLASH_STR), NULL);
}

void Tree::moveTree(TNode* source, TNode* dest)
{
	if (!source)
		return;

	source->children.pushBack(dest);
}

void Tree::copyTree(const TNode* source, TNode*& destination)
{
	if (!source)
		return;

	destination->data = source->data->isDirectory() ? new Directory(source->data) 
												    : new File(source->data);

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
		if (node->data->isDirectory())
			node->children.pushBack(new TNode(file, node));
		else
			throw InvalidFileOperation("Tried to put File* in a file!");
}

TNode* Tree::remove(const std::string& path)
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
			TNode* toBeRemoved = node->parent->children.popAt(deleter);
			--iter;

			return toBeRemoved;
		}
	}

	return NULL;
}

void Tree::getNodeAt(const std::string& path, TNode*& currentNode, TNode*& result)
{
	if (currentNode->data == path)
	{
		result = currentNode;
		return;
	}

	if (currentNode->data->getName() != path.substr(0, currentNode->data->getName().size()))
		return;

	std::string& pathLeft = getSecondPart(path);

	if (!pathLeft.empty())
	{
		for (ListIterator iter = currentNode->children.begin(); iter; ++iter)
			getNodeAt(pathLeft, *iter, result);
	}
}

void Tree::serialize(std::ostream& stream) const
{
	serializeRecursive(stream, root);
}

void Tree::serializeRecursive(std::ostream& stream, TNode* node) const
{
	int size = node->children.getSize();
	stream.write(reinterpret_cast<const char*>(&size), sizeof(int));

	node->data->serialize(stream);

	for (ListIterator iter = node->children.begin(); iter; ++iter)
		serializeRecursive(stream, *iter);
}

void Tree::deserialize(std::istream& stream, size_t at)
{
	stream.seekg(at, std::ios::beg);
	root = new TNode(NULL);
	deserializeRecursive(stream, root);
}

void Tree::deserializeRecursive(std::istream& stream, TNode*& node)
{	
	int size = 0;
	stream.read(reinterpret_cast<char*>(&size), sizeof(int));

	for (int i = 0; i < size; ++i)
		node->children.pushBack(new TNode(node));

	bool isDir = false;
	stream.read(reinterpret_cast<char*>(&isDir), sizeof(bool));

	node->data = isDir ? new Directory() : new File();

	node->data->deserialize(stream);

	for (ListIterator iter = node->children.begin(); iter; ++iter)
		deserializeRecursive(stream, *iter);
}

void Tree::DFS() const
{
	DFSR(root);
}

void Tree::DFSR(TNode* node) const
{
	std::cout << "Father: " << node->data->toString() << std::endl << node->children.getSize() << std::endl;
	for (ListIterator iter = node->children.begin(); iter; ++iter)
		std::cout << (*iter)->data->toString() << " ";

	std::cout << "\n-----------------------------------------\n";
	for (ListIterator iter = node->children.begin(); iter; ++iter)
		DFSR(*iter);
}