#include "Fragment.h"

Fragment::Fragment() : ByteContainer()
{

}

Fragment::~Fragment()
{
	delete[] bytes;
}