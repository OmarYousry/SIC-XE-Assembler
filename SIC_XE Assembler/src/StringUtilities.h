#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_
#include <string>
#include <iostream>
#include <vector>
#include "sstream"

using namespace std;

string intToString(int integer, bool hex);

void adjustStringLength(string* line, int length, char filling, bool lhs);

string toUpperCase(string x);

string trim(string x);

int parseDecimal(string x);

int parseHexaDecimal(string x);

float parseFloat(string x);

vector<string>* split(string x, char s);

#endif
