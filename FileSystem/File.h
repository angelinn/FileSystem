#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
public:
	File(std::string &);
	File(std::string &, std::string &);
	File(const File &);
	File& operator=(const File &);
	virtual ~File();

public:
	static size_t getFileSize(std::ifstream &);
	virtual std::string toString();
	bool isEmpty() { return size != 0; }

private:
	void copyFrom(const File &);
	void free();

private:
	typedef unsigned char byte;
	byte* content;
	std::string name;
	size_t size;
};


#endif // FILE_H
