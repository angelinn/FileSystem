#include "Tools.h"

stringPair splitPath(const std::string& path)
{
	std::string workPath(path, 1);
	size_t nextBackslash = workPath.find(BACKSLASH_CHAR);

	if (nextBackslash == std::string::npos)
		throw std::exception("Something went wrong with string splitting!");

	std::string current(workPath, 0, nextBackslash);
	std::string leftover(workPath, nextBackslash + 1);

	return stringPair(current, leftover);
}

std::string getSecondPart(const std::string& path)
{
	size_t nextBackslash = path.find(BACKSLASH_CHAR);

	if (nextBackslash == std::string::npos)
		return std::string();

	return std::string(path, nextBackslash + 1);
}