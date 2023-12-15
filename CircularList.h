/************************************************************************
TITLE: CIRCULAR LINKED LIST
DESCRIPTION:
This class was made to aid in the construction of the ring dht
REQUIREMENTS: COPY CONSTRUCTOR FOR THE TYPE MUST BE DEFINED
AUTHOR: DANIYAL AHMED [22I-1032]
DATE: MONDAY 4-12-2023
LASTEDITBY: DANIYAL AHMED
*************************************************************************/
#pragma once
template<class T>
class cNode {
public:
	T data;
	cNode<T>* next;
	cNode<T>* prev;
	T getData() { return data; }
	void setData(T d) { data = d; }
	cNode*& getNext() { return next; }
	cNode(T data) : data(data), next(nullptr), prev(nullptr) {}
};
template<class T>
class CircularLinkedList {
public:
	cNode<T>* head;
	CircularLinkedList() : head(nullptr) {}
	void insert(T data) {
		if (!head) {
			head = new cNode<T>(data);
			head->next = head;
			head->prev = head;
			return;
		}
		if (head->next == head) {
			head->next = new cNode<T>(data);
			head->next->prev = head;
			head->next->next = head;
			return;
		}
		cNode<T>* curr = head->next;
		while (curr && curr->next != head)
			curr = curr->next;
		curr->next = new cNode<T>(data);
		curr->next->prev = curr;
		curr = curr->next;
		curr->next = head;
		head->prev = curr;
	}
	bool insertAscending(T data) {
		if (isEmpty()) {
			head = new cNode<T>(data);
			head->next = head;
			head->prev = head;
			return true;
		}
		if (data == head->data) {
			return false;
		}
		if (data < head->data) {
			cNode<T>* node = new cNode<T>(data);
			node->next = head;
			node->prev = head->prev;
			head->prev->next = node;
			head->prev = node;
			head = node;
			return true;
		}
		cNode<T>* curr = head;
		do {
			if (curr->data > data) break;
			else if (curr->data == data) return false;
			curr = curr->next;
		} while (curr != head);
		cNode<T>* node = new cNode<T>(data);
		node->prev = curr->prev;
		node->next = curr;
		curr->prev->next = node;
		curr->prev = node;
		return true;
	}
	cNode<T>*& getHead() {
		return head;
	}
	bool isEmpty() {
		return !head;
	}
	bool exists(T data) {
		if (isEmpty()) return false;
		if (head->data == data) return true;
		cNode<T>* curr = head->next;
		while (curr && curr->next != head) {
			if (curr->data == data) return true;
			curr = curr->next;
		}
		return false;
	}

	const T& search(const T& data) {
		cNode<T>* temp = head;
		bool found = false;
		do {
			if (temp->data == data) {
				return temp->data;
			}
			temp = temp->next;
		} while (temp != head);
		return T();
	}
	void update(int data, int replacer) {
		if (isEmpty()) return;
		if (head->data == data) head->setData(replacer);
		cNode<T>* curr = head->next;
		while (curr && curr->next != head) {
			if (curr->data == data) {
				curr->setData(replacer);
				break;
			}
			curr = curr->next;
		}
	}

	void remove(T data) {
		if (isEmpty())
			return;
		cNode<T>* curr = head;


		if (head->data == data) {
			if (head->next == head) { //means that only one element in list
				delete head;
				head = nullptr;
				return;
			}
			cNode<T>* temp = head;
			cNode<T>* curr = head->next;
			while (curr->next != head) curr = curr->next;
			head = head->next;
			head->prev = temp->prev;
			curr->next = head;
			delete temp;
			return;
		}
		do {
			if (curr->data == data) {
				cNode<T>* temp = curr;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				return;
			}

			curr = curr->next;
		} while (curr != head);
	}
	void printList() {
		cNode<T>* temp = head;
		if (head != NULL) {
			do {
				cout << temp->data << " ";
				temp = temp->next;
			} while (temp != head);
		}
		cout << endl;
	}
	~CircularLinkedList() {
		cNode<T>* curr = head->next;
		cNode<T>* temp = nullptr;
		while (curr != head) {
			temp = curr;
			curr = curr->next;
			delete temp;
		}
		if (!head) delete head;
		head = nullptr;
	}
};
