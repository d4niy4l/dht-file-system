#pragma once
#include<iostream>
#include "BigInt.h"
#include "LinkedList.h"
using namespace std;
class File {
	Bigint hash;
	string path;
	string name;
	File(Bigint hash, string path, string name) : hash(hash), path(path){
		
	
	}
};