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
		//fs.exportFile("/rar", "C:\\users\\angelin\\desktop\\copy.rar");


		fs.addDirectory("/empty");
		//fs.addEmptyFile("/empty/file");
		fs.addDirectory("/other");
		fs.addDirectory("/other/nested");

		fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
		fs.copyFile("/empty/rar", "/other/nested/rar_copy.r");
		fs.exportFile("/other/nested/rar_copy.r", "C:\\users\\angelin\\desktop\\RAR_COPY.rar");

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