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
	static const size_t FRAGMENT_SIZE = 4096;

private:
	static int ID;
	int nextFragment;
	size_t startByte;
	size_t endByte;
};


#endif // FRAGMENT_H
