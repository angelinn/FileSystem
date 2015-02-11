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


		//fs.addDirectory("/empty");
		////fs.addEmptyFile("/empty/file");
		//fs.addDirectory("/other");
		//fs.addDirectory("/other/nested");

		//fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
		//fs.importFile("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", "/other/nested/du");
		//fs.copyFile("/other/nested/du", "/empty/du_copy");
		//fs.exportFile("/empty/du_copy", "C:\\users\\angelin\\desktop\\copy.docx");
		//fs.exportFile("/empty/rar", "C:\\users\\angelin\\desktop\\RAR_COPY.rar");

		fs.importDirectory("D:\\angelin\\documents\\Eclipse", "/imported");
		fs.flush();
		fs.exportDirectory("/imported", "C:\\users\\angelin\\desktop\\export_the_imported");

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