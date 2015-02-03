#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "ByteContainer.h"

class Fragment : public ByteContainer
{
public:
	Fragment();
	Fragment(const Fragment &);
	Fragment& operator=(const Fragment &);

public:
	static void setFragmentSize(size_t);
	static const int FRAGMENT_SIZE = 0;

private:
	size_t startByte;
	size_t endByte;
};


#endif // FRAGMENT_H
