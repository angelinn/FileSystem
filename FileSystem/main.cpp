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
		fs.create(FileSystem::FILE_NAME, true);
		//fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/rar");
		//fs.exportFile("/rar", "C:\\users\\angelin\\desktop\\copy.rar");


		fs.addDirectory("/empty");
		fs.addEmptyFile("/empty/file");
		fs.addDirectory("/other");
		fs.moveFile("/empty", "/other/emptyy");
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