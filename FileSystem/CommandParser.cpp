#include "CommandParser.h"
#include "FileSystem.h"

void CommandParser::registerCommand(const std::string& cmd, FileAction action)
{
	list.pushBack(cmdPair(cmd, action));
}

//void CommandParser::parse(const std::string& cmd)
//{
//	for (DLList<cmdPair>::Iterator iter = list.begin(); iter; ++iter)
//		if ((*iter).first == cmd)
//			(fs->*(*iter).second)();
//}
//
//void CommandParser::fill()
//{
//	registerCommand("mkdir", FileSystem::addDirectory);
//}