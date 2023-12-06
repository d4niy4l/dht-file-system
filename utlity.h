#pragma once
#include <iostream>
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
string getLastNBits(string binary, int bits) {
	string ans;
	for (int i = binary.length(); i >= binary.length() - bits; i--) 
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