#ifndef READ_STATE
#define READ_STATE

#include "Sector.h"

struct ReadState
{
	size_t filled;
	SectorInfo info;
	bool wouldOverwrite;
};


#endif // READ_STATE
