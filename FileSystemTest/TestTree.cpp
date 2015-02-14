#include "CppUnitTest.h"

#include "../FileSystem/FileSystem.h"
#include "../FileSystem/FileSystemException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DirectorySystemTest
{		
	TEST_CLASS(TestTree)
	{
	public:
		Tree* tree;

		TEST_METHOD_INITIALIZE(SetUp)
		{
			tree = new Tree();
			tree->setRoot();

			tree->insert("/", new Directory("boot"));
			tree->insert("/boot", new File("settings.ini"));
			tree->insert("/boot", new Directory("some_Directory"));
			tree->insert("/boot", new Directory("other_Directory"));
		}

		TEST_METHOD_CLEANUP(TearDown)
		{
			delete tree;
		}

		TEST_METHOD(IsRootPresent)
		{
			Assert::IsTrue(tree->getNode("/")->data->getName() == "/");
		}

		TEST_METHOD(InsertingElementInRoot)
		{
			Assert::IsTrue(tree->getNode("/boot")->data->getName() == "boot");
		}

		TEST_METHOD(InsertElementNotInRoot)
		{
			Assert::IsTrue(tree->getNode("/boot/settings.ini")->data->getName() == "settings.ini");
		}

		TEST_METHOD(InsertNestedElement)
		{
			tree->insert("/boot/some_Directory", new Directory("nested"));
			Assert::IsTrue(tree->getNode("/boot/some_Directory/nested")->data->getName() == "nested");
		}

		TEST_METHOD(IsElementInChildren)
		{
			for (DLList<TNode*>::Iterator iter = tree->getNode("/boot")->children.begin(); iter; ++iter)
				if ((*iter)->data->getName() == "other_Directory")
					return;

			Assert::IsTrue(false);
		}

		TEST_METHOD(IsParentCorrect)
		{
			Assert::IsTrue(tree->getNode("/boot/settings.ini")->parent->data->getName() == "boot");
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

		TEST_METHOD(SerializeAndDeserialize)
		{
			std::fstream stream("ser_test.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
			if (!stream)
				throw - 1;

			tree->serialize(stream);
			stream.flush();

			Tree other;
			other.deserialize(stream, 0);

			Assert::IsTrue(other.getNode("/")->data->getName() == "/");
			Assert::IsTrue(other.getNode("/boot")->data->getName() == "boot");
			Assert::IsTrue(other.getNode("/boot/settings.ini")->data->getName() == "settings.ini");
			Assert::IsTrue(other.getNode("/boot/some_Directory")->data->getName() == "some_Directory");
			Assert::IsTrue(other.getNode("/boot/other_Directory")->data->getName() == "other_Directory");

			stream.close();
		}

	};

}