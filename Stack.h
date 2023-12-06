#pragma once
#include <iostream>
using namespace std;
template<class T>
class sNode{
public:
	T data;
	sNode<T>* next;
	sNode<T>(T data) {
		next = nullptr;
		this->data = data;
	}
	sNode<T>() : data(0), next(nullptr) {}
};
template<class T>
class Stack {
public:
	sNode<T>* head;
	sNode<T>* top;
	int items;
	Stack() {
		head = nullptr;
		top = nullptr;
		items = 0;
	}
	void push(const T data) {
		items++;
		if (!top) {
			top = new sNode<T><T>(data);
			return;
		}
		sNode<T>* node = new sNode<T>(data);
		node->next = top;
		top = node;
	}
	T peek() {
		if (!top) T();
		return top->data;
	}
	bool isEmpty() {
		return !top;
	}
	T pop() {
		if (!top) return T();
		T data = top->data;
		sNode<T>* node = top;
		top = top->next;
		delete node;
		items--;
		return data;
	}
	void clear() {
		while (!isEmpty())
			T data = pop();
	}
	~Stack() {
		clear();
	}
};