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
	string ext;
public:
	File(Bigint hash, string path) : hash(hash), path(path){
		name = getNameFromPath(path);
		ext = getFileExtension(path);
		for (int i = 0; i < ext.size(); i++) {
			name.pop_back();
		}
	}

	const string& getFilename() const {
		return (this->name);
	}
	
	void setFilename(const string& _name) {
		name = _name;
	}

	bool operator == (const File& other) const {
		return (hash == other.hash && name == other.name);
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
		cout << "NAME: " << file.name << file.ext << endl;;
		cout << "PATH: " << file.path << endl;
		return out;
	}
};