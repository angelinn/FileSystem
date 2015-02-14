#include "CLI.h"
#include <iostream>
#include "FileSystemException.h"

/// TO DO

CLI::CLI() : keepGoing(true)
{
	std::cout << LOADING_MESSAGE << std::endl;
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
	parser.registerCommand("help", &CLI::help);
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
	std::cout << PROMPT_ON_CREATE;

	char response = 0;
	std::cin >> response;

	std::cout << FILE_NAME_REQUEST;
	std::string fileName = FileSystem::FILE_NAME;
	//std::cin >> fileName;

	std::cout << LOADING_MESSAGE << std::endl;

	if (response == RESPONSE_NEW)
		fileSystem.create(fileName, true);
	else
		fileSystem.create(fileName);

}

void CLI::standby()
{
	FileAction action = NULL;

	while (keepGoing)
	{
		std::cout << PROMPT << SOUND_CHAR;
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

void CLI::help(DLList<std::string> &)
{

}

void CLI::exit(DLList<std::string> &)
{
	keepGoing = false;
}

void CLI::addEmptyFile(DLList<std::string>& commands)
{
	firstBuffer = commands.popBack();
	fileSystem.addEmptyFile(firstBuffer);

	std::cout << "Empty file " << firstBuffer << " added." << std::endl;
}

void CLI::addDirectory(DLList<std::string>& commands)
{
	firstBuffer = commands.popBack();
	fileSystem.addDirectory(firstBuffer);

	std::cout << "Created directory " << firstBuffer << std::endl;
}

void CLI::importFile(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.importFile(firstBuffer, secondBuffer);
	std::cout << "Imported " << firstBuffer << " into " << secondBuffer << std::endl;
}

void CLI::importDirectory(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.importDirectory(firstBuffer, secondBuffer);
	std::cout << "Imported " << firstBuffer << " into " << secondBuffer << std::endl;
}

void CLI::exportFile(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.exportFile(firstBuffer, secondBuffer);
	std::cout << "Exported " << firstBuffer << " into " << secondBuffer << std::endl;
}

void CLI::exportDirectory(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.exportDirectory(firstBuffer, secondBuffer);
	std::cout << "Exported " << firstBuffer << " into " << secondBuffer << std::endl;
}

void CLI::deleteFile(DLList<std::string>& commands)
{
	firstBuffer = commands.popBack();
	fileSystem.deleteFile(firstBuffer);

	std::cout << firstBuffer << " deleted successfully." << std::endl;
}

void CLI::deleteDirectory(DLList<std::string>& commands)
{
	firstBuffer = commands.popBack();
	fileSystem.deleteDirectory(firstBuffer);

	std::cout << firstBuffer << " deleted successfully." << std::endl;
}

void CLI::moveFile(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.moveFile(firstBuffer, secondBuffer);
	std::cout << "Moved " << firstBuffer << " to " << secondBuffer << std::endl;
}

void CLI::copyFile(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.copyFile(firstBuffer, secondBuffer);
	std::cout << "Copied " << firstBuffer << " to " << secondBuffer << std::endl;
}

void CLI::copyDirectory(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.copyDirectory(firstBuffer, secondBuffer);
	std::cout << "Copied " << firstBuffer << " to " << secondBuffer << std::endl;
}

void CLI::rename(DLList<std::string>& commands)
{
	secondBuffer = commands.popBack();
	firstBuffer = commands.popBack();

	fileSystem.rename(commands.popBack(), commands.popBack());
	std::cout << firstBuffer << " is now " << secondBuffer << std::endl;
}

void CLI::appendText(DLList<std::string>& commands)
{

}

void CLI::getFileInfo(DLList<std::string>& commands)
{
	std::cout << fileSystem.getFileInfo(commands.popBack());
}