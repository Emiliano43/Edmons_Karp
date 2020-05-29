#include "Algorithm.h"

using namespace std;

int main() {
	string file("Network.txt");
	RBtree<char, int> titles;
	int start = -1, end = -1;
	TitlesInput(file, titles, start, end);
	vector<vector<int>> Matrix(titles.get_size(), vector<int>(titles.get_size(), 0));
	input(file, titles, Matrix);
	vector<bool> visited(titles.get_size(), false);

	if (ConnectionTest(Matrix, start, visited) != titles.get_size()) {
		cout << "Incorrect graph(network)!" << endl;
	}
	else {
		int maxFlowEK = EdmondsKarp(Matrix, start, end);
		cout << "Max flow of this network: " << maxFlowEK << endl;
	}
	system("pause");
	return 0;
}