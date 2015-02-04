#include <iostream>
#include <crtdbg.h>
#include "FileSystem.h"
#include "Tools.h"


int main()
{
	try
	{
		/*FileSystem::create(FileSystem::FILE_NAME);
		FileSystem fs;
		fs.addEmptyFile("/empty");
		fs.addEmptyFile("/empty/dsa");
		fs.addEmptyFile("/empty/other");*/
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}