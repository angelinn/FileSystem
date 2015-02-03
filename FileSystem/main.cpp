#include <iostream>
#include <crtdbg.h>
#include "FileSystem.h"
#include "Tools.h"


int main()
{
	try
	{
		Tree tree;
		tree.setRoot();
		std::cout << tree.getNode("/")->data->toString() << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}