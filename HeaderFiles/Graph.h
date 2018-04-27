#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <list>
#include <vector>

class Graph {
private:
	std::vector<std::list<Edge>> vertices;
	bool directed;
	bool weighted;
	int numEdges = 0;
	int numVertices = 0;
	void swapVertices(Edge& edge);

public:
	Graph(int n, bool directed, bool weighted);
	void addEdge(Edge e);
	std::list<Edge> getAdjacentList(int v) const;
	Edge getEdge(int v1, int v2) const;
	int getNumVertices() const;
	int getNumEdges() const;
	bool isDirected() const;
	bool isWeighted() const;
};

#endif

