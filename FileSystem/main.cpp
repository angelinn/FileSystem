#include <iostream>
#include <crtdbg.h>
#include "CLI.h"
#include <ctime>


int main()
{
	try
	{
		//CLI cli;
		//cli.promptForFS();
		//cli.standby();
		FileSystem fs;
		fs.create(FileSystem::FILE_NAME, false);

		fs.addDirectory("/empty");
		//fs.importFile("C:\\Users\\Angelin\\Desktop\\doxygen-1.8.9.1.src\\doxygen-1.8.9.1\\src\\translator_am.h", "/empty/rar");
		//fs.exportFile("/empty/rar", "C:\\users\\angelin\\desktop\\other.h");
		//fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
		//fs.importFile("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", "/empty/docx");
		//fs.importDirectory("D:\\ubuntu", "/empty/ubuntu");
		//fs.importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar_other");
		//fs.exportDirectory("/empty/ubuntu", "C:\\users\\angelin\\desktop\\cool_ubuntu");
		//fs.addDirectory("/other");
		//fs.copyFile("/other/nested/du", "/empty/du_copy");
		//fs.exportFile("/empty/docx", "C:\\users\\angelin\\desktop\\cool_docx.docx");
		//fs.exportFile("/empty/rar", "C:\\users\\angelin\\desktop\\cool_rar.rar");

		//fs.printTree();
		//std::cout << std::endl << fs.getTotalSize() << " vs " << fs.getSize(0) << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}