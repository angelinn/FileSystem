#ifndef READ_STATE
#define READ_STATE

#include "Sector.h"

///
/// Structure to help while reading from a file
///
/// Contains the:
/// byte amount information read - filled
/// sector information - info
/// if the byte array wasn't big enough, so seekg() is returned back - wouldOverwrite
/// 

struct ReadState
{
	ReadState() : filled(0), wouldOverwrite(false) 
	{  }

	size_t filled;
	SectorInfo info;
	bool wouldOverwrite;
};


#endif // READ_STATE
