#include "CppUnitTest.h"

#include "../FileSystem/FileSystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileSystemTest
{		
	TEST_CLASS(TestTree)
	{
	public:
		Tree* tree;

		TEST_METHOD_INITIALIZE(SetUp)
		{
			tree = new Tree();
			tree->setRoot();
		}

		TEST_METHOD_CLEANUP(TearDown)
		{
			delete tree;
		}

		TEST_METHOD(IsRootPresent)
		{
			Assert::IsTrue(operator==(tree->getNode("/")->data, "/"));
		}

		TEST_METHOD(InsertingElementInRoot)
		{
			tree->insert("/", new File("boot"));
			Assert::IsTrue(operator==(tree->getNode("/boot")->data, "boot"));
		}

		TEST_METHOD(InsertElementNotInRoot)
		{
			tree->insert("/", new File("boot"));
			tree->insert("/boot", new File("settings.ini"));

			Assert::IsTrue(operator==(tree->getNode("/boot/settings.ini")->data, "settings.ini"));
		}

		TEST_METHOD(IsElementInChildren)
		{
			tree->insert("/", new File("boot"));
			tree->insert("/boot", new File("settings.ini"));
			tree->insert("/boot", new File("some_file"));
			tree->insert("/boot", new File("other_file"));

			for (DLList<TNode*>::Iterator iter = tree->getNode("/boot")->children.begin(); iter; ++iter)
				if (operator==((*iter)->data, "other_file"))
					return;

			Assert::IsTrue(false);
		}

		TEST_METHOD(IsParrentCorrect)
		{
			tree->insert("/", new File("boot"));
			tree->insert("/boot", new File("settings.ini"));

			Assert::IsTrue(operator==(tree->getNode("/boot/settings.ini")->parent->data, "boot"));
		}
	};
}