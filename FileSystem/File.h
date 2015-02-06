#ifndef FILE_H
#define FILE_H

#include <string>
#include "Sector.h"

class File
{
public:
	File();
	File(std::string, int = SectorInformation::noNext, bool = false);

public:
	virtual std::string toString();
	void serialize(std::fstream &) const;
	void deserialize(std::fstream &);
	static size_t getFileSize(std::fstream &);

private:
	int startFragmentID;
	std::string name;
	bool isDirectory;

	friend bool operator==(const File *, const std::string);
};

bool operator==(const File *, const std::string);


#endif // FILE_H
