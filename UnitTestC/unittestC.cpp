#include"stdafx.h"
#include "CppUnitTest.h"
#include "../Course/Algorithm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMaximumFlow
{
	TEST_CLASS(UnitTestMaximumFlow)
	{
		string file = "../Course/test.txt";
	public:

		TEST_METHOD(test_TitlesInput)
		{
			RBtree<char, int> titles;
			int start, end;
			TitlesInput(file, titles, start, end);
			Assert::IsTrue(titles.get_size() != 0);
		}

		TEST_METHOD(test_input)
		{
			RBtree<char, int> titles;
			int start, end;
			TitlesInput(file, titles, start, end);
			vector<vector<int>> Matrix(titles.get_size(), vector<int>(titles.get_size(), 0));
			input(file, titles, Matrix);
			Assert::IsTrue(Matrix.size() != 0);
		}

		TEST_METHOD(test_ConnectionTest)
		{
			vector<vector<int>> Matrix(3, vector<int>(3, 0));
			vector<bool> visited(3, false);
			int start = 0;
			Matrix[0][1] = 1;
			Matrix[1][2] = 1;
			Assert::IsTrue(ConnectionTest(Matrix, start, visited) == 3);
		}

		TEST_METHOD(test_ExcepConnectionTest)
		{
			try {
				vector<vector<int>> Matrix(0);
				vector<bool> visited(0);
				int test = ConnectionTest(Matrix, 0, visited);
			}
			catch (exception error) {
				Assert::AreEqual(error.what(), "Empty adjacency matrix!");
			}
		}

		TEST_METHOD(test_bfs)
		{
			vector<vector<int>> Matrix(3, vector<int>(3, 0));
			vector<int> parent(3, 0);
			int start = 0;
			int end = 2;
			Matrix[0][1] = 1;
			Matrix[1][2] = 1;
			Assert::IsTrue(bfs(Matrix, start, end, parent));
		}

		TEST_METHOD(test_excepBFS)
		{
			try {
				vector<vector<int>> Matrix(0);
				vector<int> parent(0);
				bool test = bfs(Matrix, 0, 0, parent);
			}
			catch (exception error) {
				Assert::AreEqual(error.what(), "Empty adjacency matrix!");
			}
		}
		TEST_METHOD(test_EdmondsKarp) {
			string file("../Course/test.txt");
			RBtree<char, int> titles;
			int start = -1, end = -1;
			TitlesInput(file, titles, start, end);
			vector<vector<int>> Matrix(titles.get_size(), vector<int>(titles.get_size(), 0));
			input(file, titles, Matrix);
			vector<bool> visited(titles.get_size(), false);
			int maxFlowEK = EdmondsKarp(Matrix, start, end);
			Assert::AreEqual(5, maxFlowEK);
		}
		TEST_METHOD(test_ExcepEdmondsKarp) {
			try {
				vector<vector<int>> Matrix(0);
				int maxFlow =EdmondsKarp(Matrix, 0, 0);
			}
			catch (exception error) {
				Assert::AreEqual(error.what(), "Empty adjacency matrix!");
			}
		}
	};
}