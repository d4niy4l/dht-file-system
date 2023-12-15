#include "System.h"
#include "BigInt.h"

int main() {
	/*Ringdht sys(5,5);
	sys.insertMachine("machine 1","1");
	sys.insertMachine("machine 29", "29");
	//sys.insertMachine("machine 4","4");
	sys.insertMachine("machine 11", "11");
	//sys.showRoutingTables();
	//sys.insertMachine("machine 21");
	//sys.insertMachine("machine 14", "14");
	//sys.insertMachine("machine 20", "20");
	//sys.insertMachine("machine 18", "18");
	//sys.insertMachine("machine 28", "28");
	//sys.insertMachine("machine 21");
	//sys.showRoutingTables();
	cout << "--------------------\n";
	
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\ccases.png","11"); // HASH: 22
	cout << "--------------------\n";
	
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt","11");  // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\ccases.png", "11"); // HASH: 22
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\ccases.png", "11"); // HASH: 22
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt", "11"); // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt", "11"); // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt", "11"); // HASH: 29
	sys.insertFile("C:\\Users\\Ahmed\\Desktop\\poop.txt", "11"); // HASH: 29
	Bigint a(1);
	sys.removeMachine(a);


	//	TODO: CHANGE QUEUE IN BTREE
	//	TODO: ADD COUT STATEMENTS
	//	TODO: ADD FUNCTIONALITY TO SHOW PATH WHEN USING searchFile()



	//sys.removeMachine(a);
	//cout << "------- DELETION --------\n";
	//sys.searchFile("29", "1");
	//sys.removeFile("22", "9");
	int i;


	//	SPLITTING CHECK
	//	NODE 18 REMOVED BEFORE -> FILE WITH HASH 15 STORED AT MACHINE 20 NOW
	//sys.insertMachine("machine 18", "18");

	//sys.searchFile("22", "18");
	//	HEREE 

	/*
	
		SEARCH FILE FUNCTION BELOW DOES NOT GET NODE 29 FOR THE FILE TO BE SEARCHED
	*/
	/*
	cout << "----------------------------\n";

	sys.printAllMachines();
	cout << "----------------------------\n";




	sys.searchFile("15", "29");

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
	/*
	Bigint fid(1);
	Bigint mid(29);
	Machine* m = sys.searchMachine(fid, mid);
	m->printTree();	*/
int choice;
System system;

do {
    system.newsystem();
    cin >> choice;

    switch (choice) {
    case 1:
      
        int size, order;
        cout << left << setw(20) << "Identifier space: ";
        cin >> size;
        cout << left << setw(20) << "Order: ";
        cin >> order;
        system.setringdht(size, order);
        system.setmachines();
        system.assignidtoeachmachine();
        

        do {
            system.mainmenu();
            cin >> choice;
            switch (choice) {
            case 1:
                system.insertafile();
                break;
            case 2:
                system.deletefile();
                break;
            case 3:
                system.printroutingtable();
                break;
            case 4:
                system.addanewmachine();
                break;
            case 5:
                system.removeamachine();
                break;
            case 6:
                system.displaybtree();
                break;
            case 7:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
        break;
    case 2:
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
    }

} while (choice != 2);

return 0;
}
