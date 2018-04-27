#include "HashFile.h"

HashFile::HashFile(int n, int r) {
	instance = true;
	file = "data.txt";
	hfile.open(file, std::ios::out | std::ios::binary);
	Bucket bucket;
	N = n;
	bucketCapacity = r;
	bucketInfo.resize(N);
	if (hfile) {
		bucket.records.resize(bucketCapacity);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < bucketCapacity; j++) {
				bucket.records[j].id = 0;
			}
			Record nullRec;
			bucketInfo[i] = 0;
			bucket.writeToFile(hfile, nullRec, i, bucketCapacity, instance);
		}
		hfile.close();
		instance = false;
	}
}

int HashFile::store(Record rec) {
	int i = 0;
	int bucketNumber = linearProbing(hash(rec.id), i++);
	int probe = bucketNumber;
	bool availability = false;
	Bucket tempBucket;
	while (!availability) {
		if (bucketInfo[probe] == bucketCapacity) {
			probe = linearProbing(probe, i++);
		}
		else {
			availability = true;
			bucketNumber = probe;
		}
	}
	hfile.open(file, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
	tempBucket.recordPosition = bucketInfo[bucketNumber];
	tempBucket.writeToFile(hfile, rec, bucketNumber, bucketCapacity, false);
	bucketInfo[bucketNumber]++;
	hfile.close();
	
	return bucketNumber;
}

int HashFile::linearProbing(int hash, int i) {
	return ((hash + (i * 1)) % 7);
}

int HashFile::hash(int id) {
	return id % N;
}

Record* HashFile::retrieve(int id) {
	int i = 0;
	int bucketNumber = linearProbing(id, i++);
	Record* record = NULL;
	while(true) {
		Bucket bucket;
		bucket.readFromFile(hfile, bucketNumber, bucketCapacity);
		for (int i = 0; i < bucket.records.size(); i++) {
			if (bucket.records[0].id == id) {
				record = &bucket.records[i];
				return record;
			}
		}
		return record;
	}
	
}
