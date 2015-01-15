#ifndef BYTE_CONTAINER_H
#define BYTE_CONTAINER_H

#include <cstring>

class ByteContainer
{
	typedef unsigned char byte;

public:
	ByteContainer(byte* = NULL, size_t = 0);
	ByteContainer(const ByteContainer &);
	ByteContainer& operator=(const ByteContainer &);
	virtual ~ByteContainer() = 0;

protected:
	byte* content;
	size_t size;

private:
	void copyFrom(const ByteContainer &);
	void free();
};


#endif // BYTE_CONTAINER_H