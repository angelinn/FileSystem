#include "CppUnitTest.h"

#include "../FileSystem/FileSystem.h"
#include "../FileSystem/FileSystemException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileSystemTest
{
	TEST_CLASS(TestFileSystem)
	{
	public:
		FileSystem* fs;

		TEST_METHOD_INITIALIZE(SetUp)
		{
			fs = new FileSystem();
		}

		TEST_METHOD_CLEANUP(TearDown)
		{
			delete fs;
		}

		TEST_METHOD(TestEmptyFileWriting)
		{
			fs->create(FileSystem::FILE_NAME, true);
			fs->addEmptyFile("/empty");
			fs->addEmptyFile("/empty/dsa");
			fs->addEmptyFile("/empty/other");

			size_t expectedSize = SectorInformation::SECTOR_SIZE * 3 + sizeof(int) * 3 + sizeof(size_t) * 3;

			std::fstream testFile(FileSystem::FILE_NAME, std::ios::in | std::ios::binary);
			if (!testFile)
				throw - 1;

			Assert::AreEqual(expectedSize, File::getFileSize(testFile));
		}
	};
}