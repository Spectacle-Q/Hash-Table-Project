#include "Graph.h"
#include <stdexcept>

Graph::Graph(int n, bool directed, bool weighted) {
	numVertices = n;
	this->directed = directed;
	this->weighted = weighted;
	vertices.resize(n);
}

void Graph::addEdge(Edge e) {
	numEdges++;
	if (!directed) {
		vertices[e.vertex1].push_back(e);
		swapVertices(e);
		vertices[e.vertex1].push_back(e);
	}
	else {
		vertices[e.vertex1].push_back(e);
	}
}

std::list<Edge> Graph::getAdjacentList(int v) const{
	return vertices[v];
}

Edge Graph::getEdge(int v1, int v2) const {
	if ((v1 < 0 || v2 < 0) || (v1 > numVertices || v2 > numVertices)) {
		throw std::out_of_range("List : vertex/vertices out of bounds");
	}

	std::list<Edge> edgeList = vertices[v1];

	for (std::list<Edge>::iterator it = edgeList.begin(); it != edgeList.end(); it++) {
		if (it->vertex1 == v1 && it->vertex2 == v2) {
			return *it;
		}
	} 

	throw std::out_of_range("Graph : edge doesn\'t exist");
}

int Graph::getNumVertices() const {
	return numVertices;
}

int Graph::getNumEdges() const {
	return numEdges;
}

bool Graph::isDirected() const {
	return directed;
}

bool Graph::isWeighted() const {
	return weighted;
}

void Graph::swapVertices(Edge& edge) {
	Edge temp = edge;
	temp.vertex1 = edge.vertex1;
	edge.vertex1 = edge.vertex2;
	edge.vertex2 = temp.vertex1;
}