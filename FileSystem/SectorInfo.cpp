#include "SectorInfo.h"

///
/// Writes the data in a stream
///
void SectorInfo::deserialize(std::fstream& stream)
{
	stream.read(reinterpret_cast<char*>(&nextSector), sizeof(int));
	stream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
}

///
/// Reads the data from a stream
///
void SectorInfo::serialize(std::fstream& stream)
{
	stream.write(reinterpret_cast<const char*>(&nextSector), sizeof(int));
	stream.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
}

///
/// Returns the size, available for writing per sector
/// (without the service information)
///
size_t SectorInfo::AVAILABLE_SIZE()
{
	return SECTOR_SIZE - informationSize();
}

///
/// Returns the service information size per sector
///
size_t SectorInfo::informationSize()
{
	return sizeof(size_t) + sizeof(int);
}

///
/// Returns the free space for writing
///
size_t SectorInfo::freeSpace() const
{
	return AVAILABLE_SIZE() - size;
}