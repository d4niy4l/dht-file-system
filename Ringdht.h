#pragma once
#include<iostream>
#include "utlity.h"
#include "Machine.h"
#include "SHA1.hpp"
#include "CircularList.h"
#include "BigInt.h"
using namespace std;

class Ringdht {
	int identifierspace;
	Bigint size;
	CircularLinkedList<Machine> ring;
public:
	Ringdht(int s) : identifierspace(s), size(Bigint::power(2, s)) {}
	string hashFunction(string data) {
		SHA1 hasher;
		hasher.update(data);
		return hasher.final();
	}
	void insertMachine(string name) {

	}
};