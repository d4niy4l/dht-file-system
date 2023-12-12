#pragma once
#include <iostream>
#include "Ringdht.h"
using namespace std;
class System {
	Ringdht filesys;
	System(int size, int order) : filesys(size, order) {}
};