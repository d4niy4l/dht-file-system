#include "Btree.h"
#include "RingDHT.h"
#include "SHA1.hpp"
#include "BigInt.h"
#include "utlity.h"
int main() {
	Ringdht sys(160,5);
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
	sys.showRoutingTables();
	
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\cases.png","11"); // HASH: 22
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt","11");  // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\ccases.png", "11"); // HASH: 22
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\ccases.png", "11"); // HASH: 22
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop (1).txt", "11"); // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop (1).txt", "11"); // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop (1).txt", "11"); // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop (1).txt", "11"); // HASH: 29
	Bigint a(28);
	sys.removeMachine(a);


	//	TODO: CHANGE QUEUE IN BTREE
	//	TODO: ADD COUT STATEMENTS
	//	TODO: ADD FUNCTIONALITY TO SHOW PATH WHEN USING searchFile()



	//sys.removeMachine(a);
	//cout << "------- DELETION --------\n";
	//sys.searchFile("29", "1");
	//sys.removeFile("22", "9");
	int i;
	cin >> i;

	//	SPLITTING CHECK
	//	NODE 18 REMOVED BEFORE -> FILE WITH HASH 15 STORED AT MACHINE 20 NOW
	//sys.insertMachine("machine 18", "18");
	sys.searchFile("22", "18");

	sys.insertMachine("machine 29", "29");
	//	HEREE 

	/*
	
		SEARCH FILE FUNCTION BELOW DOES NOT GET NODE 29 FOR THE FILE TO BE SEARCHED
	*/





	sys.searchFile("29", "1");
	cin >> i;
	/*
	n.insertion(4);
	n.insertion(10);
	n.insertion(2);
	n.insertion(12);
	n.insertion(30);
	n.insertion(43);
	n.insertion(3);
	n.insertion(1);
	n.insertion(54);
	n.insertion(64);
	n.insertion(60);
	n.insertion(92);
	n.insertion(90);
	n.insertion(70);
	n.insertion(66);*/

	/*n.insertion(1);
	n.insertion(2);
	n.insertion(3);
	n.insertion(4);
	n.insertion(5);
	n.insertion(6);
	n.insertion(7);
	n.insertion(8);
	n.insertion(9);
	n.insertion(10);
	n.insertion(11);
	n.insertion(12);
	n.insertion(13);
	n.insertion(14);
	n.insertion(15);
	n.insertion(16);
	n.insertion(17);
	n.insertion(18);
	n.insertion(19);
	n.insertion(20);

	n.traversal();*/
	//visualizeTree(generateDotCode(n.root));
}
