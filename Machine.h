
#pragma once
#include <iostream>
#include <string>
#include "DoubleList.h"
#include "BigInt.h"
#include "Btree.h"
#include "SHA1.hpp"
#include "Key_Pair.h"
using namespace std;
class Machine {
	Bigint id;
	string name;

public:
	BTree<Key_Pair<File>> tree;
	DoublyLinkedList<Machine*> RoutingTable;   
	Machine(Bigint& id,string name, int order) : name(name), id(id), tree(order) {}
	void printDetails() {
		cout << "MACHINE NAME: " << name << ", ";
		cout << "MACHINE ID: " << id << endl;
	}
	const DoublyLinkedList<Machine*>& getRoutingTable() {
		return RoutingTable;
	}
	void showRoutingTable() {
		printDetails();
		cout << "CONNECTED TO: " << endl;
		dNode<Machine*>* ptr = RoutingTable.getHead();
		while (ptr) {
			ptr->data->printDetails();
			ptr = ptr->next;
		}
		cout << endl;
	}

	Bigint getID() {
		return id;
	}
	
		
	//	FILE FUNCTIONS
	void removeFile(const string& filehash) {
		cout << "reached" << this->getID()<< "!\n";
		Bigint key(filehash);
		Key_Pair<File> pair(key);
		Key_Pair<File> keyPair = tree.search(pair);
		File f(key, "abc");
		for (int i = 0; i < keyPair.getList().size(); i++) {
			string fileName = keyPair.getList().getHead().getFilename();
			f.setFilename(fileName);
			cout << i + 1 << ". " << keyPair.getList().getHead().getFilename();
			keyPair.remove(f);
		}
		cout << "Enter indexes (comma-seperated) of the files to remove: ";
		string response;
		getline(cin, response);
	}
	
	//	COMPARISON OPERATORS OVERLOADED
	bool operator < (const Machine& m) {
		return id < m.id;
	}
	bool operator > (const Machine& m) {
		return id > m.id;
	}
	bool operator == (const Machine& m) {
		return id == m.id;
	}
	bool operator <= (const Machine& m) {
		return id <= m.id;
	}
	bool operator >= (const Machine& m) {
		return id >= m.id;
	}
	bool operator != (const Machine& m) {
		return id != m.id;
	}
};