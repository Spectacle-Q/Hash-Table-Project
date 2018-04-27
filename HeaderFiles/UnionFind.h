#ifndef UnionFind_H
#define UnionFind_H

#include <vector>

class UnionFind {
private:
	int arraySize;
	std::vector<int> parent;
	std::vector<int> parentSize;
	

public:
	UnionFind(int n);
	void wUnion(int e1, int e2);
	int pcFind(int e);
	void printArray();
	int treeSize(int e);
};

#endif
