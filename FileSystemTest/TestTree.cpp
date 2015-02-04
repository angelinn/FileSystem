#include "CppUnitTest.h"

#include "../FileSystem/FileSystem.h"
#include "../FileSystem/FileSystemException.h"

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

			tree->insert("/", new File("boot"));
			tree->insert("/boot", new File("settings.ini"));
			tree->insert("/boot", new File("some_file"));
			tree->insert("/boot", new File("other_file"));
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
			Assert::IsTrue(operator==(tree->getNode("/boot")->data, "boot"));
		}

		TEST_METHOD(InsertElementNotInRoot)
		{
			Assert::IsTrue(operator==(tree->getNode("/boot/settings.ini")->data, "settings.ini"));
		}

		TEST_METHOD(InsertNestedElement)
		{
			tree->insert("/boot/some_file", new File("nested"));
			Assert::IsTrue(operator==(tree->getNode("/boot/some_file/nested")->data, "nested"));
		}

		TEST_METHOD(IsElementInChildren)
		{
			for (DLList<TNode*>::Iterator iter = tree->getNode("/boot")->children.begin(); iter; ++iter)
				if (operator==((*iter)->data, "other_file"))
					return;

			Assert::IsTrue(false);
		}

		TEST_METHOD(IsParentCorrect)
		{
			Assert::IsTrue(operator==(tree->getNode("/boot/settings.ini")->parent->data, "boot"));
		}

		TEST_METHOD(RemoveElementNotRoot)
		{
			tree->remove("/boot/settings.ini");

			TNode* node = tree->getNode("/boot/settings.ini");
			Assert::IsNull(node);
		}

		TEST_METHOD(RemoveRoot)
		{
			bool caught = false;

			try
			{
				tree->remove("/");
			}
			catch (InvalidFileOperation &)
			{
				caught = true;
			}

			Assert::IsTrue(caught);
		}

		TEST_METHOD(RemoveWrongElement)
		{
			bool caught = false;

			try
			{
				tree->remove("/boot/fake");
			}
			catch (InvalidFilePath &)
			{
				caught = true;
			}

			Assert::IsTrue(caught);
		}
	};
}