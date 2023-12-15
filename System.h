#pragma once
#include<iostream>
#include"Ringdht.h"
using namespace std;
class System {
public:
    Ringdht *filesys;
    Bigint noofmac;
    System() { filesys = nullptr; }

    void setringdht(int size, int order) {
        filesys = new Ringdht(size, order);
    }

    void setmachines() {
        cout << left << setw(20) << "---------------------------------------" << endl;
        cout << left << setw(20) << "||        NUMBER OF MACHINES          ||" << endl;
        cout << left << setw(20) << "---------------------------------------" << endl;
        cout << left << setw(20) << "||  1.Enter total number of machines: ||" << endl;
        cout << left << setw(20) << "---------------------------------------" << endl;

        cout << "NUMBER OF MACHINES: ";
        cin >> noofmac;
    }
    void assignidtoeachmachine() {
        Bigint i = 0;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||     MANUALLY ASSIGN IDs       ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||    1.Enter name of machine    ||" << endl;
        cout << left << setw(20) << "||    2.Enter machine ID         ||" << endl;
        cout << left << setw(20) << "||  (Press -1 to skip a machine  ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;

        while (i < noofmac) {
            string s;
            string name;
            std::cout << std::left << std::setw(20) << "Name of machine " << i << ": ";
            if(i.str() == "0")
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, name);

            std::cout << std::left << std::setw(20) << "Enter machine ID " << i << ": ";
            std::getline(std::cin, s);
            if (s == "-1") {
                i++;
                filesys->insertMachine(name);
                continue;
            }
            filesys->insertMachine(name, s);
            i++;
        }
    }


    void insertafile() {
        cout << left << setw(20) << "---------------------------------" << endl;
        cout << left << setw(20) << "||        INSERT A FILE         ||" << endl;
        cout << left << setw(20) << "----------------------------------" << endl;
        cout << left << setw(20) << "||     1.Enter Path of file     ||" << endl;
        cout << left << setw(20) << "||   2. Enter the machine id    ||" << endl;
        cout << left << setw(20) << "---------------------------------" << endl;
        string path;
        string machineid;

        cout << left << setw(20) << "Path: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, path);
        cout << left << setw(20) << "Machine ID: ";
        std::getline(std::cin, machineid);
        filesys->insertFile(path, machineid);
        // display the b tree
    }

    void deletefile() {
        cout << left << setw(20) << "------------------------------------------------" << endl;
        cout << left << setw(20) << "||                 DELETE A FILE              ||" << endl;
        cout << left << setw(20) << "-----------------------------------------------" << endl;
        cout << left << setw(20) << "|| 1. Enter Machine id you want to delete from||" << endl;
        cout << left << setw(20) << "|| 2. Enter file hash                         ||" << endl;
        cout << left << setw(20) << "-----------------------------------------------" << endl;
        string machineid;
        string filehash;
        cout << left << setw(20) << "machine id: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, machineid);
        cout << left << setw(20) << "File hash: ";
        std::getline(std::cin, filehash);
        filesys->removeFile(filehash, machineid);
    }

    void addanewmachine() {
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||         ADD A MACHINE         ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||    1.Enter name of machine    ||" << endl;
        cout << left << setw(20) << "||    2.Enter machine ID         ||" << endl;
        cout << left << setw(20) << "||  (Press -1 to skip a machine  ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        string s;
        string name;
        cout << left << setw(20) << "Name: ";
        std::cin.ignore(); // Clear input buffer
        std::getline(std::cin, name);
        std::cout << std::left << std::setw(20) << "Enter machine ID " << ": ";
        std::getline(std::cin, s);
        if (s == "-1") {
            filesys->insertMachine(name);
            return;
        }
        filesys->insertMachine(name, s);
    }

    void removeamachine() {
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||       DELETE A MACHINE         ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||     1.Enter ID of machine      ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        Bigint s;
        cout << left << setw(20) << "Machine ID: ";
        cin >> s;
        filesys->removeMachine(s);
    }

    void mainmenu() {
        cout << left << setw(20) << "-------------------------------------------------------" << endl;
        cout << left << setw(20) << "||                    MAIN MENU                      ||" << endl;
        cout << left << setw(20) << "-------------------------------------------------------" << endl;
        cout << left << setw(20) << "||1.Do you want to insert a file                     ||" << endl; // complete path taken //Show b tree
        cout << left << setw(20) << "||2.Do you want to delete a file                     ||" << endl; // complete path taken //Show b tree
        cout << left << setw(20) << "||3.do you want to print the routing table           ||" << endl;
        cout << left << setw(20) << "||4.do you want to add a new machine                 ||" << endl;
        cout << left << setw(20) << "||5.do you want to delete a machine                  ||" << endl;
        cout << left << setw(20) << "||6.do you want to print b tree                      ||" << endl;
        cout << left << setw(20) << "||7.do you want to print all machines                ||" << endl;
        cout << left << setw(20) << "||8.Exit                                             ||" << endl;
        cout << left << setw(20) << "-------------------------------------------------------" << endl;
        cout << left << setw(20) << "Enter your choice: ";
    }

    void newsystem() {
        cout << left << setw(20) << "-------------------------------------------------------" << endl;
        cout << left << setw(20) << "||        InterPlanetary File System (IPFS)          ||" << endl;
        cout << left << setw(20) << "-------------------------------------------------------" << endl;
        cout << left << setw(20) << "||1.create a new system                              ||" << endl;
        cout << left << setw(20) << "||2.Exit                                             ||" << endl;
        cout << left << setw(20) << "-------------------------------------------------------" << endl;
        cout << left << setw(20) << "Enter your choice: ";
    }

    void printroutingtable() {
        int choice;
        cout << left << setw(20) << "----------------------------------------" << endl;
        cout << left << setw(20) << "||           ROUTING TABLES            ||" << endl;
        cout << left << setw(20) << "----------------------------------------" << endl;
        cout << left << setw(20) << "||1.Routing tables of all machines     ||" << endl;
        cout << left << setw(20) << "||2.Routing Table of a specific machine||" << endl;
        cout << left << setw(20) << "-----------------------------------------" << endl;
        cout << left << setw(20) << "Enter your choice: ";
        cin >> choice;
        string machineid;
        switch (choice) {
        case 1:
            filesys->showRoutingTables();
            break;
        case 2:
            cout << left << setw(20) << "Machine ID: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, machineid);
            filesys->printRoutingTable(machineid);
        }
    }
    void displaybtree() {
        cout << left << setw(20) << "---------------------------" << endl;
        cout << left << setw(20) << "||        B-TREES         ||" << endl;
        cout << left << setw(20) << "----------------------------" << endl;
        cout << left << setw(20) << "|| 1.Enter machine id     ||" << endl;
        cout << left << setw(20) << "----------------------------" << endl;
        Bigint s;
        cout << left << setw(20) << "Machine ID :" << endl;
        cin >> s;
        Machine *m;
        m=filesys->getOrigin(s);
        m->printTree();
    }
    void displayavailablemachines() {
        cout << left << setw(20) << "---------------------------" << endl;
        cout << left << setw(20) << "||        MACHINES        ||" << endl;
        cout << left << setw(20) << "----------------------------" << endl;
        filesys->printAllMachines();
    }
    void deleteringdht() {
        delete filesys;
    }
    ~System() {
    }

};
