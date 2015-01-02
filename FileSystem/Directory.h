#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include "DLList.h"

class Directory : public File
{
public:
	Directory(std::string &);

public:
	//virtual std::string toString();

private:
	DLList<File> files;
};

#endif // DIRECTORY_H
