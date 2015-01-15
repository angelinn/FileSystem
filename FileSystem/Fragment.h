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

private:
	static const int FRAGMENT_SIZE = 0;
};


#endif // FRAGMENT_H
