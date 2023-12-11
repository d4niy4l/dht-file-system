#pragma once
#include<iostream>
#include "BigInt.h"
#include "LinkedList.h"
#include "utlity.h"
using namespace std;
class File {
	Bigint hash;
	string path;
	string name;
public:
	File(Bigint hash, string path) : hash(hash), path(path){
		name = getNameFromPath(path);
	}
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
	friend ostream& operator << (ostream& out, const File& file) {
		out << "FILE DETAILS: " << endl;
		cout << "ID: " << file.hash << endl;
		cout << "NAME: " << file.name << endl;;
		cout << "PATH: " << file.path << endl;
		return out;
	}
};