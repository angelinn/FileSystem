#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
public:
	File(std::string &);
	File(const File &);
	File& operator=(const File &);
	~File();

public:
	virtual std::string toString();

private:
	typedef unsigned char byte;
	void copyFrom(const File &);
	void free();

private:
	byte* content;
	std::string name;
	size_t size;
};


#endif // FILE_H
