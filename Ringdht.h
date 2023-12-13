#include<iostream>
#include "utlity.h"
#include "Machine.h"
#include "SHA1.hpp"
#include "CircularList.h"
#include "BigInt.h"
using namespace std;

class Ringdht {
private:
	int identifierspace;
	Bigint size; //made this so we done have to calculate the power (power function is expensive for bigint)
	CircularLinkedList<Machine> ring;
	int order;
	string hashFunction(string data) {
		/*
			the hash function, gets a string and hashes it using SHA1
		*/
		SHA1 hasher;
		hasher.update(data);
		return hasher.final();
	}

	string hashFile(string path) {
		/*
			this is exclusivly if someone wants to hash files, it reads file in ios :: binary mode and returns a hash
		*/
		SHA1 hasher;
		return hasher.from_file(path);
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
				Bigint succ = (curr->data.getID() + Bigint::power(2, i)) % size;
				cNode<Machine>* searcher = curr->next;
				if (searcher->data.getID() > succ) searcher = ring.head;
				while (searcher->data.getID() < succ) {
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



public:
	//	CONSTRUCTOR
	Ringdht(int s, int order) : identifierspace(s), size(Bigint::power(2, s)), order(order) {}
	
	//GETTERS AND SETTERS FOR ORDER
	void setOrder(int n) {
		order = n;
	}
	int getOrder() {
		return order;
	}
	//	INSERTION
	void insertFile(string path, string MachineID) {
		string filehash = hashFile(path);
		string binary = hexaToBinary(filehash);
		binary = getLastNBits(binary, identifierspace);
		Bigint id = binaryToDecimel(binary);
		Bigint mid = MachineID;
		Machine* machine = searchMachine(id, mid);
		Key_Pair<File> keyvalue;
		keyvalue.insert(File(id, path));
		machine->tree.insert(keyvalue);
		cout << "HASH OF FILE: " << id << endl;
		cout << "FILE INSERTED AT MACHINE WITH ID: " << machine->getID() << endl;
		const Key_Pair<File>* ptr = &machine->tree.search(keyvalue);
		ptr->getList().print();
	}
	//This method will be called whenever we need the machine where we need to orignate a query (searching/deleting/insertion)
	Machine* getOrigin(const Bigint& p) {
		//first step is to find the machine where the query will originate from
		//case 1: there is only one machine
		/* 
		* IF ONLY ONE MACHINE AVALIABLE THEN CHECK IF P == MACHINE ID IF NOT
		* THEN IT IS AN INVALID ID FOR ORIGIN 
		*/
		Machine* curr = &ring.head->data;
		if (ring.getHead() == ring.getHead()->next) {
			if (curr->getID() == p)
				return curr;
			cout << "MACHINE OF ID " << p << " DOES NOT EXIST IN FILE SYSTEM \n";
			return nullptr;
		}

		// WHILE REQUIRED ID IS NOT REACHED
		while (p != curr->getID()) {
			// IF P > CURRENT MACHINE ID AND P IS >= TO THE HEAD OF ROUTING TABLE THEN SET IT TO THE HEAD OF THE ROUTING TABLR
			// THIS IS P > CURR MACHINE AND P <= FT [1]
			if (p > curr->getID() && p <= curr->RoutingTable.head->data->getID()) {
				curr = curr->RoutingTable.head->data;
				break; //EITHER MACHINE == P OR MACHINE > P (IF MACHINE > P) THEN MACHINE DOES NOT EXIST IN FILE SYSTEM
			}
			// TRAVERSE ROUTING TABLE
			dNode<Machine*>* ptr = curr->RoutingTable.head;
			while (ptr) {
				if (!ptr->next) {  // IF THERES NO NEXT THEN REROUTE TO THE LAST MEMBER OF THE FT
					curr = ptr->data;
					break;
				}
				else if (p > ptr->data->getID() && p <= ptr->next->data->getID()) { //CHECK IF FT[j] < P <= FT[j+1]
					curr = ptr->data;
					break;
				}
				ptr = ptr->next;
			}
		}
		// IF P < MACHINE ID
		if (p != curr->getID()) {
			cout << "MACHINE OF ID " << p << " DOES NOT EXIST IN FILE SYSTEM \n";
			return nullptr;
		}
		return curr;
	}
	//search the machine required for file insertion/searching/deletion
	Machine* searchMachine(const Bigint& fileHash, const Bigint& machineHash) {
		Machine* origin = getOrigin(machineHash);
		if (!origin) {
			cout << "Machine does not exist in filesystem!\n";
			return nullptr;
		}
		Machine* ret = nullptr;
		Machine* curr = origin;
		Machine* currMin = nullptr;
		Machine* currLast = nullptr;
		Bigint currId = curr->getID();
		Bigint startId = currId;
		bool nodeFound = false;
		bool c1 = false;
		bool c2 = false;
		bool c3 = false;
		int count = 0;
		while (!nodeFound) {
			currId = curr->getID();

			//	(P == E) || (E <= P && P is machine with smallest id) || (E >= max Machine id and P is smaalest machine node)
			if ((currId == fileHash) || (currId >= fileHash && currId == ring.getHead()->data.getID() || (fileHash >= ring.head->prev->data.getID() && currId == ring.getHead()->data.getID()))) {
				ret = curr;
				c1 = true;
				return ret;
			}
			//	P < E && E < FTP[1]
			else if (currId < fileHash && fileHash <= curr->getRoutingTable().head->data->getID()) {
				curr = curr->getRoutingTable().head->data;
				c2 = true;
			}
			//	CHECK ALL ENTRIES IN ROUTING TABLE
			else {
				bool validEntry = false;
				Machine* prev = curr->getRoutingTable().head->data;
				Machine* curr1 = curr->getRoutingTable().head->next->data;
				dNode<Machine*>* currNode = curr->getRoutingTable().head;
				currNode = currNode->next;
				Machine* minM = nullptr;
				Machine* maxM = nullptr;
				while (currNode) {
					if (fileHash > prev->getID() && fileHash <= curr1->getID()) {
						validEntry = true;
						break;
					}
					else {
						prev = curr1;
						if (!minM || prev->getID() < minM->getID()) {
							minM = prev;
						}
						if (!maxM || prev->getID() > maxM->getID()) {
							maxM = prev;
						}
						currNode = currNode->next;
						if (currNode) {
							curr1 = currNode->data;
						}
					}

				}
				if (validEntry) {
					curr = prev;
				}
				if ((!validEntry && fileHash <= ring.head->data.getID()) || (!validEntry && fileHash > ring.head->prev->data.getID())) {
					if (minM->getID() == ring.getHead()->data.getID()) {
						curr = minM;
						return curr;
					}
					else {
						curr = maxM;
						validEntry = true;
					}
				}
				else if (!validEntry && fileHash <= ring.head->prev->data.getID()) {
					if (fileHash > curr->getID()) {
						if (curr->getID() < prev->getID()) {
							if (prev->getID() < fileHash) {
								curr = prev;
								validEntry = true;
							}
						}
					}
					else {
						currMin = minM;
					}
				}
				if (validEntry) {
					c3 = true;
				}
				else {
					currLast = prev;
				}
			}



			if (c1 || c2 || c3) {
				c1 = false;
				c2 = false;
				c3 = false;
			}
			else if (!c1 && !c2 && !c3) {
				/*if ((fileHash > curr->getRoutingTable().head->data->getID() && fileHash > currLast->getID()) || (fileHash < curr->getRoutingTable().head->data->getID() && fileHash < currLast->getID())) {
					return curr;
				}else{
					curr = currLast;
				}
				*/
				if (startId == curr->getID() && count == 0) {
					curr = currLast;
					count++;
				}
				else {
					return curr;
				}
			}

		}

	}

	//inserts machine, gets machine name and autogenerates its id using SHA1
	//then converts hexa to binary and gets last n bits of it and changes it into decimel to make it an ID on which comparisons can
	// be done
	void insertMachine(string name) {
		string hex = hashFunction(name);
		string binary = hexaToBinary(hex);
		binary = getLastNBits(binary, identifierspace);
		Bigint id = binaryToDecimel(binary);
		Machine machine = Machine(id, name, order);
		ring.insertAscending(machine);
		makeRoutingTables();
	}
	void removeMachine(Bigint& id) {
		string name = "DELETED MACHINE";
		ring.remove(Machine(id, name, order));
		makeRoutingTables();
	}
	void insertMachine(string name, string id) { //incase user wants to give their own id
		Bigint sid = id;
		Machine machine = Machine(sid, name, order);
		ring.insertAscending(machine);
		makeRoutingTables();
	}


	void removeFile(string fileHash, string mid) {
		Machine* m = searchMachine(Bigint(fileHash), mid);
		m->removeFile(fileHash);
	}

	void showRoutingTables() {
		cNode<Machine>* curr = ring.getHead();
		do {
			curr->data.showRoutingTable();
			curr = curr->next;
		} while (curr != ring.getHead());
	}

};