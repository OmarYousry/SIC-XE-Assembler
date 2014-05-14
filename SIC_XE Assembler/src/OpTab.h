#ifndef OPTAB_H_
#define OPTAB_H_

#include <map>
#include <string>

using namespace std;

const unsigned char FORMAT_1 = 1;
const unsigned char FORMAT_2 = 2;
const unsigned char FORMAT_3_4 = 3;

struct OpInfo {
	string mnmoneic;
	unsigned char format;
	unsigned char opCode;
};

map<string, OpInfo*>* opTab = NULL;

void fillOpTab();

map<string, OpInfo*>* getOpTab();

#endif
