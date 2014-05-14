#include "IO.h"

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

int counter = 0;

string constructLine(int address, string label, string op, string operands) {
	int length;
	char spaceChar = SPACE_CHAR
	;
	char zeroChar = ZERO_CHAR;
	string line;
	string lineNumberStr = intToString(++counter, false);
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

void writeHeader() {

}

void writeError(string error, string fileName) {
	int errLength = error.length();
	int offset = 31 - errLength - 3;
	int excess;
	char spaceChar = SPACE_CHAR
	;
	char asterisk = ASTERISK_CHAR
	;

	adjustStringLength(&error, errLength + 3, asterisk, true);
	adjustStringLength(&error, errLength + offset, spaceChar, true);
	excess = 63 - errLength;

	adjustStringLength(&error, errLength + excess, spaceChar, false);

	writeLine(error, fileName);
}
