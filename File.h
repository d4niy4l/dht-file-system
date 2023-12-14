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
	File(Bigint hash, string Newpath, string path) : hash(hash), path(Newpath){
		name = "FILE_"+ hash.str();
		ext = getFileExtension(path);
	}

	const string& getFilename() const {
		return (this->name);
	}

	const string& getExtension() const {
		return (this->ext);
	}

	const string& getPath() const {
		return this->path;
	}

	void setPath(const string& _path) {
		path = _path;
	}
	void setExtension(const string& _ext) {
		ext = _ext;
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
		cout << "PATH: " << file.path + "/" + file.name + file.ext << endl;
		return out;
	}
};