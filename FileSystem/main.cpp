#include <iostream>
#include <crtdbg.h>
#include "FileSystem.h"

int main()
{
	try
	{
		Tree<int> tree;
		File file(std::string("Yeah.txt"));
		Directory dir(std::string("Dir"));
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}