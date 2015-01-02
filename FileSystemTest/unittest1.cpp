#include "CppUnitTest.h"

#include "../FileSystem/FileSystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileSystemTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			FileSystem system;
			File* file = new File(std::string("cool"));
			File* dir = new Directory(std::string("dir"));

			Assert::AreEqual(std::string("cool"), file->toString());
		}

		TEST_METHOD(TestMethod2)
		{

		}

	};
}