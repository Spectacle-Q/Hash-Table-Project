#ifndef HASHFILE_H
#define HASHFILE_H

#include "Bucket.h"
#include <fstream>
#include "Record.h"
#include <iostream>
#include <string>

class HashFile {
private:
	std::string file;
	int N;
	const int STEP = 1;
	std::fstream hfile;
	int bucketCapacity;
	std::vector<int> bucketInfo;
	int linearProbing(int hash, int i);
	int hash(int id);
	bool instance;

public:
	HashFile(int n, int r) ;
	int store(Record rec);
	Record* retrieve(int id);
};

#endif