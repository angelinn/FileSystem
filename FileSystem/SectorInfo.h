#ifndef SECTOR_INFORMATION_H
#define SECTOR_INFORMATION_H

#include <fstream>

class SectorInfo
{
public:
	SectorInfo() : nextSector(-2), size(-1) 
	{  }

public:
	/// Indicates there is no next sector
	static const int noNext = -1;
	static const size_t SECTOR_SIZE = 4096;

public:
	static size_t AVAILABLE_SIZE();
	static size_t informationSize();

public:
	void deserialize(std::fstream &);
	void serialize(std::fstream &);

public:
	bool isEmpty() const { return size == 0; }
	size_t freeSpace() const;

public:
	int nextSector;
	size_t size;
};


#endif // SECTOR_INFORMATION_H
