#ifndef IO_H_
#define IO_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "StringUtilities.h"

#define FILE_LINE_LENGTH 63;
#define LINE_NUMBER_LENGTH 16;
#define ADDRESS_LENGTH 15;
#define LABEL_LENGTH 9;
#define MNEMONIC_LENGTH 8;
#define OPERANDS_LENGTH 16;
#define SPACE_CHAR 0x20;
#define ZERO_CHAR 0x30
#define ASTERISK_CHAR 0x2A;
#define DASH_CHAR 0x2D;
#define NEW_LINE_CHAR 0x0A;
#define EQUAL_CHAR 0x3D;
#define TAB_CHAR 0x09;

using namespace std;

string constructLine(int lineNumber, string label, string op, string operands);

void deleteFile(string name);

void writeLine(ofstream* file, string line);

string readLine(ifstream* file);

void writeHeader(ofstream* file);

void writeError(ofstream* file, string error);

void writeBorder(ofstream* file);

void writeSymTab(ofstream* file, map<string, int>* symTab);

void writeComment(ofstream* file, string comment);

#endif
