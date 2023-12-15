/************************************************************************
TITLE: VECTOR
DESCRIPTION:
AUTHOR: HAFIZA IQRA [22I-1269]
COAUTHOR: MUHAMMAD AHMAD [22I-1056]
COAUTHOR: DANIYAL AHMED [22I-1032]
DATE: MONDAY 15-12-2023
LASTEDITBY: MUHAMMAD AHMAD
*************************************************************************/
#include "System.h"
#include "BigInt.h"

int main() {
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
                        system.displayavailablemachines();
                        break;
                    case 8:
                        system.deleteringdht();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice != 8);
                break;
            case 2:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }

        } while (choice != 2);

        return 0;
}
