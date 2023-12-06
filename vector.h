#pragma once
#include <iostream>
using namespace std;
template <class T>
class Vector {
	int capacity;
	int size;
	T* data;
public:
	Vector(int s) {
		capacity = s;
		size = 0;
		data = new T[capacity];
	}
	Vector(int s, T val) {
		capacity = s;
		size = s;
		data = new T[capacity];
		for (int i = 0; i < s; i++)
			data[i] = val;
	}
	void resize(int s, T val) {
		delete[] data;
		data = new T[s];
		capacity = s;
		for (int i = 0; i < s; i++)
			data[i] = val;
	}
	void push_back(T val) {
		if (size >= capacity) {
			T* temp = data;
			data = new T[capacity + 10];
			for (int i = 0; i < capacity; i++)
				data[i] = temp[i];
			capacity = capacity + 10;
			delete[] temp;
		}
		data[size] = val;
		size++;
	}
	void pop_back() {
		if (size > 0)
			size--;
	}
	void push_front(T val) {
		T* temp = data;
		if (size >= capacity)
			data = new T[capacity + 10];
		for (int i = 0, j = 1; i < capacity; i++, j++)
			data[j] = temp[i];
		if (size >= capacity) capacity += 10;
		data[0] = val;
		delete[] temp;
	}
	void pop_front() {
		for (int i = 0; i < capacity - 1; i++)
			data[i] = data[i + 1];
		size--;
	}
	int getSize() const {
		return size;
	}
	int get_capacity() const{
		return capacity;
	}
	void insert_at_index(T val, int index) {
		if (index < 0 || index >= capacity) return;
		for (int i = capacity - 1; i > index; i--)
			data[i] = data[i - 1];
		size++;
	}
	T& operator [](int i) {
		if (i >= capacity || i < 0) {
			cout << "OUT OF BOUNDS";
			exit;
		}
		return data[i];
	}
	T& operator [](int i) const {
		if (i >= capacity || i < 0) {
			cout << "OUT OF BOUNDS";
			exit;
		}
		return data[i];
	}
	void clear() {
		delete[] data;
		data = nullptr;
		capacity = 0;
		size = 0;
	}
	~Vector() {
		delete[] data;
	}
};