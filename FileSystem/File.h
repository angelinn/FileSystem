#ifndef FILE_H
#define FILE_H

#include <string>
#include "ByteContainer.h"

class File //: public ByteContainer
{
public:
	File(std::string);
	File(const File &);
	File& operator=(const File &);

public:
	void buurn();

public:
	void read(const std::string &);
	void write(const std::string &);
	static size_t getFileSize(std::ifstream &);
	virtual std::string toString();
	bool isEmpty() { return size != 0; }

private:
	int startFragmentID;

	std::string name;

	friend bool operator==(const File *, const std::string);
};

bool operator==(const File *, const std::string);


#endif // FILE_H
