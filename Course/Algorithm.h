#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Queue.h"
#include "RBtree.h"

using namespace std;

void TitlesInput(string fileName, RBtree<char, int>& names, int& source, int& sink) {
	fstream file;
	file.open(fileName, ios::in);
	if (!file.is_open()) 
		throw exception("File open error!");
	else {
		char vertex1, vertex2;
		int weight;
		int number = 0;
		while (!file.eof()) {
			file >> vertex1;
			file >> vertex2;
			file >> weight;
			if (!names.contains(vertex1)) {
				if (vertex1 == 'S') source = number;
				if (vertex1 == 'T') sink = number;
				names.insert(vertex1, number);
				number++;
			}
			if (!names.contains(vertex2)) {
				if (vertex2 == 'S') source = number;
				if (vertex2 == 'T') sink = number;
				names.insert(vertex2, number);
				number++;
			}

		}
	}
	file.close();
	if (source == -1 || sink == -1)
		throw exception("Wrong numbers!");
}

void input(string fileTitle, RBtree<char, int>& names, vector<vector<int>>& adjacencyMatrix) {
	fstream file;
	file.open(fileTitle, ios::in);
	if (!file.is_open()) throw exception("File open error!");
	else {
		char vertex1, vertex2;
		int weight;
		while (!file.eof()) {
			file >> vertex1;
			file >> vertex2;
			file >> weight;
			if (weight < 0) 
				throw exception("Wrong number!");
			int v1 = names.find(vertex1);
			int v2 = names.find(vertex2);
			adjacencyMatrix[v1][v2] = weight;
		}
	}
	file.close();
}

int ConnectionTest(vector<vector<int>>& Matrix, int s,
	vector<bool>& visited) {
	if (Matrix.size() == 0) 
		throw exception("Empty adjacency matrix!");

	int visitedVertices = 1;
	visited[s] = true;
	for (int i = 0; i < Matrix[s].size(); i++) {
		if (Matrix[s][i] > 0 && visited[i] == false) {
				visitedVertices += ConnectionTest(Matrix, i, visited);
		}
	}
	return visitedVertices;
}

bool bfs(vector<vector<int>>& graph, int start, int end, vector<int>& parent) {		//implements breadth-first search
	if (graph.size() == 0) 
		throw exception("Empty adjacency matrix!");

	vector<bool> visited(graph.size(), false);
	Queue<int> queue;
	queue.enqueue(start);
	visited[start] = true;
	parent[start] = -1;

	while (queue.size()!=0)
	{
		int u = queue.peek();
		queue.dequeue();

		for (int v = 0; v < graph.size(); v++)
		{
			if (visited[v] == false && graph[u][v] > 0)
			{
				queue.enqueue(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return (visited[end] == true);
}
	
int EdmondsKarp(vector<vector<int>>& Matrix, int start, int end)
{
	if (Matrix.size() == 0) 
		throw exception("Empty adjacency matrix!");

	vector<vector<int>> graph(Matrix);
	vector<int> parent(graph.size(), 0);
	int maxFlow = 0;

	while (bfs(graph, start, end, parent))
	{
		int wayFlow = INT_MAX;
		for (int v = end; v != start; v = parent[v])
		{
			int u = parent[v];
			wayFlow = min(wayFlow, graph[u][v]);
		}
		for (int v = end; v != start; v = parent[v])
		{
			int u = parent[v];
			graph[u][v] -= wayFlow;
			graph[v][u] += wayFlow;
		}
		maxFlow += wayFlow;
	}
	return maxFlow;
}