
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
	Machine(Bigint id,string name, int order) : name(name), id(id), tree(order) {}
	void printDetails() {
		cout << "MACHINE NAME: " << name << ", ";
		cout << "MACHINE ID: " << id << endl;
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