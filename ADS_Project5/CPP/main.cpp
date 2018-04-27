#include "Record.h"
#include <iostream>
#include "HashFile.h"

int main() {
	Record item;
	int numOfBuckets, bucketCap;
	std::cout << "Number of Buckets: ";
	std::cin >> numOfBuckets;
	std::cout << "Bucket Size: ";
	std::cin >> bucketCap;
	HashFile hfile(numOfBuckets, bucketCap);
	Record records[11];
	std::cout << "---Enter Data---" << std::endl;
	std::cout << "Record: ";

	while (true) {
		std::cin >> item.id;
		if (item.id == 0) {
			break;
		}
		std::cin >> item.name;
		int bucketNum = hfile.store(item);
		std::cout << "id: " << item.id << " | name: " << item.name;
		std::cout << " - bucket #: " << bucketNum << std::endl;
		std::cout << "Record: ";
	}

	std::cout << "id: ";	
	int id;
	while(true) {
		std::cin >> id;
		if (id == 0) {
			break;
		}
		Record* record = hfile.retrieve(item.id);
		if (!record) {
			std::cout << "id: " << item.id << " Not Found\n";
		}
		else {
			std::cout << "id: " << record->id << " | name: " << record->name << std::endl;
		}
		std::cout << "id: ";
	}
}