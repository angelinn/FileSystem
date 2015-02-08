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
			fs->create(FileSystem::FILE_NAME, true);
		}

		TEST_METHOD_CLEANUP(TearDown)
		{
			delete fs;
		}

		TEST_METHOD(TestEmptyFileWriting)
		{
			fs->addEmptyFile("/file");
			fs->addDirectory("/empty");
			fs->addEmptyFile("/empty/dsa");
			fs->addEmptyFile("/empty/other");

			size_t expectedSize = SectorInformation::SECTOR_SIZE * 3;

			std::fstream testFile(FileSystem::FILE_NAME, std::ios::in | std::ios::binary);
			if (!testFile)
				throw - 1;

			Assert::AreEqual(expectedSize, File::getFileSize(testFile));
		}

		TEST_METHOD(CreateDirectory)
		{
			fs->addDirectory("/root");
			fs->addEmptyFile("/root/empty");

			size_t expectedSize = SectorInformation::SECTOR_SIZE;

			std::fstream testFile(FileSystem::FILE_NAME, std::ios::in | std::ios::binary);
			if (!testFile)
				throw - 1;

			Assert::AreEqual(expectedSize, File::getFileSize(testFile));
		}

		TEST_METHOD(ImportExportFile)
		{
			// TO DO
			Assert::IsTrue(false);
		}

		TEST_METHOD(MoveEmptyFile)
		{
			fs->addDirectory("/empty");
			fs->addDirectory("/empty/other");
			fs->addEmptyFile("/empty/dsa");
			fs->moveFile("/empty/dsa", "/empty/other/new_dsa");

			Assert::IsTrue(!fs->getFile("/empty/other/new_dsa")->data->getName().compare("new_dsa"));
		}
	};
}