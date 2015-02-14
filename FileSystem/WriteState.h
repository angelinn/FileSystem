#ifndef WRITE_STATE
#define WRITE_STATE

#include "SectorInfo.h"

///
/// Represents a sector information and
/// the last sector ID of a file
///
struct WriteState
{
	WriteState() : lastSectorID(-1)
	{  }

	SectorInfo info;
	int lastSectorID;
};


#endif // WRITE_STATE
