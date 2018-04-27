#ifndef BUCKET_H
#define BUCKET_H

#include "Record.h"
#include <vector>

class Bucket {
private:
	int calcByteOffset(int bucketNumber, int recordLength, int bucketCap);
	Bucket update(Record rec);

public:
	Bucket readFromFile(std::fstream& file, int bucketNumber, int bucketCap);
	std::vector<Record> records;
	void writeToFile(std::fstream& file, Record rec, int bucketNumber, int bucketCap, bool instance);
	int recordPosition;
};

#endif