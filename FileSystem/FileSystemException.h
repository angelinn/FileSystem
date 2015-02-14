#ifndef FS_EXCEPTION
#define FS_EXCEPTION

#include <stdexcept>

class FileSystemException : public std::runtime_error
{
public:
	FileSystemException(const char* message) : std::runtime_error(message)
	{  }
};

class InvalidFilePath : public FileSystemException
{
public:
	InvalidFilePath(const char* message) : FileSystemException(message)
	{  }
};

class InvalidFileOperation : public FileSystemException
{
public:
	InvalidFileOperation(const char* message) : FileSystemException(message)
	{  }
};

class FileOpenError : public FileSystemException
{
public:
	FileOpenError(const char* message) : FileSystemException(message)
	{  }
};

class InvalidFileType : public FileSystemException
{
public:
	InvalidFileType(const char* message) : FileSystemException(message)
	{  }
};

#endif // FS_EXCEPTION
