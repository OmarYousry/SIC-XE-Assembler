#ifndef IO_H_
#define IO_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "StringUtilities.h"

#define LINE_NUMBER_LENGTH 16;
#define ADDRESS_LENGTH 15;
#define LABEL_LENGTH 8;
#define MNEMONIC_LENGTH 8;
#define OPERANDS_LENGTH 16;
#define SPACE_CHAR 0x20;
#define ZERO_CHAR 0x30
#define ASTERISK_CHAR 0x2A;

using namespace std;

string constructLine(int lineNumber, string label, string op, string operands);

void deleteFile(string name);

void writeLine(string line, string name);

string readLine(ifstream* file);

void writeHeader();

void writeError(string error, string fileName);

#endif
