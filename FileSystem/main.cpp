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

		//fs.addDirectory("/empty");

		//fs.importDirectory("C:\\users\\angelin\\desktop\\dirent-1.20.1", "/empty/dir");
		//fs.exportDirectory("/empty/dir", "C:\\users\\angelin\\desktop\\dirent_copy");
		//fs.deleteDirectory("/empty/dir");
		
		fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
		

		//fs.deleteFile("/empty/docx");
		//fs.addEmptyFile("/empty/emp");

		//fs.addDirectory("/empty");
		////fs.addEmptyFile("/empty/file");
		//fs.addDirectory("/other");
		//fs.addDirectory("/other/nested");

		//fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
		//fs.importFile("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", "/other/nested/du");
		//fs.copyFile("/other/nested/du", "/empty/du_copy");
		//fs.exportFile("/empty/du_copy", "C:\\users\\angelin\\desktop\\copy.docx");
		//fs.exportFile("/empty/rar", "C:\\users\\angelin\\desktop\\RAR_COPY.rar");

		//fs.importDirectory("D:\\angelin\\documents\\Eclipse", "/imported");
		//fs.exportDirectory("/imported", "C:\\users\\angelin\\desktop\\export_the_imported");

		//fs.addEmptyFile("/empty");
		//fs.addEmptyFile("/empty/dsa/ok");
		//fs.addEmptyFile("/empty/other");

		fs.printTree();
		std::cout << std::endl << fs.getTotalSize() << " vs " << fs.getSize(0) << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}