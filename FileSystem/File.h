#ifndef FILE_H
#define FILE_H

#include <string>
#include "ByteContainer.h"

class File : public ByteContainer
{
public:
	File(std::string &);
	File(std::string &, std::string &);
	File(const File &);
	File& operator=(const File &);

public:
	static size_t getFileSize(std::ifstream &);
	virtual std::string toString();
	bool isEmpty() { return size != 0; }

private:
	std::string name;
};


#endif // FILE_H
