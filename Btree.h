#pragma once
/************************************************************************
TITLE: Btree
DESCRIPTION:
This class was made to store files efficiently in the form of b tree
AUTHOR: DANIYAL AHMED [22I-1032]
AUTHOR: MUHAMMAD AHMAD [22I-1056]
AUTHOR: HAFIZA IQRA [22I-1269]
DATE: MONDAY 4-12-2023
LASTEDITBY: MUHAMMAD AHMAD
*************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "vector.h"
#include "Key_Pair.h"
#include "Queue.h"
using namespace std;

template <class T>
class BNode {
public:
	Vector<T> arr;
	Vector<BNode<T>*> links;
	int m;
	int count;
	bool isLeaf;
	int medPos;
	bool evenSplit = 0;

	//  CONSTRUCTOR
	BNode(int order)
		:links(order + 1), arr(order)
	{
		this->m = order;
		this->isLeaf = false;
		this->count = 0;
		if (m % 2 == 1 || evenSplit == 1) {
			this->medPos = order / 2;
		}
		else {
			this->medPos = (order / 2) - 1;
		}
	}

	//  DESTRUCTOR
	~BNode() {

	}

	//  GET MEDIAN
	const T& getMedian() {
		return this->arr[this->medPos];
	}

	bool isFull() {
		return (count == m - 1);
	}

	//  INSERT 
	void insert(const T& val) {
		bool inserted = false;
		for (int i = 0; i < count; i++) {
			if (arr[i] > val) {
				arr.insert_at_index(val, i);
				count++;
				inserted = true;
				break;
			}
		}
		if (!inserted) {
			arr.insert_at_index(val, count++);
		}
	}

	void insert(const T& data, BNode<T>* left, BNode<T>* right) {
		int idx = -1;
		for (int i = 0; i < count; i++) {
			if (data > arr[i]) {
				idx++;
				continue;
			}
			break;
		}

		arr.insert_at_index(data, idx + 1);
		count++;
		links.set_at_index(left, idx + 1);
		links.insert_at_index(right, idx + 2);
	}


	//	REMOVE
	void remove(int i, const T& data) {
		this->arr.remove_at_index(i);
		this->count--;
	}

};

template <>
class BNode<Key_Pair<File>> {
public:
	Vector<Key_Pair<File>> arr;
	Vector<BNode<Key_Pair<File>>*> links;
	int m;
	int count;
	bool isLeaf;
	int medPos;
	bool evenSplit = 0;

	//  CONSTRUCTOR
	BNode(int order)
		:links(order + 1), arr(order)
	{
		this->m = order;
		this->isLeaf = false;
		this->count = 0;
		if (m % 2 == 1 || evenSplit == 1) {
			this->medPos = order / 2;
		}
		else {
			this->medPos = (order / 2) - 1;
		}
	}

	//	DESTRUCTOR
	~BNode() {

	}

	const Key_Pair<File>& getMedian() {
		return this->arr[this->medPos];
	}

	bool isFull() {
		if (count == m - 1) {
			return true;
		}
		else {
			return false;
		}
	}


	void insert(const Key_Pair<File>& val) {
		bool inserted = false;
		for (int i = 0; i < count; i++) {
			if (arr[i] == val) {
				Key_Pair<File>& f = arr[i];
				File newobj = val.getList().getHead();
				f.insert(newobj);
				inserted = true;
				break;
			}
			else if (arr[i] > val) {
				arr.insert_at_index(val, i);
				count++;
				inserted = true;
				break;
			}
		}

		if (!inserted) {
			arr.insert_at_index(val, count++);
		}
	}

	void insert(const Key_Pair<File>& data, BNode<Key_Pair<File>>* left, BNode<Key_Pair<File>>* right) {
		int idx = -1;
		for (int i = 0; i < count; i++) {
			if (data > arr[i]) {
				idx++;
				continue;
			}
			break;
		}

		arr.insert_at_index(data, idx + 1);
		count++;
		links.set_at_index(left, idx + 1);
		links.insert_at_index(right, idx + 2);
	}

	//	REMOVE
	void remove(int i, const Key_Pair<File>& val) {
		Key_Pair<File>& k = arr[i];
		File f = val.getList().getHead();
		k.remove(f);
		if (k.getList().size() > 0) {
			return;
		}
		this->arr.remove_at_index(i);
		this->count--;
	}

};


template <class T>
class BTree {
private:
	int order;
	BNode<T>* root;
	const int MAX_KEYS;
	const int MAX_LINKS;
	const int MIN_KEYS;
	bool evenSplit = 0;
	bool DELETE_VIA_SUCCESSOR = 0;
private:


	//	HELPER FUNCTIONS FOR SEARCH
	const T* helpSearch(BNode<T>* currNode, const T& data) {
		if (currNode == nullptr) {
			return nullptr;
		}
		int idx = -1;
		for (int i = 0; i < currNode->count; i++) {
			if (data > currNode->arr[i]) {
				idx++;
			}
			else {
				break;
			}
		}
		if (currNode->arr[idx + 1] == data) {
			return &currNode->arr[idx + 1];
		}
		else {
			if (currNode->isLeaf) {
				return nullptr;
			}else{
				return helpSearch(currNode->links[idx + 1], data);
			}
		}
	}

	//  HELPER FUNCTIONS FOR INSERTION
	void insertNode(BNode<T>*& currNode, const T& data) {
		//  IF CURRENT NODE IS LEAF THEN VALUE NEEDS TO BE INSERTED
		if (currNode->isLeaf) {
			currNode->insert(data);
		}
		//  TRAVERSE TO THE LEAF
		else {
			int idx = -1;
			for (int i = 0; i < currNode->count; i++) {
				if (data > currNode->arr[i]) {
					idx++;
				}
				else {
					break;
				}
			}
			insertNode(currNode->links[idx + 1], data);
			if (currNode->links[idx + 1]->count > MAX_KEYS) {
				splitChild(currNode, currNode->links[idx + 1]);
				//  THIS WILL SPLIT THE CHILD INTO TWO PARTS AND ADD THEIR MEDIAN TO THE PARENT
				//  ON ROLLBACK THE PARENT WILL ALSO GET CHECKED HERE IF IT'S FULL OR NOT
			}
		}
	}

	void splitChild(BNode<T>*& parent, BNode<T>*& child) {
		T median = child->getMedian();
		BNode<T>* left = child;
		BNode<T>* right = new BNode<T>(order);
		right->isLeaf = left->isLeaf;

		//  COPYING ELEMENTS [KEYS]
		int medianidx;
		//  IF ODD ORDER OR (IF EVEN ORDER EVEN MEDIAN CASE)
		if (order % 2 == 1 || evenSplit == 1) {
			medianidx = order / 2;
		}
		else {
			medianidx = order / 2 - 1;
		}
		int startIdx = medianidx + 1;
		int count = order - startIdx;


		for (int i = 0; i < count; i++) {
			right->arr.insert_at_index(left->arr[i + startIdx], i);
			right->count++;
		}
		for (int i = 0; i < count; i++) {
			left->arr.pop_back();
			left->count--;
		}
		left->arr.pop_back();
		left->count--;

		//  IF NOT LEAF THEN ALSO NEED TO COPY THE [LINKS]
		if (!left->isLeaf) {
			int startIdx;
			if (order % 2 == 1 || evenSplit == 1) {
				startIdx = (order / 2) + 1;
			}
			else {
				startIdx = order / 2;
			}
			int count = order + 1 - startIdx;
			for (int i = 0; i < count; i++) {
				right->links.insert_at_index(left->links[i + startIdx], i);
				left->links[i + startIdx] = nullptr;
			}
			for (int i = 0; i < count; i++) {
				left->links.pop_back();
			}
		}

		//  ADD MEDIAN TO PARENT NODE
		parent->insert(median, left, right);
	}

	//  HELPER FUNCTIONS FOR DELETION
	void deleteAtLeaf(BNode<T>*& currNode, const T& data) {
		for (int i = 0; i < currNode->count; i++) {
			if (currNode->arr[i] == data) {
				currNode->remove(i, data);
				break;
			}
		}
	}
	void deleteAtInternal(BNode<T>*& currNode, const T& data) {
		int idx = -1;
		for (int i = 0; i < currNode->count; i++) {
			if (data > currNode->arr[i]) {
				idx++;
			}
			else {
				break;
			}
		}
		//  SUCCESSOR
		if (DELETE_VIA_SUCCESSOR) {
			BNode<T>* child = currNode->links[idx + 2];
			BNode<T>* temp = child;
			while (temp->isLeaf == false) {
				temp = temp->links[0];
			}
			T currData = temp->arr[0];
			currNode->arr[idx + 1] = currData;
			deleteNode(child, currData);
			checkDeficiency(currNode, child, idx + 2);
		}
		else {
			//  LEFT SUBTREE - RIGHTMOST ELEMENT
			BNode<T>* child = currNode->links[idx + 1];
			BNode<T>* temp = child;
			while (temp->isLeaf == false) {
				temp = temp->links[temp->count];
			}
			T currData = temp->arr[temp->count - 1];
			currNode->arr[idx + 1] = currData;
			deleteNode(child, currData);
			checkDeficiency(currNode, child, idx + 1);
		}
	}
	void checkDeficiency(BNode<T>* currNode, BNode<T>* child, int childidx) {
		if (child->count >= MIN_KEYS) {
			return;
		}

		bool resolved = false;


		//  CHECK LEFT SIBLING
		if (childidx - 1 >= 0) {
			BNode<T>* nLeft = currNode->links[childidx - 1];
			if (nLeft->count > MIN_KEYS) {
				T temp = nLeft->arr[nLeft->count - 1];
				nLeft->arr.pop_back();

				T currNodeVal = currNode->arr[childidx - 1];
				currNode->arr[childidx - 1] = temp;

				child->insert(currNodeVal);
				if (!child->isLeaf) {
					BNode<T>* temp = nLeft->links[nLeft->count];
					nLeft->links.pop_back();
					child->links.push_front(temp);
				}
				nLeft->count--;
				resolved = true;
			}
		}

		if (resolved) {
			return;
		}
		//  CHECK RIGHT SIBLING
		if (childidx + 1 <= currNode->count) {
			BNode<T>* nRight = currNode->links[childidx + 1];
			if (nRight->count > MIN_KEYS) {
				T temp = nRight->arr[0];
				nRight->arr.remove_at_index(0);

				T currNodeVal = currNode->arr[childidx];
				currNode->arr[childidx] = temp;

				child->insert(currNodeVal);
				if (!child->isLeaf) {
					BNode<T>* temp = nRight->links[0];
					nRight->links.pop_front();
					child->links.push_back(temp);
				}
				nRight->count--;
				resolved = true;
			}
		}
		if (resolved) {
			return;
		}
		//  MERGE LEFT
		if (childidx - 1 >= 0) {
			//BNode* mergedNode = new BNode(order);

			BNode<T>* nLeft = currNode->links[childidx - 1];
			nLeft->arr.push_back(currNode->arr[childidx - 1]);
			nLeft->count++;
			currNode->arr.remove_at_index(childidx - 1);
			currNode->count--;
			for (int i = 0; i < child->count; i++) {
				nLeft->arr.push_back(child->arr[i]);
				nLeft->count++;
			}
			if (!child->isLeaf) {
				for (int i = 0; i <= child->count; i++) {
					nLeft->links.push_back(child->links[i]);
				}
			}
			delete child;
			child = nullptr;
			currNode->links.set_at_index(nLeft, childidx);
			currNode->links.remove_at_index(childidx - 1);

			if (currNode->count == 0 && currNode == this->root) {
				this->root = nLeft;
			}
			return;
		}

		//  MERGE RIGHT
		if (childidx + 1 <= currNode->count) {
			BNode<T>* nRight = currNode->links[childidx + 1];
			nRight->arr.push_front(currNode->arr[childidx]);
			nRight->count++;
			currNode->arr.remove_at_index(childidx);
			currNode->count--;
			for (int i = 0; i < child->count; i++) {
				nRight->arr.push_front(child->arr[i]);
				nRight->count++;
			}

			if (!child->isLeaf) {
				for (int i = child->count; i >= 0; i--) {
					nRight->links.push_front(child->links[i]);
				}
			}
			delete child;
			child = nullptr;
			currNode->links.set_at_index(nRight, childidx);
			currNode->links.remove_at_index(childidx + 1);

			if (currNode->count == 0 && currNode == this->root) {
				this->root = nRight;
			}
			return;
		}
	}
	void deleteNode(BNode<T>*& currNode, const T& data) {
		if (currNode == nullptr) {
			return;
		}
		int idx = -1;
		for (int i = 0; i < currNode->count; i++) {
			if (data > currNode->arr[i]) {
				idx++;
			}
			else {
				break;
			}
		}
		//  VALUE FOUND IN CURRENT NODE
		if (data == currNode->arr[idx + 1]) {
			if (currNode->isLeaf) {
				deleteAtLeaf(currNode, data);
			}
			else {
				deleteAtInternal(currNode, data);
			}
		}
		//  FIND VALUE IN SUBTREE
		else {
			if (currNode->isLeaf) {
				return;
			}
			deleteNode(currNode->links[idx + 1], data);
			checkDeficiency(currNode, currNode->links[idx + 1], idx + 1);
		}

	}
	void destroyTree(BNode<T>* node) {
		if (node != nullptr) {
			if (!node->isLeaf) {
				for (int i = 0; i <= node->count; i++) {
					if (node->links[i])
						destroyTree(node->links[i]);
				}
			}
			if (node) {
				delete node;
				node = nullptr;
			}
		}
	}

public:
	//  CONSTRUCTOR
	BTree(int order)
		:order(order), MAX_KEYS(order - 1), MAX_LINKS(order), MIN_KEYS(ceil(order / 2.0) - 1), root(nullptr)
	{
	}

	//  DESTRUCTOR
	~BTree() {
		this->destroyTree(this->root);
	}

	//  IS EMPTY
	bool isEmpty() {
		if (this->root == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	//  INSERT
	void insert(const T& data) {
		//  IF ROOT IS NULL
		if (this->root == nullptr) {
			BNode<T>* newNode = new BNode<T>(order);
			newNode->isLeaf = true;
			newNode->arr.insert_at_index(data, 0);
			newNode->count++;
			this->root = newNode;
			return;
		}
		//  IF ROOT IS NOT NULL
		else {
			insertNode(this->root, data);

			//  IF ROOT GETS FULL
			if (this->root->arr.size() > MAX_KEYS) {
				BNode<T>* newParent = new BNode<T>(order);
				newParent->links.insert_at_index(this->root, 0);
				this->root = newParent;
				splitChild(this->root, this->root->links[0]);
			}
		}
	}

	//  REMOVE
	void remove(const T& data) {
		deleteNode(this->root, data);
		if (this->root->count == 0) {
			delete this->root;
			this->root = nullptr;
		}
	}

	//	SEARCH
	const T* search(const T& val) {
		const T* result = helpSearch(root, val);
		if (result) {
			return result;
		}
		else {
			return nullptr;
		}
	}

	//  GETTERS
	BNode<T>* getRoot() {
		return this->root;
	}

	//	GET MINIMUM
	const T* getMinimum() {
		if (this->isEmpty()) {
			return nullptr;
		}
		BNode<T>* temp = this->root;
		while (temp && !temp->isLeaf) {
			temp = temp->links[0];
		}
		const T* ret = &temp->arr[0];
		return ret;
	}
	
	//	GET MAXIMUM
	const T* getMaximum() {
		if (this->isEmpty()) {
			return nullptr;
		}
		BNode<T>* temp = this->root;
		while (temp && !temp->isLeaf) {
			temp = temp->links[temp->count];
		}
		const T* ret = &temp->arr[temp->count -1];
		return ret;
	}

};

template <>
void BTree<Key_Pair<File>>::deleteAtInternal(BNode<Key_Pair<File>>*& currNode, const Key_Pair<File>& data) {
	int idx = -1;
	for (int i = 0; i < currNode->count; i++) {
		if (data > currNode->arr[i]) {
			idx++;
		}
		else {
			break;
		}
	}
	Key_Pair<File>& k = currNode->arr[idx + 1];
	if (k.getList().size() > 1) {
		k.remove(data.getList().getHead());
		return;
	}
	//  SUCCESSOR
	if (DELETE_VIA_SUCCESSOR) {
		BNode<Key_Pair<File>>* child = currNode->links[idx + 2];
		BNode<Key_Pair<File>>* temp = child;
		while (temp->isLeaf == false) {
			temp = temp->links[0];
		}
		Key_Pair<File> currData = temp->arr[0];
		currNode->arr[idx + 1] = currData;
		deleteNode(child, currData);
		checkDeficiency(currNode, child, idx + 2);
	}
	else {
		//  LEFT SUBTREE - RIGHTMOST ELEMENT
		BNode<Key_Pair<File>>* child = currNode->links[idx + 1];
		BNode<Key_Pair<File>>* temp = child;
		while (temp->isLeaf == false) {
			temp = temp->links[temp->count];
		}
		Key_Pair<File> currData = temp->arr[temp->count - 1];
		currNode->arr[idx + 1] = currData;
		deleteNode(child, currData);
		checkDeficiency(currNode, child, idx + 1);
	}
}


// BTREE VISUALIZATION
void visualizeTree(const string & dotCode) {
	ofstream dotFile("btree.dot");
	dotFile << dotCode;
	dotFile.close();
	string command = "dot -Tpng btree.dot -o btree.png";
	system(command.c_str());
	system("start btree.png");
}

//	FOR INT
template <class T>
string generateTreeDotCode(BNode<T>* btreeRoot) {
	std::string dotCode = "digraph BTree {\n";
	dotCode += "\tnode [shape=record, height=.1];\n\n";

	Queue<BNode<T>*> levelOrderQueue;
	Vector<int> idQ;
	levelOrderQueue.enqueue(btreeRoot);
	int count = 0;
	idQ.push_back(count);
	while (!levelOrderQueue.isEmpty()) {
		BNode<T>* current = levelOrderQueue.peek();
		levelOrderQueue.dequeue();
		int j = idQ[0];
		idQ.remove_at_index(0);
		dotCode += "\tnode" + std::to_string(j) + " [label=\"";
		for (int i = 0; i < current->arr.size(); i++) {
			dotCode += "|";
			dotCode += to_string(current->arr[i]);
		}
		dotCode += "|\"];\n";

		for (size_t i = 0; i < current->links.size(); ++i) {
			count++;
			dotCode += "\tnode" + std::to_string(j) + " -> node" + std::to_string(count) + ";\n";
			idQ.push_back(count);
			if (current->links[i]) {
				levelOrderQueue.enqueue(current->links[i]);
			}
		}
	}

	dotCode += "}\n";
	return dotCode;
}

//	FOR CHAR
template <>
string generateTreeDotCode(BNode<char>* btreeRoot) {
	std::string dotCode = "digraph BTree {\n";
	dotCode += "\tnode [shape=record, height=.1];\n\n";

	Queue<BNode<char>*> levelOrderQueue;
	Vector<int> idQ;
	levelOrderQueue.enqueue(btreeRoot);
	int count = 0;
	idQ.push_back(count);
	while (!levelOrderQueue.isEmpty()) {
		BNode<char>* current = levelOrderQueue.peek();
		levelOrderQueue.dequeue();
		int j = idQ[0];
		idQ.remove_at_index(0);
		dotCode += "\tnode" + std::to_string(j) + " [label=\"";
		for (int i = 0; i < current->arr.size(); i++) {
			char ch = current->arr[i];
			dotCode += "|";
			dotCode += ch;
		}
		dotCode += "|\"];\n";

		for (size_t i = 0; i < current->links.size(); ++i) {
			count++;
			dotCode += "\tnode" + std::to_string(j) + " -> node" + std::to_string(count) + ";\n";
			idQ.push_back(count);
			if (current->links[i]) {
				levelOrderQueue.enqueue(current->links[i]);
			}
		}
	}

	dotCode += "}\n";
	return dotCode;
}

//	FOR STRINGS
template <>
string generateTreeDotCode(BNode<string>* btreeRoot) {
	std::string dotCode = "digraph BTree {\n";
	dotCode += "\tnode [shape=record, height=.1];\n\n";

	Queue<BNode<string>*> levelOrderQueue;
	Vector<int> idQ;
	levelOrderQueue.enqueue(btreeRoot);
	int count = 0;
	idQ.push_back(count);
	while (!levelOrderQueue.isEmpty()) {
		BNode<string>* current = levelOrderQueue.peek();
		levelOrderQueue.dequeue();
		int j = idQ[0];
		//idQ.erase(idQ.begin());
		idQ.remove_at_index(0);
		dotCode += "\tnode" + std::to_string(j) + " [label=\"";
		for (int i = 0; i < current->arr.size(); i++) {
			dotCode += "|";
			dotCode += current->arr[i];
		}
		dotCode += "|\"];\n";

		for (size_t i = 0; i < current->links.size(); ++i) {
			count++;
			dotCode += "\tnode" + std::to_string(j) + " -> node" + std::to_string(count) + ";\n";
			idQ.push_back(count);
			if (current->links[i]) {
				levelOrderQueue.enqueue(current->links[i]);
			}
		}
	}

	dotCode += "}\n";
	return dotCode;
}

//	FOR KEY_PAIR<FILE>
template <>
string generateTreeDotCode(BNode<Key_Pair<File>>* btreeRoot) {
	std::string dotCode = "digraph BTree {\n";
	dotCode += "\tnode [shape=record, height=.1];\n\n";

	Queue<BNode<Key_Pair<File>>*> levelOrderQueue;
	Vector<int> idQ;
	levelOrderQueue.enqueue(btreeRoot);
	int count = 0;
	idQ.push_back(count);
	while (!levelOrderQueue.isEmpty()) {
		BNode<Key_Pair<File>>* current = levelOrderQueue.peek();
		levelOrderQueue.dequeue();
		int j = idQ[0];
		//idQ.erase(idQ.begin());
		idQ.remove_at_index(0);
		dotCode += "\tnode" + std::to_string(j) + " [label=\"";
		for (int i = 0; i < current->arr.size(); i++) {
			dotCode += "|";
			dotCode += current->arr[i].getKey().str();
		}
		dotCode += "|\"];\n";

		for (size_t i = 0; i < current->links.size(); ++i) {
			count++;
			dotCode += "\tnode" + std::to_string(j) + " -> node" + std::to_string(count) + ";\n";
			idQ.push_back(count);
			if (current->links[i]) {
				levelOrderQueue.enqueue(current->links[i]);
			}
		}
	}

	dotCode += "}\n";
	return dotCode;
}








