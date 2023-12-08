#pragma once
#include<iostream>
#include "BigInt.h"
#include "LinkedList.h"
using namespace std;
class File {
	Bigint hash;
	string path;
	string name;
public:
	File(Bigint hash, string path, string name) : hash(hash), path(path){}
	bool operator == (const File& other) const {
		return hash == other.hash;
	}
	bool operator != (const File& other) const {
		return hash != other.hash;
	}
	bool operator > (const File& other) const {
		return hash > other.hash;
	}
	bool operator >= (const File& other) const {
		return hash >= other.hash;
	}
	bool operator < (const File& other) const {
		return hash < other.hash;
	}
	bool operator <= (const File& other) const {
		return hash <= other.hash;
	}
};