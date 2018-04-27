#ifndef graphAlgorithm_H
#define graphAlgorithm_H

#include "Graph.h"
#include "UnionFind.h"
#include "Edge.h"
#include <queue>
#include "Comparator.h"
#include <iostream>
#include <stack>
#include <iterator>

void depthFirst(int start, const Graph& graph, std::stack<int>& stack);
void RDFS(int start, const Graph& graph, std::stack<int>& stack, std::vector<bool>& visited, bool& done, int& end, int& tracker);
void pre_visit(int start, std::stack<int>& stack, bool& done, int& end, int& tracker);
Graph kruskalsAlgorithm(const std::vector<Edge>& edges, int N);
void bft(int start, const Graph& graph, int* sum);

#endif
