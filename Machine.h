
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
		const Key_Pair<File>* ptr = tree.search(pair);
		if (ptr == nullptr) {
			cout << "ERROR: Unable to delete file. File is not stored on the machine.\n";
			return;
		}
		if (ptr->getList().size() == 1) {
			//	SUCCESSFULLY REMOVED FILENAME FROM SYSTEM
			File f = ptr->getList().getHead();
			cout << "SUCCESSFULLY REMOVED FILE" << f.getFilename() << f.getExtension() << "with path: " << f.getPath()<<'\\'<<f.getFilename() << f.getExtension() << endl;
			string filePath = f.getPath() + '\\' + key.str()  + '\\' + f.getFilename() + f.getExtension();
			remove(filePath.c_str());
			pair.insert(f);
			tree.remove(pair);
			return;
		}
		Key_Pair<File> keyPair = *ptr;
		File f(key, "hello.txt", "temppath.txt");
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
		cout << "Enter indexes (space seperated) of the files to remove: ";
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

			File currFile(key, "random.txt", "temppath.txt");
			while (curr > count) 
			{
				currFile = list.getHead();
				list.remove(currFile);
				count++;
			}

			if (curr == count) {
				//	PERFORM DELETION HERE
				Key_Pair<File> tempPair(key);
				tempPair.insert(currFile);
				cout << "SUCCESSFULLY REMOVED FILE" << currFile.getFilename() << currFile.getExtension() << "with path: " << currFile.getPath()<< '\\' << currFile.getFilename() << currFile.getExtension() << endl;
				string filePath = currFile.getPath() + '\\' + key.str()  + '\\' + currFile.getFilename() + currFile.getExtension();
				remove(filePath.c_str());
				tree.remove(tempPair);
			}
		}
		//	COUTING
		const Key_Pair<File>* newP = tree.search(pair);
		if (!newP) {
			cout << "NO FILES REMAINING IN BTREE!\n";
			return;
		}
		cout << "FILES AFTER DELETION: \n";
		Key_Pair<File> newPair = *newP;
		int psize = newPair.getList().size();
		for (int i = 0; i < psize; i++) {
			cout << newPair.getList().getHead();
			newPair.remove(newPair.getList().getHead());
		}
	}

	void insertFile(const Bigint& id, const string& path) {
		Key_Pair<File> keyvalue(id);
		const Key_Pair<File>* pair = tree.search(keyvalue);
		string Newpath = ".\\IPFS\\MACHINE" + this->id.str();
		File newFile(id, Newpath, path);
		if (pair == nullptr) {
			keyvalue.insert(newFile);
			string filePath = ".\\IPFS\\MACHINE" + this->id.str();
			filePath += "\\" + id.str();
			_mkdir(filePath.c_str());
			filePath += '\\' + newFile.getFilename() + newFile.getExtension();
			bool success = copyFile(path, filePath);
			if (success) {
				cout << "FILE COPIED SUCCESSFULLY\n";
			}
		}
		else {
			 string delimeter = to_string(pair->getList().getIC());
			 string fileName = newFile.getFilename();
			 fileName += " (" + delimeter + ")";
			 newFile.setFilename(fileName);
			 keyvalue.insert(newFile);
			 string filePath = ".\\IPFS\\MACHINE" + this->id.str();
			 filePath += "\\" + id.str();
			 _mkdir(filePath.c_str());
			 filePath += '\\' + newFile.getFilename() + newFile.getExtension();
			 bool success = copyFile(path, filePath);
			 if (success) {
				 cout << "FILE COPIED SUCCESSFULLY\n";
			 }
		}
		tree.insert(keyvalue);
		cout << "HASH OF FILE: " << id << endl;
		cout << "FILE INSERTED AT MACHINE WITH ID: " << getID() << endl;
	}
	
	void splitTree(const Bigint& mid, Machine* m) {
		//	IF THE CURRENT MACHINE HAS FILES ONLY THEN SPLITTING MIGHT HAPPEN
		if (tree.isEmpty() == false) {
			//	IF MACHINE ID OF NEWER MACHINE IS LESSER
			if (m->getID() < this->id) {

				bool minIsLess = false;
				do {
					//	INITIALLY ASSUME THAT MINIMUM WOULD BE LESSER - IF GREATER LOOP BREAKS
					minIsLess = false;

				
					//	GET CURRENT MINIMUM
					const Key_Pair<File>* kp = tree.getMinimum();
					if (kp == nullptr) {
						break;
					}
					//	IF LESSER COPY THE PAIR AND THEN REMOVE FROM THE TREE
					if (kp->getKey() <= mid) {
						minIsLess = true;
						Key_Pair<File> copy = *kp;
						int numFiles = kp->getList().size();
						for (int i = 0; i < numFiles; i++) {
							//	MAKE ONE PAIR FROM WHOLE LINKED LIST ONE BY ONE FOR EVERY FILE
							Key_Pair<File> tempPair(copy.getKey());
							File temp = copy.getList().getHead();
							tempPair.insert(temp);

							//	INSERTING TO NEW MACHINE AND REMOVING FROM PREVIOUS MACHINE
							m->tree.insert(tempPair);
							tree.remove(tempPair);

							//	REMOVING FROM COPY SO THAT THE HEAD GIVES THE NEXT FILE NEXT TIME
							copy.remove(temp);
						}
					}

				} while (minIsLess);


			} 
			
			if (m->getID() > this->id) {
				bool maxIsLess = false;
				do {


					//	GET CURRENT MINIMUM
					const Key_Pair<File>* kp = tree.getMaximum();
					if (kp == nullptr) {
						break;
					}
					//	IF LESSER COPY THE PAIR AND THEN REMOVE FROM THE TREE
					if (kp->getKey() <= mid) {
						maxIsLess = true;
						Key_Pair<File> copy = *kp;
						int numFiles = kp->getList().size();
						for (int i = 0; i < numFiles; i++) {
							//	MAKE ONE PAIR FROM WHOLE LINKED LIST ONE BY ONE FOR EVERY FILE
							Key_Pair<File> tempPair(copy.getKey());
							File temp = copy.getList().getHead();
							tempPair.insert(temp);

							//	INSERTING TO NEW MACHINE AND REMOVING FROM PREVIOUS MACHINE
							m->tree.insert(tempPair);
							tree.remove(tempPair);

							//	REMOVING FROM COPY SO THAT THE HEAD GIVES THE NEXT FILE NEXT TIME
							copy.remove(temp);
						}
					}

				} while (maxIsLess);
			}
		}
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