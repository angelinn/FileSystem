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

			size_t expectedSize = SectorInfo::SECTOR_SIZE * 3;

			std::fstream testFile(FileSystem::FILE_NAME, std::ios::in | std::ios::binary);
			if (!testFile)
				throw - 1;

			Assert::AreEqual(expectedSize, (size_t)File::getFileSize(testFile));
		}

		TEST_METHOD(CreateDirectory)
		{
			fs->addDirectory("/root");
			fs->addEmptyFile("/root/empty");

			size_t expectedSize = SectorInfo::SECTOR_SIZE;

			std::fstream testFile(FileSystem::FILE_NAME, std::ios::in | std::ios::binary);
			if (!testFile)
				throw - 1;

			Assert::AreEqual(expectedSize, (size_t)File::getFileSize(testFile));
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

		TEST_METHOD(ImportExportFile)
		{
			std::string path("C:\\users\\angelin\\desktop\\hello.rar");
			std::string output("C:\\users\\angelin\\desktop\\COPY_FS.rar");


			fs->addDirectory("/empty");
			fs->importFile(path, "/empty/rar");
			fs->exportFile("/empty/rar", output);

			std::ifstream i(path, std::ios::in | std::ios::binary);
			std::ifstream o(output, std::ios::in | std::ios::binary);

			if (!i || !o)
				throw - 1;

			Assert::AreEqual(File::getFileSize(i), File::getFileSize(o));
			i.close();
			o.close();
			std::remove(output.c_str());
		}

		TEST_METHOD(CopyFile)
		{
			std::string path("C:\\users\\angelin\\desktop\\hello.rar");
			std::string output("C:\\users\\angelin\\desktop\\TEST_COPY_FS.rar");


			fs->addDirectory("/empty");
			fs->addDirectory("/other");
			fs->addDirectory("/other/nested");
			fs->importFile(path, "/empty/rar");
			fs->copyFile("/empty/rar", "/other/nested/rar_copy");
			fs->exportFile("/other/nested/rar_copy", output);

			std::ifstream i(path, std::ios::in | std::ios::binary);
			std::ifstream o(output, std::ios::in | std::ios::binary);

			if (!i || !o)
				throw "can't open stream";

			Assert::AreEqual(File::getFileSize(i), File::getFileSize(o));
			i.close();
			o.close();
			std::remove(output.c_str());
		}

		TEST_METHOD(AddTwoFilesInDifferentDirsAndExport)
		{
			fs->addDirectory("/empty");
			fs->addDirectory("/other");
			fs->addDirectory("/other/nested");

			fs->importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
			fs->importFile("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", "/other/nested/du");
			fs->copyFile("/other/nested/du", "/empty/du_copy");
			fs->exportFile("/empty/du_copy", "C:\\users\\angelin\\desktop\\copy.docx");
			fs->exportFile("/empty/rar", "C:\\users\\angelin\\desktop\\RAR_COPY.rar");

			std::ifstream i("C:\\users\\angelin\\desktop\\hello.rar", std::ios::in | std::ios::binary);
			std::ifstream o("C:\\users\\angelin\\desktop\\RAR_COPY.rar", std::ios::in | std::ios::binary);

			if (!i || !o)
				throw "can't open stream";

			Assert::AreEqual(File::getFileSize(i), File::getFileSize(o));
			i.close();
			o.close();

			i.open("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", std::ios::in | std::ios::binary);
			o.open("C:\\users\\angelin\\desktop\\copy.docx", std::ios::in | std::ios::binary);

			if (!i || !o)
				throw "can't open stream";

			Assert::AreEqual(File::getFileSize(i), File::getFileSize(o));
			i.close();
			o.close();
		}

		TEST_METHOD(CopyDirectoryAndExportFiles)
		{
			fs->addDirectory("/empty");
			fs->addDirectory("/empty/nested");
			fs->addDirectory("/other");

			fs->importFile("C:\\users\\angelin\\desktop\\hello.rar", "/empty/rar");
			fs->importFile("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", "/empty/nested/docx");
			fs->copyDirectory("/empty", "/other/empty_copy");

			fs->exportFile("/other/empty_copy/nested/docx", "C:\\users\\angelin\\desktop\\copy.docx");
			fs->exportFile("/other/empty_copy/rar", "C:\\users\\angelin\\desktop\\RAR_COPY.rar");

			std::ifstream i("C:\\users\\angelin\\desktop\\hello.rar", std::ios::in | std::ios::binary);
			std::ifstream o("C:\\users\\angelin\\desktop\\RAR_COPY.rar", std::ios::in | std::ios::binary);

			if (!i || !o)
				throw "can't open stream";

			Assert::AreEqual(File::getFileSize(i), File::getFileSize(o));
			i.close();
			o.close();

			i.open("C:\\users\\angelin\\desktop\\54 Angelin Nedelchev.docx", std::ios::in | std::ios::binary);
			o.open("C:\\users\\angelin\\desktop\\copy.docx", std::ios::in | std::ios::binary);

			if (!i || !o)
				throw "can't open stream";

			Assert::AreEqual(File::getFileSize(i), File::getFileSize(o));
			i.close();
			o.close();
		}

		TEST_METHOD(IsDirectory)
		{
			std::string file("C:\\users\\angelin\\desktop\\copy.docx");
			std::string dir("C:\\users\\angelin\\desktop");

			Assert::IsFalse(fs->isDirectory(file));
			Assert::IsTrue(fs->isDirectory(dir));
		}
	};
}