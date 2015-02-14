#include "CLI.h"
#include <iostream>
#include "FileSystemException.h"

/// TO DO

CLI::CLI() : keepGoing(true)
{
	std::cout << "loading .." << std::endl;
	registerCommands();
}

void CLI::registerCommands()
{
	parser.registerCommand("touch", &CLI::addEmptyFile);
	parser.registerCommand("mkdir", &CLI::addDirectory);
	parser.registerCommand("import-file", &CLI::importFile);
	parser.registerCommand("import-dir", &CLI::importDirectory);
	parser.registerCommand("export-file", &CLI::exportFile);
	parser.registerCommand("export-dir", &CLI::exportDirectory);
	parser.registerCommand("delete-file", &CLI::deleteFile);
	parser.registerCommand("delete-dir", &CLI::deleteDirectory);
	parser.registerCommand("move", &CLI::moveFile);
	parser.registerCommand("copy-file", &CLI::copyFile);
	parser.registerCommand("copy-dir", &CLI::copyDirectory);
	parser.registerCommand("rename", &CLI::rename);
	parser.registerCommand("append", &CLI::appendText);
	parser.registerCommand("dir", &CLI::getFileInfo);
	parser.registerCommand("exit", &CLI::exit);
}

DLList<std::string> CLI::parseInput() const
{
	char buffer[_MAX_PATH];
	std::cin.getline(buffer, _MAX_PATH);

	DLList<std::string> result;
	DLList<int> boundaries;
	boundaries.pushBack(0);

	int i = 0;
	for (; buffer[i] != '\0'; ++i)
	{
		if (buffer[i] == ' ')
			boundaries.pushBack(i);
		else if (buffer[i] == '\"')
		{
			++i;
			while (buffer[i] != '\"')
				++i;

			boundaries.pushBack(++i);
		}
	}
	boundaries.pushBack(i);

	int start = boundaries.popFront();
	int end = 0;

	while (!boundaries.isEmpty())
	{
		end = boundaries.popFront();
		result.pushBack(std::string(buffer, start, end - start));
		start = end + 1;
	}

	return result;
}

void CLI::promptForFS()
{
	std::cout << "If you want to create a new file system, type 'n'!\n"
		<< "Else if you want to create an existing one type 'e'!\n";

	char response = 0;
	std::cin >> response;

	std::cout << "\nType in the name of the File\n > ";
	std::string fileName = FileSystem::FILE_NAME;
	//std::cin >> fileName;

	std::cout << "creating .." << std::endl;

	if (response == 'n')
		fileSystem.create(fileName, true);
	else
		fileSystem.create(fileName);

}

void CLI::standby()
{
	FileAction action = NULL;

	while (keepGoing)
	{
		std::cout << "> \a";
		DLList<std::string>& commands = parseInput();
		try
		{
			action = parser.getMethod(commands.popFront());
			if (action)
				(this->*action)(commands);
		}
		catch (InvalidFilePath& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			//std::cerr << "Something wrong happened." << std::endl;
		}
	}
}

void CLI::exit(DLList<std::string> &)
{
	keepGoing = false;
}

void CLI::addEmptyFile(DLList<std::string>& commands)
{
	fileSystem.addEmptyFile(commands.popFront());
}

void CLI::addDirectory(DLList<std::string>& commands)
{
	fileSystem.addDirectory(commands.popFront());
	std::cout << "Created dir " << std::endl;
}

void CLI::importFile(DLList<std::string>& commands)
{
	fileSystem.importFile(commands.popBack(), commands.popBack());
}

void CLI::importDirectory(DLList<std::string>& commands)
{
	fileSystem.importDirectory(commands.popBack(), commands.popBack());
}

void CLI::exportFile(DLList<std::string>& commands)
{
	fileSystem.exportFile(commands.popBack(), commands.popBack());
}

void CLI::exportDirectory(DLList<std::string>& commands)
{
	fileSystem.exportDirectory(commands.popBack(), commands.popBack());
}

void CLI::deleteFile(DLList<std::string>& commands)
{
	fileSystem.deleteFile(commands.popBack());
}

void CLI::deleteDirectory(DLList<std::string>& commands)
{
	fileSystem.deleteDirectory(commands.popBack());
}

void CLI::moveFile(DLList<std::string>& commands)
{
	fileSystem.moveFile(commands.popBack(), commands.popBack());
}

void CLI::copyFile(DLList<std::string>& commands)
{
	fileSystem.copyFile(commands.popBack(), commands.popBack());
}

void CLI::copyDirectory(DLList<std::string>& commands)
{
	fileSystem.copyDirectory(commands.popBack(), commands.popBack());
}

void CLI::rename(DLList<std::string>& commands)
{
	fileSystem.rename(commands.popBack(), commands.popBack());
}

void CLI::appendText(DLList<std::string>& commands)
{

}

void CLI::getFileInfo(DLList<std::string>& commands)
{
	std::cout << fileSystem.getFileInfo(commands.popBack());
}