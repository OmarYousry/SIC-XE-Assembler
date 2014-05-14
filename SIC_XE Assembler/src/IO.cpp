#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define LINE_NUMBER_LENGTH 16;
#define ADDRESS_LENGTH 15;
#define LABEL_LENGTH 8;
#define MNEMONIC_LENGTH 8;
#define OPERANDS_LENGTH 16;
#define SPACE_CHAR 0x20;
#define ZERO_CHAR 0x30

using namespace std;

string intToString(int integer, bool hex); /* string handling */
string constructLine(int lineNumber, int address, string label, string op,
		string operands);
void adjustStringLength(string* line, int length, char filling, bool lhs); /* string handling */
void deleteFile(string name);
void writeLine(string line, string name);
string readLine(ifstream* file);

//int main() {
//	deleteFile("test.txt");
//
//	writeLine(constructLine(10, 11, "ALPHA", "LDA", "#10"), "test.txt");
//	writeLine(constructLine(20, 25, "BETA", "LDX", "TEN"), "test.txt");
//	writeLine(constructLine(30, 17, "", "LDT", "FIVE"), "test.txt");
//
//	ifstream file;
//	file.open("test.txt");
//
//	string line;
//	line = readLine(&file);
//	cout << line << endl;
//
//	line = readLine(&file);
//	cout << line << endl;
//
//	line = readLine(&file);
//	cout << line << endl;
//
//	return 0;
//}

string intToString(int integer, bool hex) {
	stringstream ss;
	string intAsStr;
	if (hex)
		ss << uppercase << std::hex << integer;
	else
		ss << integer;
	intAsStr = ss.str();
	return intAsStr;
}

void adjustStringLength(string* line, int length, char filling, bool lhs) {
	if (lhs)
		for (int i = line->length(); i < length; i++)
			*line = filling + *line;
	else
		for (int i = line->length(); i < length; i++)
			*line += filling;
}

string constructLine(int lineNumber, int address, string label, string op,
		string operands) {
	int length;
	char spaceChar = SPACE_CHAR
	;
	char zeroChar = ZERO_CHAR;
	string line;
	string lineNumberStr = intToString(lineNumber, false);
	length = LINE_NUMBER_LENGTH
	;
	string addressStr = intToString(address, true);
	adjustStringLength(&lineNumberStr, length, spaceChar, false);
	length = 6;
	adjustStringLength(&addressStr, length, zeroChar, true);
	length = ADDRESS_LENGTH
	;
	adjustStringLength(&addressStr, length, spaceChar, false);
	length = LABEL_LENGTH
	;
	adjustStringLength(&label, length, spaceChar, false);
	length = MNEMONIC_LENGTH
	;
	adjustStringLength(&op, length, spaceChar, false);
	length = OPERANDS_LENGTH
	;
	adjustStringLength(&operands, length, spaceChar, false);
	line = lineNumberStr + addressStr + label + op + operands;
	return line;
}

void deleteFile(string name) {
	if (remove(name.c_str()) == 0)
		cout << "file \"" << name << "\" was deleted" << endl;
	else
		cout << "error deleting " << name << endl;
}

void writeLine(string line, string name) {
	ofstream file;
	file.open("test.txt", std::ios_base::app);
	file << line << endl;
	file.close();
}

string readLine(ifstream* file) {
	string line = "";
	getline(*file, line);
	return line;
}
