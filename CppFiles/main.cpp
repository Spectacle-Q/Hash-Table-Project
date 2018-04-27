#include "UnionFind.h"
#include "Graph.h"
#include "Edge.h"
#include "graphAlgorithm.h"
#include <fstream>
#include <iostream>
#include <tuple>
#include <time.h>

std::vector<std::tuple<int, int>> permute(int);
void generateMaze(Graph& graph, UnionFind& uft, int x);
std::vector<std::tuple<int, int>> internalWalls(int N);
void print(int cell1, int cell2);

int main() {
	system("color f0");
	std::cout << "\n\n";
	//part 1
	std::cout << "\t***PART ONE***\n";
	for (int i = 3; i <= 5; i++) {
		std::cout << "\t" << i << " x " << i << " - Maze" << std::endl;
		UnionFind* set = new UnionFind(i * i);
		Graph* graph = new Graph(i * i, false, false);
		std::stack<int> stack;
		generateMaze(*graph, *set, i);
		depthFirst(0, *graph, stack);
		int stackSize = stack.size();
		int* path = new int[stackSize];
		int index = stackSize - 1;

		while (!stack.empty()) {
			path[index--] = stack.top();
			stack.pop();
		}

		std::cout << "\n\tPath: ";
		for (int i = 0; i < stackSize; i++) {
			std::cout << path[i] << " ";
		}

		delete set;
		delete graph;
		delete path;

		std::cout << "\n\n";
	}

	// part 2
	std::cout << "\n\t***PART TWO***\n";
	std::ifstream file("Z:/Users/ChipperQ/Documents/Project4_Input.txt");
	int numVertices;
	file >> numVertices;
	Edge edge;
	std::vector<Edge> edges;
	int length = 1;

	while (file >> edge.vertex1 >> edge.vertex2 >> edge.weight) {
		edges.resize(length++, edge);
	}

	file.close();

	Graph MST = kruskalsAlgorithm(edges, numVertices);
	int sum = 0;
	int* sumPtr = &sum;
	bft(0, MST, sumPtr);
	int edgesSum = sum;

	std::cout << "\n\tSUM OF EDGES = " << edgesSum << "\n\n";

	system("pause");
	return 0;
}

void print(int cell1, int cell2) {
	std::cout << "(" << cell1 << ", " << cell2 << ")" << " ";
}

std::vector<std::tuple<int, int>> internalWalls(int N) {
	int length = 2 * (N*(N - 1));
	std::vector<std::tuple<int, int>> cells(length);
	for (int k = 0, j = 0; k < N*N - 1; k++, j++) {
		int x = k;
		if ((k % N == (N - 1))) {
			cells[j] = std::make_tuple(x, x + N);
		}
		else if (k >(N*N - N) - 1) {
			cells[j] = std::make_tuple(x, x + 1);
		}
		else {
			cells[j] = std::make_tuple(x, x + 1);
			x = k;
			cells[j + 1] = std::make_tuple(x, x + N);
			j++;
		}
	}
	return cells;
}

void generateMaze(Graph& graph, UnionFind& uft, int x) {
	std::vector<std::tuple<int, int>> sets = permute(x);
	int e1;
	int e2;

	bool* wallDown = new bool[sets.size()];

	for (int i = 0; i < sets.size(); i++) {
		e1 = uft.pcFind(std::get<0>(sets[i]));
		e2 = uft.pcFind(std::get<1>(sets[i]));

		if (e1 != e2) {
			uft.wUnion(e1, e2);
			Edge edge;
			edge.vertex1 = std::get<0>(sets[i]);
			edge.vertex2 = std::get<1>(sets[i]);
			edge.directed = false;
			edge.weighted = false;
			graph.addEdge(edge);
			wallDown[i] = true;
		}
		else {
			wallDown[i] = false;
		}


	}

	std::cout << "\tWALLS DOWN: ";
	for (int i = 0; i < sets.size(); i++) {
		if (wallDown[i]) {
			print(std::get<0>(sets[i]), std::get<1>(sets[i]));
		}
	}

	std::cout << "\n\tWALLS UP: ";
	for (int i = 0; i < sets.size(); i++) {
		if (!wallDown[i]) {
			print(std::get<0>(sets[i]), std::get<1>(sets[i]));
		}
	}

	delete wallDown;
}

std::vector<std::tuple<int, int>> permute(int x) {
	std::vector<std::tuple<int, int>> permCells = internalWalls(x);
	std::srand(time(NULL));
	std::random_shuffle(permCells.begin(), permCells.end());
	return permCells;
}