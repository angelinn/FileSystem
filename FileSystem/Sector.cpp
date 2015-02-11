#include "Sector.h"

void SectorInfo::deserialize(std::fstream& stream)
{
	stream.read(reinterpret_cast<char*>(&nextFragment), sizeof(int));
	stream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
}

void SectorInfo::serialize(std::fstream& stream)
{
	int a = stream.tellp();
	stream.write(reinterpret_cast<const char*>(&nextFragment), sizeof(int));
	stream.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	a = stream.tellp();
}