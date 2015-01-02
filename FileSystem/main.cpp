#include <iostream>
#include "Tree.h"
#include <crtdbg.h>

int main()
{
	{
		Tree<int> tree;
	}

	_CrtDumpMemoryLeaks();
}