#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include "DLList.h"

class Directory : public File
{
public:
	Directory(const std::string &);

public:
	//virtual std::string toString();
};

#endif // DIRECTORY_H
