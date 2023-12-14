#include "Btree.h"
#include "RingDHT.h"
#include "SHA1.hpp"
#include "BigInt.h"
#include "utlity.h"
int main() {
	Ringdht sys(5,5);
	sys.insertMachine("machine 1","1"); 
	sys.insertMachine("machine 4","4");
	sys.insertMachine("machine 9", "9");
	//sys.showRoutingTables();
	sys.insertMachine("machine 11", "11");
	sys.insertMachine("machine 14", "14");
	sys.insertMachine("machine 20", "20");
	sys.insertMachine("machine 18", "18");
	sys.insertMachine("machine 28", "28");
	sys.insertMachine("machine 21", "21");
	//sys.showRoutingTables();
	Bigint a(18);
	sys.removeMachine(a);
	string user = "";

	cout << "--------  FILE INSERTION ---------\n";
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\cases.png", "11"); // HASH: 8
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\ccases.png","11"); // HASH: 22
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt","11");	  // HASH: 15
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop (1).txt", "11"); // HASH: 29

	
	//sys.removeMachine(a);
	//cout << "------- DELETION --------\n";
	sys.searchFile("29", "1");
	sys.removeFile("22", "9");


	//	SPLITTING CHECK
	//	NODE 18 REMOVED BEFORE -> FILE WITH HASH 15 STORED AT MACHINE 20 NOW
	sys.insertMachine("NEW MACHINE LES GOO", "18");
	sys.searchFile("22", "18");

}
