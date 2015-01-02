#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Tree.h"

class FileSystem
{
public:
	void addFile();
	void addDirectory();

public:
	virtual std::string toString();

private:
	Tree<TNode<File*>> files;
};


#endif // FILE_SYSTEM_H
