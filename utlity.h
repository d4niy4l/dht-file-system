#pragma once
#include <iostream>
#include <fstream>
#include "BigInt.h"
using namespace std;
string hexaToBinary(string hex){
	string binary = "";
	for (int i = 0; i < hex.length(); ++i){
		if (hex[i] == '0') binary += "0000";
		else if (hex[i] == '1') binary += "0001";
		else if (hex[i] == '2') binary += "0010";
		else if (hex[i] == '3') binary += "0011";
		else if (hex[i] == '4') binary += "0100";
		else if (hex[i] == '5') binary += "0101";
		else if (hex[i] == '6') binary += "0110";
		else if (hex[i] == '7') binary += "0111";
		else if (hex[i] == '8') binary += "1000";
		else if (hex[i] == '9') binary += "1001";
		else if (hex[i] == 'a') binary += "1010";
		else if (hex[i] == 'b') binary += "1011";
		else if (hex[i] == 'c') binary += "1100";
		else if (hex[i] == 'd') binary += "1101";
		else if (hex[i] == 'e') binary += "1110";
		else if (hex[i] == 'f') binary += "1111";
	}
	return binary;
}
string getLastNBits(const string& binary, int bits) {
	string ans;
	int s = binary.length() - bits;
	for (int i = binary.length()-1; i >= s; i--) 
		ans += binary[i];
	return ans;
}
Bigint binaryToDecimel(string binary) {
	Bigint decimel;
	Bigint curr;
	for (int i = binary.length() - 1,j = 0; i >= 0; i--,j++) {
		curr = binary[i] - '0';
		decimel += (Bigint::power(2, j) * curr);
	}
	return decimel;
}
string getNameFromPath(const string& path) {
	string name;
	for (int i = path.length() - 1; i >= 0 && path[i] != '/' && path[i] != '\\'; i--) 
		name = path[i] + name;
	return name;
}

string getFileExtension(const string& path) {
	string ext;
	for (int i = path.length() - 1; i >= 0 && path[i] != '.'; i--)
		ext = path[i] + ext;
	ext = '.' + ext;
	return ext;
}
bool copyFile(const string& from, const string& destination) {
	ifstream source_File(from, ios::binary);
	ofstream dest_File(destination, ios::binary);
	if (!source_File) {
		cout << "Error opening source file " << endl;
		return false;
	}
	if (!dest_File) {
		cout << "Error opening destination file " << endl;
		return false;
	}
	dest_File << source_File.rdbuf();
	if (!dest_File) {
		cout << "Error copying file from " << from << " to " << destination << endl;
		return false;
	}
	return true;
}

