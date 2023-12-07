#pragma once
#include<iostream>
#include "utlity.h"
#include "Machine.h"
#include "SHA1.hpp"
#include "CircularList.h"
#include "BigInt.h"
using namespace std;

class Ringdht {
	int identifierspace;
	Bigint size;
	CircularLinkedList<Machine> ring;
public:
	Ringdht(int s) : identifierspace(s), size(Bigint::power(2, s)) {}
	string hashFunction(string data) {
		SHA1 hasher;
		hasher.update(data);
		return hasher.final();
	}

	void insertMachine(string name) {
		string hex = hashFunction(name);
		string binary = hexaToBinary(hex);
		binary = getLastNBits(binary, identifierspace);
		Bigint id = binaryToDecimel(binary);
		Machine machine = Machine(id, name);
		ring.insertAscending(machine);
		makeRoutingTables();
	}
	void makeRoutingTables() {
		if (ring.head->next == ring.head) {
			ring.head->data.RoutingTable.clear();
			return;
		}
		cNode<Machine>* curr = ring.getHead();
		do {
			curr->data.RoutingTable.clear();
			for (int i = 0; i < identifierspace; i++) {
				Bigint succ = curr->data.getID() + Bigint::power(2,i);
				bool fullcircle = false;
				cNode<Machine>* searcher = curr->next;
				while(searcher->data.getID() < succ){
					if (searcher == ring.getHead()) {
						succ -= size;
						if (searcher->data.getID() >= succ) break;
					}
					searcher = searcher->next;
				}
				curr->data.RoutingTable.insert(&searcher->data);
			}
			curr = curr->next;

		} while (curr != ring.getHead());
	}
	void showRoutingTables() {
		cNode<Machine>* curr = ring.getHead();
		do {
			curr->data.showRoutingTable();
			curr = curr->next;
		} while (curr != ring.getHead());
	}
	void insertMachine(string name, string id) { //incase user wants to give their own id
		Machine machine = Machine(Bigint(id), name);
		ring.insertAscending(machine);
		makeRoutingTables();
	}
};