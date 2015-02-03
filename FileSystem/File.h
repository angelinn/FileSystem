#ifndef FILE_H
#define FILE_H

#include <string>
#include "ByteContainer.h"

class File : public ByteContainer
{
public:
	File(std::string);
	File(std::string, std::string);
	File(const File &);
	File& operator=(const File &);

public:
	static size_t getFileSize(std::ifstream &);
	virtual std::string toString();
	bool isEmpty() { return size != 0; }

private:
	int endFragment;
	int startFragment;

	std::string name;

	friend bool operator==(const File *, const std::string);
};

bool operator==(const File *, const std::string);


#endif // FILE_H
