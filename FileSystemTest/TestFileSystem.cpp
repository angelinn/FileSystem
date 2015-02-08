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
			//Assert::IsFalse(_CrtDumpMemoryLeaks());
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

		TEST_METHOD(MoveDirectory)
		{
			fs->addDirectory("/empty");
			fs->addDirectory("/empty/other");
			fs->addDirectory("/test");
			fs->addDirectory("/test/dest");

			fs->addEmptyFile("/empty/dsa");
			fs->addEmptyFile("/empty/other/other_file");
			fs->moveFile("/empty", "/test/dest/empty_moved");

			fs->printTree();

			Assert::IsTrue(!fs->getFile("/test/dest/empty_moved")->data->getName().compare("empty_moved"));
			Assert::IsTrue(!fs->getFile("/test/dest/empty_moved/other")->data->getName().compare("other"));
			Assert::IsTrue(!fs->getFile("/test/dest/empty_moved/dsa")->data->getName().compare("dsa"));
			Assert::IsTrue(!fs->getFile("/test/dest/empty_moved/other/other_file")->data->getName().compare("other_file"));
		}

		TEST_METHOD(DeleteFile)
		{
			fs->addDirectory("/root");
			fs->addEmptyFile("/root/hello.rar");
			fs->deleteFile("/root/hello.rar");
			Assert::IsNull(fs->getFile("/root/hello.rar"));
		}
	};
}