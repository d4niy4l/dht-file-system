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
	Bigint size; //made this so we done have to calculate the power (power function is expensive for bigint)
	CircularLinkedList<Machine> ring;
public:
	Ringdht(int s) : identifierspace(s), size(Bigint::power(2, s)) {}

	//the hash function, gets a string and hashes it using SHA1
	string hashFunction(string data) {
		SHA1 hasher;
		hasher.update(data);       
		return hasher.final();
	}

	//this is exclusivly if someone wants to hash files, it reads file in ios :: binary mode and returns a hash
	string hashFile(string path) {
		SHA1 hasher;
		return hasher.from_file(path);      
	}


	
	void insertFile(string path) {
		string filehash = hashFile(path);
		string binary = hexaToBinary(filehash);
		binary = getLastNBits(binary,identifierspace);
		Bigint id = binaryToDecimel(binary);

	}
	
	//This method will be called whenever we need the machine where we need to orignate a query (searching/deleting/insertion)
	Machine* getOrigin(Bigint& p) {
		//first step is to find the machine where the query will originate from
		//case 1: there is only one machine
		Machine* curr = &ring.head->data;
		if (ring.getHead() == ring.getHead()->next) {
			if (curr->getID() == p)
				return curr;
			cout << "MACHINE OF ID " << p << " DOES NOT EXIST IN FILE SYSTEM \n";
			return nullptr;
		}
		while (p != curr->getID()) {
			if (p > curr->getID() && p <= curr->RoutingTable.head->data->getID()) {
				curr = curr->RoutingTable.head->data;
				break;
			}
			dNode<Machine*>* ptr = curr->RoutingTable.head;
			while (ptr) {
				if (!ptr->next) {
					curr = ptr->data;
					break;
				}
				else if (p > ptr->data->getID() && p <= ptr->next->data->getID()) {
					curr = ptr->data;
					break;
				}
			}
		}
		if (p != curr->getID()) {
			cout << "MACHINE OF ID " << p << " DOES NOT EXIST IN FILE SYSTEM \n";
			return nullptr;
		}
		return curr;
	}

	//search the machine required for file insertion/searching/deletion
	Machine* searchMachine(Bigint& e, Bigint& p) {
		Machine* origin = getOrigin(p);
		if (!origin) return nullptr;

	}


	//inserts machine, gets machine name and autogenerates its id using SHA1
	//then converts hexa to binary and gets last n bits of it and changes it into decimel to make it an ID on which comparisons can
	// be done
	void insertMachine(string name) {
		string hex = hashFunction(name);
		string binary = hexaToBinary(hex);
		binary = getLastNBits(binary, identifierspace);
		Bigint id = binaryToDecimel(binary);
		Machine machine = Machine(id, name, 5);
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
				Bigint succ = (curr->data.getID() + Bigint::power(2,i)) % size;
				cNode<Machine>* searcher = curr->next;
				if (searcher->data.getID() > succ) searcher = ring.head;
				while(searcher->data.getID() < succ){
					if (searcher->next == ring.getHead() && succ > searcher->next->data.getID()) {
						searcher = searcher->next;
						break;
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
		Machine machine = Machine(Bigint(id), name, 5);
		ring.insertAscending(machine);
		makeRoutingTables();
	}
};

 

