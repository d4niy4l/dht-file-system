#pragma once
template <class T>
class dNode {
public:
	T data;
	dNode<T>* next;
	dNode<T>* prev;
	dNode<T>() : data(0), next(nullptr), prev(nullptr) {}
	dNode<T>(T data, dNode<T>* next = nullptr, dNode<T>* prev = nullptr) : data(data), next(next), prev(prev) {}
	T getData() { return data; }
	void setData(T d) { data = d; }
	dNode<T>*& getNext() { return next; }
	void setNext(dNode<T>* ptr) { next = ptr; }
	dNode<T>*& getPrev() { return prev; }
	void setPrev(dNode<T>* ptr) { prev = ptr; }
};
template <class T>
class DoublyLinkedList {
public:
	dNode<T>* head;
	dNode<T>* tail;
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}
	dNode<T>*& getHead() { return head; }
	bool isEmpty() {
		return !head;
	}
	void insert(T data) {
		if (!tail) {
			head = new dNode<T>();
			head->setData(data);
			tail = head;
			return;
		}
		dNode<T>* node = new dNode<T>();
		node->setData(data);
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	void insertToHead(T data) {
		dNode<T>* node = new dNode<T>();
		node->setData(data);
		if (!head) {
			head = node;
			return;
		}
		node->next = head;
		head->prev = node;
		head = node;
	}
	//list can never reach a 'full' state
	bool search(T data) {
		dNode<T>* curr = head;
		while (curr) {
			if (curr->data == data) return true;
			curr = curr->next;
		}
		return false;
	}
	void update(T d1, T d2) {
		dNode<T>* curr = head;
		while (curr) {
			if (curr->data == d1) {
				curr->setData(d2);
				return;
			}
			curr = curr->next;
		}
	}
	void insertAtIndex(T data, int index) {
		int count = 1;
		dNode<T>* curr = head;
		if (isEmpty() || index == 0) {
			insertToHead(data);
			return;
		}
		while (curr) {
			if (count == index)
				break; // 10<->20<->40 == 10<->20<->30<->40
			count++;
			curr = curr->next;
		}
		if (!curr && count - 1 < index) return;
		if (curr && !curr->next) {
			insert(data);
			return;
		}
		dNode<T>* node = new dNode<T>();
		node->setData(data);
		node->prev = curr;
		node->next = curr->next;
		curr->next = node;
	}
	void print() {
		dNode<T>* curr = head;
		while (curr) {
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}
	void deleteData(T data) {
		dNode<T>* curr = head;
		while (curr) {
			if (curr->data == data) {
				dNode<T>* node = curr;
				if (curr->next && curr->prev) {
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
				}
				else if (curr->next) {
					head = curr->next;
					curr->next->prev = nullptr;
				}
				else if (curr->prev) {
					tail = curr->prev;
					curr->prev->next = nullptr;
				}
				return;
			}
			curr = curr->next;
		}
	}
	void clear() {
		dNode<T>* curr = head;
		while (curr) {
			dNode<T>* temp = curr;
			curr = curr->next;
			delete temp;
		}
		head = nullptr;
		tail = nullptr;
	}
	~DoublyLinkedList() {
		clear();
	}
};