#include <iostream>
#include <crtdbg.h>
#include "CLI.h"

int main()
{
	try
	{
		//CLI cli;
		//FileSystem::create(FileSystem::FILE_NAME);
		FileSystem fs;
		fs.create(FileSystem::FILE_NAME, false);
		//fs.addEmptyFile("/empty");
		//fs.addEmptyFile("/empty/dsa/ok");
		//fs.addEmptyFile("/empty/other");
		
		fs.printTree();
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}