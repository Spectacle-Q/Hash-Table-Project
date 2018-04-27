#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Edge.h"

class Comparator {
public:
	bool operator() (const Edge& e1, const Edge& e2) {
		return e1.weight > e2.weight;
	}
};

#endif