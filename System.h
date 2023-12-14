#pragma once
#include<iostream>
#include"Ringdht.h"
using namespace std;
class System {
public:
    Ringdht filesys;
    Bigint noofmac;

    System(int size, int order) : filesys(size, order) {}

    void setmachines() {
        cout << left << setw(20) << "---------------------------------------" << endl;
        cout << left << setw(20) << "||        NUMBER OF MACHINES          ||" << endl;
        cout << left << setw(20) << "---------------------------------------" << endl;
        cout << left << setw(20) << "||  1. Enter total number of machines: ||" << endl;
        cout << left << setw(20) << "---------------------------------------" << endl;

        cout << "NUMBER OF MACHINES: ";
        cin >> noofmac;
        filesys.setMaxMachines(noofmac);
    }

    void assignidtoeachmachine() {
        Bigint i = 0;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||     MANUALLY ASSIGN IDs        ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||    1. Enter name of machine    ||" << endl;
        cout << left << setw(20) << "||    2. Enter machine ID         ||" << endl;
        cout << left << setw(20) << "||  (Press -1 to skip a machine   ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;

        while (i != noofmac) {
            string s;
            string name;

            cout << left << setw(20) << "Name of machine " << i << ": ";
            cin >> name;
            cout << left << setw(20) << "Enter machine ID " << i << ": ";
            cin >> s;
            if (s == "-1") {
                i++;
                filesys.insertMachine(name);
                continue;
            }
            filesys.insertMachine(name, s);
            i++;
        }
    }

    void insertafile() {
        cout << left << setw(20) << "----------------------------------" << endl;
        cout << left << setw(20) << "||        INSERT A FILE          ||" << endl;
        cout << left << setw(20) << "----------------------------------" << endl;
        cout << left << setw(20) << "||     1. Enter Path of file     ||" << endl;
        cout << left << setw(20) << "||   2. Enter the machine id     ||" << endl;
        cout << left << setw(20) << "---------------------------------" << endl;
        string path;
        string machineid;

        cout << left << setw(20) << "Path: ";
        cin >> path;
        cout << left << setw(20) << "Machine ID: ";
        cin >> machineid;
        filesys.insertafile(path, machineid);
        // display the b tree
    }

    void deletefile() {
        cout << left << setw(20) << "---------------------------------" << endl;
        cout << left << setw(20) << "||        DELETE A FILE         ||" << endl;
        cout << left << setw(20) << "----------------------------------" << endl;
        string path;
        string machineid;
        cout << left << setw(20) << "Path: ";
        cin >> path;
        cout << left << setw(20) << "Machine ID: ";
        cin >> machineid;
    }

    void addanewmachine() {
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||         ADD A MACHINE          ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||    1. Enter name of machine    ||" << endl;
        cout << left << setw(20) << "||    2. Enter machine ID         ||" << endl;
        cout << left << setw(20) << "||  (Press -1 to skip a machine   ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        string s;
        string name;
        cout << left << setw(20) << "Name: ";
        cin >> name;
        cout << left << setw(20) << "Machine ID: ";
        cin >> s;
        if (s == "-1") {
            filesys.insertMachine(name);
            return;
        }
        filesys.insertMachine(name, s);
    }

    void removeamachine() {
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||       DELETE A MACHINE         ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        cout << left << setw(20) << "||     1. Enter ID of machine     ||" << endl;
        cout << left << setw(20) << "-----------------------------------" << endl;
        string s;
        cout << left << setw(20) << "Machine ID: ";
        cin >> s;
        filesys.removeMachine(s);
    }
};
