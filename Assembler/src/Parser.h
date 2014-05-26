#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <string>

using namespace std;

struct parsedLine {
	string lable;
	string opcode;
	string operand1;
	string operand2;
};

parsedLine parse(string line);

#endif
