#include <iostream>
#include <crtdbg.h>
#include "CLI.h"


int main()
{
	try
	{
		CLI cli;
		cli.promptForFS();
		cli.standby();
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}