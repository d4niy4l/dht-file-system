#include<iostream>
#include "utlity.h"
#include "Machine.h"
#include "SHA1.hpp"
#include "CircularList.h"
#include "BigInt.h"
#include <fstream>
#include <Windows.h>
#include <direct.h>
using namespace std;

class Ringdht {
private:
	Bigint maxMachines;
	Bigint currMachines;
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
					if (ptr->data == curr || ptr->data->getID() < p) {
						curr = curr->RoutingTable.head->data;
						break;
					}
					curr = ptr->data;
					break;
				}
				else if (p == ptr->next->data->getID()) {
					curr = ptr->next->data;
					return curr;
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
public:
	//	CONSTRUCTOR
	Ringdht(int s, int order, Bigint max = 10)
		: identifierspace(s), size(Bigint::power(2, s)), order(order), maxMachines(max), currMachines(0){
		auto ret = _mkdir("./IPFS");
	}
	
	//GETTERS AND SETTERS FOR ORDER
	void setOrder(int n) {
		order = n;
	}
	int getOrder() {
		return order;
	}

	void setMaxMachines(Bigint& n) {
		maxMachines = n;
	}
	const Bigint& getMaxMachines() {
		return maxMachines;
	}

	//	INSERTION
	void insertFile(string path, string MachineID) {
		string filehash = hashFile(path);
		string binary = hexaToBinary(filehash);
		binary = getLastNBits(binary, identifierspace);
		Bigint id = binaryToDecimel(binary);
		Bigint mid = MachineID;
		Machine* machine = searchMachine(id, mid);
		machine->insertFile(id, path);
	}
	//This method will be called whenever we need the machine where we need to orignate a query (searching/deleting/insertion)
	
	//search the machine required for file insertion/searching/deletion
	Machine* searchMachine(const Bigint& fileHash, const Bigint& machineHash)  {
		Machine* origin = getOrigin(machineHash);
		if (!origin) {
			cout << "Machine does not exist in filesystem!\n";
			return nullptr;
		}
		Machine* ret = nullptr;
		Machine* curr = origin;
		Machine* currMin = nullptr;
		Machine* currMax = nullptr;
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
			if ((currId == fileHash) || (currId >= fileHash && currId == ring.getHead()->data.getID() || (fileHash > ring.head->prev->data.getID() && currId == ring.getHead()->data.getID()))) {
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
						currMax = maxM;
					}
				}
				if (validEntry) {
					c3 = true;
				}
				else {
					currLast = prev;
				}
					currMin = minM;
					currMax = maxM;
			}

			if (c1 || c2 || c3) {
				c1 = false;
				c2 = false;
				c3 = false;
			}
			else if (!c1 && !c2 && !c3) {
				if (startId == curr->getID() && count == 0) {
					curr = currLast;
					count++;
				}
				else {
					if (curr->getID() < fileHash) {
						curr = currMax;
					}else{
						return curr;
					}
				}
			}

		}

	}

	//inserts machine, gets machine name and autogenerates its id using SHA1
	//then converts hexa to binary and gets last n bits of it and changes it into decimel to make it an ID on which comparisons can
	// be done
	void insertMachine(const string& mName) {
		if (currMachines >= maxMachines) {
			cout << "MAX NUMBER OF MACHINES REACHED \n";
			return;
		}
		string hex = hashFunction(mName);
		string binary = hexaToBinary(hex);
		binary = getLastNBits(binary, identifierspace);
		Bigint id = binaryToDecimel(binary);
		Machine machine = Machine(id, mName, order);
		ring.insertAscending(machine);
		makeRoutingTables();
		
		Machine* newMachine = getOrigin(id);
		Machine* nextMachine = newMachine->getRoutingTable().head->data;
		//	ONLY SPLIT TREES IF THE NEXT MACHINE EXISTS - IF ONLY ONE MACHINE THEN NO SPLITTING SHOULD BE THERE
		if (nextMachine) {
			nextMachine->splitTree(id, newMachine);

			//	TODO: ALSO MOVE FILE FOLDERS TO OTHER MACHINE
		}

		string path = "./IPFS/MACHINE" + machine.getID().str();
		auto ret = _mkdir(path.c_str());
		++currMachines;
	}
	void removeMachine(Bigint& id) {
		if (currMachines == 0) {
			cout << "NO MACHINE PRESENT IN FILE SYSTEM \n";
			return;
		}
		string name = "DELETED MACHINE";
		Machine* machine = getOrigin(id);
		if (!machine) {
			cout << "PLEASE SELECT AN EXISTING MACHINE"<<endl;
			return;
		}
		dNode<Machine*>* next = machine->getRoutingTable().head;
		if (!next) {
			//TODO: WARNING COUT
			string removeStr = "rmdir / s / q IPFS/MACHINE" + machine->getID().str();
			system(removeStr.c_str());
			ring.remove(Machine(id, name, order));
			makeRoutingTables();
			--currMachines;
			//	WRITE COUT HERE THAT SUCCESSFULLY REMOVED
			return;
		}
		
		Machine* nextM = machine->getRoutingTable().head->data;
		while (!machine->tree.isEmpty()) {
			Key_Pair<File> pair = machine->tree.getRoot()->arr[0];
			Bigint key = pair.getKey();
			int s = pair.getList().size();
			string newPath = ".\\IPFS\\MACHINE" + nextM->getID().str() + "\\" + key.str();
			auto ret = _mkdir(newPath.c_str());
			string oldPath = ".\\IPFS\\MACHINE" + machine->getID().str() + "\\" + key.str();

			for (int i = 0; i < s; i++) {
				Key_Pair<File> temp(key);
				File f = pair.getList().getHead();
				string retFilePath = "\\" + f.getFilename() + f.getExtension();
				bool successful = copyFile(oldPath + retFilePath, newPath + retFilePath);
				if (successful) {
					cout << "FILE SHIFTED SUCCESSFULLY\n";
				}
				temp.insert(f);
				pair.remove(f);
				nextM->tree.insert(temp);
				machine->tree.remove(temp);
			}
		}
		string removeStr = "rmdir / s / q .\\IPFS\\MACHINE" + machine->getID().str();
		system(removeStr.c_str());
		ring.remove(Machine(id, name, order));
		makeRoutingTables();
		//showRoutingTables();
		--currMachines;
	}
	void insertMachine(string name, string id) { //incase user wants to give their own id
		Bigint sid = id;
		Machine machine = Machine(sid, name, order);
		ring.insertAscending(machine);
		makeRoutingTables();
		if (id == "29") {
			showRoutingTables();
		}
		
		string path = "./IPFS/MACHINE" + machine.getID().str();
		auto ret = _mkdir(path.c_str());
		++currMachines;
		if (currMachines > 1) {
			Machine* newMachine = getOrigin(sid);
			Machine* nextMachine = newMachine->getRoutingTable().head->data;
			//	ONLY SPLIT TREES IF THE NEXT MACHINE EXISTS - IF ONLY ONE MACHINE THEN NO SPLITTING SHOULD BE THERE
			if (nextMachine) {
				nextMachine->splitTree(sid, newMachine);

				//	TODO: ALSO MOVE FILE FOLDERS TO OTHER MACHINE
			}
		}
		
	}

	void searchFile(const string& filehash, const string& mid) {
		Machine* m = searchMachine(filehash, mid);
		if (m == nullptr) {
			cout << "No suitable machine found where the file could be stored!\n";
			return;
		}
		m->printDetails();
		m->searchFile(filehash);
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
	~Ringdht() {
		string remove = "rmdir / s / q IPFS";
		system(remove.c_str());
	}

};