#pragma once

template <typename T>
struct QNode {
	T val;
	QNode<T>* next;
};

template <typename T>
class Queue {
private:
	QNode<T>* rear;
	QNode<T>* front;
	int numElements;
public:
	//	CONSTRUCTOR
	Queue() {
		this->rear = nullptr;
		this->front = nullptr;
		this->numElements = 0;
	}

	//	DESTRUCTOR
	~Queue() {
		while (!this->isEmpty()) {
			this->dequeue();
		}
	}

	//	ENQUEUE
	void enqueue(const T& val) {
		this->numElements++;
		QNode<T>* newNode = new QNode<T>;
		newNode->val = val;
		newNode->next = nullptr;
		if (!rear) {
			rear = newNode;
			front = newNode;
		}
		rear->next = newNode;
		rear = rear->next;
	}

	//	ISEMPTY
	bool isEmpty() {
		if (front == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	//	DEQUEUE
	T dequeue() {
		if (!isEmpty()) {
			numElements--;
			QNode<T>* temp = front;
			if (numElements == 0) {
				rear = nullptr;
				front = nullptr;
			}
			else {
				front = front->next;
			}
			T returnVal = temp->val;
			delete temp;
			temp = nullptr;

			return returnVal;
		}
	}

	//	SIZE
	int size() {
		return this->numElements;
	}

	//	FRONT
	T peek() {
		if (!this->isEmpty()) {
			return this->front->val;
		}
	}

};