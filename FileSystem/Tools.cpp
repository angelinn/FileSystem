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

std::string buildPath(const std::string& first, const std::string& second)
{
	return first + BACKSLASH_STR + second;
}

template <typename T>
void allocate(T*& arr, size_t size)
{
	try
	{
		arr = new T[size];
	}
	catch (std::bad_alloc &)
	{
		delete[] arr;
		throw;
	}
}