#ifndef FILE_H
#define FILE_H

#include <string>
#include "Sector.h"

class File
{
public:
	File();
	File(std::string, int = SectorInformation::noNext);

public:
	static size_t getFileSize(std::istream &);

public:
	bool isDirectory() const { return isDir; }
	int getFragmentID() const { return startFragmentID; }
	std::string getName() const { return name; }
	void setName(const std::string nn) { name = nn; }

public:
	virtual std::string toString();
	virtual File* clone() { return new File(*this); }

public:
	void serialize(std::ostream &) const;
	void deserialize(std::istream &);

protected:
	bool isDir;
	std::string name;

private:
	size_t startFragmentID;

	friend bool operator==(const File *, const std::string &);
};

bool operator==(const File *, const std::string &);


#endif // FILE_H
