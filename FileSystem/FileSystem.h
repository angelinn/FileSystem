#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Tree.h"

class FileSystem
{
public:
	void addFile();
	void addDirectory();

private:
	Tree<TNode<File*>> files;
};


#endif // FILE_SYSTEM_H
