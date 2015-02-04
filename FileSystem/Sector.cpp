#include "Sector.h"

void SectorInformation::deserialize(std::fstream& stream)
{
	stream.read(reinterpret_cast<char*>(nextFragment), sizeof(int));
	stream.read(reinterpret_cast<char*>(size), sizeof(size_t));
}

void SectorInformation::serialize(std::fstream& stream)
{
	stream.write(reinterpret_cast<const char*>(nextFragment), sizeof(int));
	stream.write(reinterpret_cast<const char*>(size), sizeof(size_t));
}