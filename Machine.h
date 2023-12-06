
#pragma once
#include <iostream>
#include <string>
#include "DoubleList.h"
#include "BigInt.h"
#include "SHA1.hpp"
using namespace std;
class Machine {
	Bigint id;
	string name;
	public:
	DoublyLinkedList<Machine*> RoutingTable;
	Machine(Bigint id,string name) : name(name), id(id) {}
	void printDetails() {
		cout << "MACHINE NAME: " << name << ", ";
		cout << "MACHINE ID: " << id << endl;
	}
	Machine* reroute(long long int key) {
		
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