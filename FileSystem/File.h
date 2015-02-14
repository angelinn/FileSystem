#ifndef FILE_H
#define FILE_H

#include <string>
#include "SectorInfo.h"

class File
{
public:
	File();
	File(std::string, int = SectorInfo::noNext, int = SectorInfo::noNext);
	File(const File *);

public:
	static size_t getFileSize(std::istream &);

public:
	bool isDirectory() const { return isDir; }
	int getFirstSectorID() const { return firstSectorID; }
	int getLastSectorID() const { return lastSectorID; }
	std::string getName() const { return name; }
	size_t getSize() const { return size; }

public:
	void setSize(size_t);
	void setLastSectorID(int);
	void setName(const std::string &);

public:
	virtual std::string toString() const;
	virtual File* clone() { return new File(*this); }

public:
	void serialize(std::ostream &) const;
	void deserialize(std::istream &);

protected:
	bool isDir;
	std::string name;
	size_t size;

private:
	int firstSectorID;
	int lastSectorID;
};


#endif // FILE_H
