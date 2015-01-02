#include <iostream>
#include <crtdbg.h>
#include "FileSystem.h"

#define MODIFYING_REAL_MAIN

int main()
{
	try
	{
		Tree<int> tree;
		File file(std::string("Yeah.txt"));
		Directory dir(std::string("Dir"));

		File* pFile = new File(file);
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}