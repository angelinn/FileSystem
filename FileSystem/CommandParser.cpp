#include "CommandParser.h"
#include "CLI.h"

void CommandParser::registerCommand(const std::string& cmd, FileAction action)
{
	list.pushBack(cmdPair(cmd, action));
}

FileAction CommandParser::getMethod(const std::string& cmd)
{
	for (DLList<cmdPair>::Iterator iter = list.begin(); iter; ++iter)
		if ((*iter).first == cmd)
			return (*iter).second;

	return NULL;
}