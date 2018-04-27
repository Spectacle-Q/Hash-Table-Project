#include "graphAlgorithm.h"

Graph kruskalsAlgorithm(const std::vector<Edge>& edges, int N) {
	UnionFind T(N*N);
	Graph MST(N, false, true);
	std::priority_queue<int, std::vector<Edge>, Comparator> queue;
	for (int i = 0; i < edges.size(); i++) {
		queue.push(edges[i]);
	}
	int e1;
	int e2;
	std::cout << "\tEdges: ";
	for (int i = 0; i < edges.size(); i++) {
		e1 = T.pcFind(queue.top().vertex1);
		e2 = T.pcFind(queue.top().vertex2);
		if (e1 != e2) {
			std::cout << "(" << queue.top().vertex1 << ", " << queue.top().vertex2 << ") ";
			T.wUnion(e1, e2);
			MST.addEdge(queue.top());

		}
		queue.pop();
	}
	return MST;
}

void bft(int start, const Graph& graph, int* sum) {
	int size = graph.getNumVertices();
	std::vector<bool> visited(size);
	for (size_t k = 0; k < size; k++) {
		visited[k] = false;
	}

	visited[start] = true;

	std::queue<int> Q;
	std::list<Edge>::iterator it;

	Q.push(start);

	while (Q.size() > 0) {
		start = Q.front();
		Q.pop();

		std::list<Edge> adjList = graph.getAdjacentList(start);
		for (it = adjList.begin(); it != adjList.end(); it++) {
			if (it->vertex1 < it->vertex2) {
				(*sum) += it->weight;
			}
			if (visited[it->vertex2]) continue;
			visited[it->vertex2] = true;
			Q.push(it->vertex2);
		}
	}
}

void depthFirst(int start, const Graph& graph, std::stack<int>& stack) {
	int size = graph.getNumVertices();
	std::vector<bool> visited(size);
	for (size_t k = 0; k < size; k++) {
		visited[k] = false;
	}
	bool done = false;
	int end = size - 1;
	int tracker = 0;
	RDFS(start, graph, stack, visited, done, end, tracker);
}

void RDFS(int start, const Graph& graph, std::stack<int>& stack, std::vector<bool>& visited, bool& done, int& end, int& tracker) {
	if (start == end) { done = true; }
	pre_visit(start, stack, done, end, tracker);
	visited[start] = true;

	std::list<Edge>::iterator it;
	std::list<Edge> adjList = graph.getAdjacentList(start);
	for (it = adjList.begin(); it != adjList.end(); it++) {
		if (visited[it->vertex2]) { continue; }
		RDFS(it->vertex2, graph, stack, visited, done, end, tracker);
	}

	if (!done) { stack.pop(); }
}

void pre_visit(int start, std::stack<int>& stack, bool& done, int& end, int& tracker) {
	if (done && tracker > 0) { return; }
	else {
		if (start == end) { tracker++; }
		stack.push(start);
	}
}
