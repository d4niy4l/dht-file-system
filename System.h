#pragma once
#include<iostream>
#include"Ringdht.h"
using namespace std;
class system{
    public:
Ringdht filesys;
Bigint noofmac;
System(int size, int order) : filesys(size, order) {}
void setmachines(){
    cout<<"enter total number of machines";
    cin>>noofmac;
}
void assignidtoeachmachine(){
    cout<<"Press -1 to skip a machine";
    Bigint i;
    while(i!=noofmac){
        string s;
        string name;
        cout<<"enter name of the machine"<<i;
        cin>>name;
        cout<<"enter the id of machine "<<i;
        cin>>s;
        if(s=="-1")
        {
            i++;
             filesys.insertMachine(name);
            continue;
        }
       filesys.insertMachine(name,s);
        i++;
    }
}
void insertafile(){
    string path;
    string machineid;
    cout<<"enter path of the file"<<endl;
    cin>>path;
    cout<<"enter the machineid you want to add through"<<endl;
    cin>>machineid;
    filesys.insertafile(path,machineid);
    //display the b tree
}
void deletefile(){
    string path;
    string machineid;
    cout<<"enter path of the file"<<endl;
    cin>>path;
    cout<<"enter machineid you want to add through"<<endl;
    cin>>machineid;
}
void addanewmachine(){
    string s;
        string name;
        cout<<"enter name of the machine"<<i;
        cin>>name;
        cout<<"enter the id of machine(enter -1 if you dont want to manually assigne the id) "<<i;
        cin>>s;
        if(s=="-1")
        {
             filesys.insertMachine(name);
             return;
        }
       filesys.insertMachine(name,s);
}
void removeamachine(){
    string s;
        cout<<"enter id of the machine"<<i;
        cin>>s;
        filesys.removeMachine(s);
}
};
