#ifndef FILE_H
#define FILE_H

#include <string>
#include "Sector.h"

class File
{
public:
	File(std::string, int = SectorInformation::noNext);

public:
	virtual std::string toString();

private:
	int startFragmentID;
	std::string name;
	friend bool operator==(const File *, const std::string);
};

bool operator==(const File *, const std::string);


#endif // FILE_H
