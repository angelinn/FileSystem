#ifndef SECTOR_INFORMATION_H
#define SECTOR_INFORMATION_H

#include <fstream>

class SectorInfo
{
public:
	static const int noNext = -1;
	static const size_t SECTOR_SIZE = 4096;
	static void setSectorSize(size_t);

	// To do - sector only 4096 bytes including the offset
	static size_t AVAILABLE_SIZE() { return SECTOR_SIZE - informationSize(); }

	void deserialize(std::fstream &);
	void serialize(std::fstream &);
	bool isEmpty() const { return size == 0; }
	size_t freeSpace() const { return AVAILABLE_SIZE() - size; }
	static size_t informationSize() { return sizeof(size_t) + sizeof(int); }



	int nextFragment;
	size_t size;
};


#endif // SECTOR_INFORMATION_H
