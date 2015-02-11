#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include "DLList.h"

class Directory : public File
{
public:
	Directory(const std::string &);
	Directory(const File *);

public:
	virtual std::string toString() const;
	virtual Directory* clone() { return new Directory(*this); }
};

#endif // DIRECTORY_H
