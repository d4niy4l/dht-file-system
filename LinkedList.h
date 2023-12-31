#pragma once
/************************************************************************
TITLE: LINKED LIST
DESCRIPTION:
This class was made to make a chain of file objects when there was a collision in hash values
REQUIREMENTS: COPY CONSTRUCTOR FOR THE TYPE MUST BE DEFINED
AUTHOR: MUHAMMAD AHMAD AZAM [22I-1056]
COAUTHOR: DANIYAL AHMED [22I-1032]
COAUTHOR: HAFIZA IQRA [22I-1269]
DATE: TUESDAY 5-12-2023
LASTEDITBY: MUHAMMAD AHMAD AZAM
*************************************************************************/
#include <iostream>
#include <string>
using namespace std;

//	LINKED LIST IMPLEMENTATION

template <typename T>
struct LNode {
	T data;
	LNode* next;

	LNode() {
		this->next = nullptr;
	}

	LNode(T data)
		:data(data), next(nullptr) {	
	}
};

template <typename T>
class LinkedList {
private:
	LNode<T>* head;
	int _size;
	int _ic;
public:
	//	CONSTRUCTOR
	LinkedList() {
		this->head = nullptr;
		_size = 0;
		_ic = 0;
	}

	//	DESTRUCTOR
	~LinkedList() {
		this->clear();
	}

	//	ASSIGNMENT OPERATOR
	LinkedList& operator = (const LinkedList& list) {
		this->clear();
		LNode<T>* curr = list.head;
		while (curr) {
			insert(curr->data);
			curr = curr->next;
		}
		this->_ic = list._ic;
		return *this;
	}


	// COPY CONSTRUCTOR
	LinkedList(const LinkedList& list) {
		clear();
		LNode<T>* curr = list.head;
		while (curr) { 
			insert(curr->data);
			curr = curr->next;
		}
	}

	//	INSERTION
	void insert(const T& val) {
		_size++;
		_ic++;
		LNode<T>* temp = this->head;
		//	IF LIST HEAD IS NULL
		if (!temp) {
			this->head = new LNode<T>(val);
			return;
		}
		//	IF THERE IS AT LEAST ONE ELEMENT
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new LNode<T>(val);
	}

	//	IS EMPTY
	bool isEmpty() const {
		return this->head == nullptr;
	}

	//	SIZE
	int size() const {
		return _size;
	}

	//	INSERTION COUNT
	int getIC() const {
		return this->_ic;
	}

	//	DELETE
	void remove(const T& val) {
		//	IF LIST IS EMPTY THEN RETURN
		if (isEmpty()) {
			return;
		}
		bool found = false;
		LNode<T>* prev = nullptr;
		LNode<T>* temp = this->head;
		while (temp) {
			if (temp->data == val) {
				found = true;
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		if (found) {
			_size--;
			//	VALUE WAS FOUND AT HEAD
			if (prev == nullptr) {
				LNode<T>* delNode = temp; 
				this->head = this->head->next;
				delete delNode;
				delNode = nullptr;
			}
			//	VALUE WAS FOUND AT SOME OTHER NODE
			else {
				prev->next = temp->next;
				delete temp;
				temp = nullptr;
			}
		}
	}
	
	//	CLEAR
	void clear() {
		while (!this->isEmpty()) {
			this->remove(this->head->data);
		}
		_size = 0;
	}

	//PRINT
	void print() const{
		LNode<T>* curr = head;
		while (curr) {
			cout << curr->data << endl;
			curr = curr->next;
		}
	}

	//	GET HEAD
	const T& getHead() const {
		if (!this->isEmpty()) {
			return this->head->data;
		}
	}
};



