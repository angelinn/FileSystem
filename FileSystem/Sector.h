#ifndef SECTOR_INFORMATION_H
#define SECTOR_INFORMATION_H

#include <fstream>

struct SectorInformation
{
	static const int noNext = -1;
	static const size_t SECTOR_SIZE = 4096;
	static void setSectorSize(size_t);

	void deserialize(std::fstream &);
	void serialize(std::fstream &);
	bool isEmpty() const { return size == 0; }
	size_t freeSpace() const { return SECTOR_SIZE - size; }

	int nextFragment;
	size_t size;
};


#endif // SECTOR_INFORMATION_H
