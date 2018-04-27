#include "Bucket.h"
#include <fstream>
#include <iostream>

Bucket Bucket::update(Record rec) {
	this->records[recordPosition] = rec;
	return *this;
}

void Bucket::writeToFile(std::fstream& file, Record rec, int bucketNumber, int bucketCap, bool newInstance) { 
	if (newInstance) {
		file.write((char*)&(*this), sizeof(Bucket));
	}
	else {
		int byteOffset = calcByteOffset(bucketNumber, sizeof(Record), bucketCap);
		Bucket updatedBucket = readFromFile(file, bucketNumber, bucketCap);
		updatedBucket.update(rec);
		file.seekp(byteOffset, file.beg);
		file.write((char*)&(updatedBucket), sizeof(Bucket));
	}
}

int Bucket::calcByteOffset(int bucketNumber, int recordLength, int bucketCap) {
	return bucketNumber * recordLength * bucketCap;
}

Bucket Bucket::readFromFile(std::fstream& file, int bucketNumber, int bucketCap) {
	Bucket bucket;
	int byteOffset = calcByteOffset(bucketNumber, sizeof(Record), bucketCap);
	file.seekg(byteOffset, file.beg);
	file.read((char*)&(bucket), sizeof(Bucket));
	return bucket;
}


