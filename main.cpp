#include "Btree.h"
#include "RingDHT.h"
#include "SHA1.hpp"
#include "BigInt.h"
#include "utlity.h"
int main() {
	const string input = "abc";

	SHA1 checksum;
	checksum.update(input);
	const string hash = checksum.final();

	cout << "The SHA-1 of \"" << input << "\" is: " << hash << endl;


	cout << "IN BINARY: " << hexaToBinary(hash) << endl;

	cout << binaryToDecimel("11111111") << endl;
	/*Bigint a("32");
	Bigint b("2");
	cout << a * b;
	cout << endl;
	Bigint c = a % 3;
	cout << c << endl;*/
	//9999999999999999999
	//9999999999999999999
	//9999999999999999999
	//cout << a - 1 << endl;
	
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