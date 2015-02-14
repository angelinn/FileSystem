#ifndef CLI_H
#define CLI_H

#include "FileSystem.h"
#include "CommandParser.h"

class CLI
{
public:
	CLI();

public:
	void promptForFS();
	void standby();

private:
	void addEmptyFile(DLList<std::string> &);
	void addDirectory(DLList<std::string> &);
	void importFile(DLList<std::string> &);
	void importDirectory(DLList<std::string> &);
	void exportFile(DLList<std::string> &);
	void exportDirectory(DLList<std::string> &);
	void deleteFile(DLList<std::string> &);
	void deleteDirectory(DLList<std::string> &);
	void moveFile(DLList<std::string> &);
	void copyFile(DLList<std::string> &);
	void copyDirectory(DLList<std::string> &);
	void rename(DLList<std::string> &);
	void appendText(DLList<std::string> &);
	void getFileInfo(DLList<std::string> &);
	void exit(DLList<std::string> &);

private:
	DLList<std::string> parseInput() const;
	void registerCommands();

private:
	bool keepGoing;
	FileSystem fileSystem;
	CommandParser parser;
};


#endif // CLI_H
