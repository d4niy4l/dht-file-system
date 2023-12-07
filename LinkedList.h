#pragma once

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

public:
	//	CONSTRUCTOR
	LinkedList() {
		this->head = nullptr;
	}

	//	DESTRUCTOR
	~LinkedList() {
		this->clear();
	}

	//	INSERTION
	void insert(const T& val) {
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
		if (this->head == nullptr) {
			return true;
		}
		else {
			return false;
		}
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
	}

	//	GET HEAD
	const T& getHead() {
		if (!this->isEmpty()) {
			return this->head->data;
		}
	}
};



