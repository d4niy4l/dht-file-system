#include "Btree.h"
#include "RingDHT.h"
#include "SHA1.hpp"
#include "BigInt.h"
#include "utlity.h"
int main() {
	
	//sys.showRoutingTables();
	
	

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
	string arr[] = { "1","4","9","11","14","15","20","18","28","21"};
	Ringdht sys(5,5); 
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		string name = "MACHINE " + arr[i];
		Bigint a(arr[i]);
		sys.insertMachine(name, a);
	}
	Bigint C = 15;
	// sys.removeMachine(C);
	sys.showRoutingTables();
	/*sys.insertMachine("machine 1", "1");
	sys.insertMachine("machine 3", "3");
	sys.insertMachine("machine 10", "10");
	sys.showRoutingTables();*/
	long fid = 29;
	 Bigint b(fid);
	Bigint mid(10);
	Machine* m = sys.searchMachine(b, mid);
	cout << "The node where file id " << fid << " should be inserted/searched/deleted is: ";
	if(m) m->printDetails();
}