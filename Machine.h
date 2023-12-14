
#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <direct.h>
#include "DoubleList.h"
#include "utlity.h"
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
	Machine(Bigint& id,string name, int order) : name(name), id(id), tree(order){
	
	}
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
	
	bool searchFile(const string& fileHash) {
		Bigint key(fileHash);
		Key_Pair<File> k(key);
		const Key_Pair<File>* result = tree.search(k);
		if (result == nullptr) {
			cout << "File does not exist on the current machine.\n";
			return false;
		}else{
			cout << "File is stored on machine " << this->getID();
			return true;
		}
	}
	
	void removeFile(const string& filehash) {
		Bigint key(filehash);
		Key_Pair<File> pair(key);
		Key_Pair<File> keyPair = tree.search(pair);
		File f(key, "./IPFS/DELETE", "hello.txt");
		int size = keyPair.getList().size();
		LinkedList<File> list;
		LinkedList<Bigint> userInput;
		for (int i = 0; i < size; i++) {
			File file = keyPair.getList().getHead();
			f.setFilename(file.getFilename());
			f.setExtension(file.getExtension());
			f.setPath(file.getPath());
			list.insert(f);
			cout << i + 1 << ". " << keyPair.getList().getHead().getFilename() << f.getExtension() << "\n";
			keyPair.remove(f);
		}
		cout << "Enter indexes (comma-seperated) of the files to remove: ";
		string response;
		getline(cin, response);
		int i = 0;
		char delimeter = ' ';
		string num;
		while (response[i] != '\0') {
			if (response[i] == delimeter) {
				userInput.insert(Bigint(num));
				num.clear();
			}
			else {
				num += response[i];
			}
			i++;
		}
		userInput.insert(Bigint(num));
		num.clear();
		int count = -1;
		while (userInput.isEmpty() == false) {
			Bigint curr = userInput.getHead();
			userInput.remove(curr);

			File currFile(key, "./IPFS/DELETE", "random.txt");
			while (curr > count) {
				currFile = list.getHead();
				list.remove(currFile);
				count++;
			}
			
			if (curr == count) {
				//	PERFORM DELETION HERE
				Key_Pair<File> tempPair(key);
				tempPair.insert(currFile);
				tree.remove(tempPair);
			}
		}
		
		const Key_Pair<File>* newP = tree.search(pair);
		Key_Pair<File> newPair = *newP;
		int psize = newPair.getList().size();
		for (int i = 0; i < psize; i++) {
			cout << newPair.getList().getHead();
			newPair.remove(newPair.getList().getHead());
		}
	}
	void insertFile(Bigint& id, string path) {
		Key_Pair<File> keyvalue(id);
		string Newpath = "./IPFS/MACHINE" + id.str();
		keyvalue.insert(File(id, Newpath, path));
		tree.insert(keyvalue);
		cout << "HASH OF FILE: " << id << endl;
		cout << "FILE INSERTED AT MACHINE WITH ID: " << getID() << endl;
		bool success = copyFile(path, Newpath + "/File_" + get + getFileExtension(path));
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
	~Machine() {
		
	}
};