#include <iostream>
#include <bitset>
#include <map>

using namespace std;

struct opCode {
	int operation;
	bitset<6> flags; //  n i x b p e -> 1 1 0 0 0 0
	int displacement;
	unsigned char format; // 1, 2, 3 or 4
	unsigned char reg1;
	unsigned char reg2;
};

map<string, int>* registers;

void fillRegMap();
