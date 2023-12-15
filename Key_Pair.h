#pragma once
/************************************************************************
TITLE: Key_Pair
AUTHOR: MUHAMMAD AHMAD [22I-1056]
COAUTHOR: DANIYAL AHMED [22I-1032]
COAUTHOR: HAFIZA IQRA [22I-1269]
DATE: MONDAY 4-12-2023
LASTEDITBY: MUHAMMAD AHMAD
*************************************************************************/
#include <iostream>
#include "LinkedList.h"
#include "BigInt.h"
#include "File.h"
using namespace std;
template <class T>
class Key_Pair {
	Bigint key;
	LinkedList<T> chain;
public:
	Key_Pair(Bigint key) : key(key){}
	Key_Pair() {
		key = Bigint(-1);
	}
	Key_Pair(const Key_Pair& otherKeyPair) {
		key = otherKeyPair.key;
		chain = otherKeyPair.chain;
	}
	Key_Pair& operator = (const Key_Pair<T>& other) {
		key = other.key;
		chain = other.chain;
		return *this;
	}
	
	
	bool operator == (const Key_Pair<T>& other) const{
		return key == other.key;
	}
	bool operator != (const Key_Pair<T>& other) const{
		return key != other.key;
	}
	bool operator > (const Key_Pair<T>& other) const{
		return key > other.key;
	}
	bool operator >= (const Key_Pair<T>& other) const{
		return key >= other.key;
	}
	bool operator < (const Key_Pair<T>& other) const{
		return key < other.key;
	}
	bool operator <= (const Key_Pair<T>& other) const{
		return key <= other.key;
	}
	void insert(const T& data) {
		chain.insert(data);
	} 
	void remove(const T& data) {
		chain.remove(data);
	}
	const LinkedList<T>& getList() const{
		return this->chain;
	}
	const Bigint& getKey() const{
		return this->key;
	}
	~Key_Pair() {

	}
};
