#include "CommandParser.h"
#include "CLI.h"

///
/// Adds a CLI member function with its keyword into the list
/// 
void CommandParser::registerCommand(const std::string& cmd, FileAction action)
{
	list.pushBack(cmdPair(cmd, action));
}

///
/// Returns the CLI member function pointer, based on the keyword
/// If not found, returns NULL
///
FileAction CommandParser::getMethod(const std::string& cmd)
{
	for (DLList<cmdPair>::Iterator iter = list.begin(); iter; ++iter)
		if ((*iter).first == cmd)
			return (*iter).second;

	return NULL;
}