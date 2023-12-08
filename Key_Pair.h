#pragma once
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
	Key_Pair() {};
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
};