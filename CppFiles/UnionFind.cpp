#include "UnionFind.h"
#include <iostream>

UnionFind::UnionFind(int n) {
	arraySize = n;
	parent.resize(arraySize);
	parentSize.resize(arraySize);
	for (int k = 0; k < arraySize; k++) {
		parent[k] = -99;
		parentSize[k] = 1;
	}
}

void UnionFind::wUnion(int e1, int e2) {
	int x = pcFind(e1);
	int y = pcFind(e2);

	if (x != y) {
		if (parentSize[x] >= parentSize[y]) {
			parent[y] = x;
			parentSize[x] += parentSize[y];
		}
		else {
			parent[x] = y;
			parentSize[y] += parentSize[x];
		}
	}
}

int UnionFind::pcFind(int e) {
	std::vector<int> compression;
	int p;
	int counter = 0;
	while ((p = parent[e]) != -99) {
		compression.resize(++counter, e);
		e = p;
	}
	if (counter != 0) {
		for (int k = 0; k < compression.size(); k++) {
			parent[compression[k]] = e;
		}
	}
	
	return e;
}

void UnionFind::printArray() {
	for (int k = 0; k < arraySize; k++) {
		if (k < arraySize - 1) {
			std::cout << "[" << k << "] = " << parent[k] << ",\n";
		}
		else {
			std::cout << "[" << k << "] = " << parent[k] << std::endl;
		}
	}
}
