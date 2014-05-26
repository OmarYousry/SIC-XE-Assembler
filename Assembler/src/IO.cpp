#include "IO.h"

//int main() {
//
//	deleteFile("test.txt");
//	map<string, int>* myMap = new map<string, int>();
//
//	myMap->insert(pair<string, int>("first",  10));
//	myMap->insert(pair<string, int>("second", 20));
//	myMap->insert(pair<string, int>("third",  30));
//	myMap->insert(pair<string, int>("forth",  40));
//	myMap->insert(pair<string, int>("fifth",  50));
//	myMap->insert(pair<string, int>("sixth",  60));
//
//	for (map<string, int>::iterator it = myMap->begin();
//					it != myMap->end(); ++it) {
//			cout << it->first << "\t" << it->second << "\n";
//
//		}
//
//	ofstream ofile;
//	ofile.open("test.txt", std::ios::app);
//	writeHeader(&ofile);
//	writeComment(&ofile, ".2345678901234567890");
//	writeLine(&ofile, constructLine(11, "ALPHA", "LDA", "#10"));
//	writeComment(&ofile, ".This is a comment line");
//	writeLine(&ofile, constructLine(11, "", "+LDA", "#10"));
//	writeLine(&ofile, constructLine(25, "BETA", "LDX", "TEN"));
//	writeLine(&ofile, constructLine(17, "", "LDT", "FIVE"));
//	writeError(&ofile, "this is an error\nthis is another error");
//	writeBorder(&ofile);
//	writeSymTab(&ofile, myMap);
//	ofile.close();
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
//	int i = '=';
//	cout << hex << i;
//
//	return 0;
//}

int counter = 0;

string constructLine(int address, string label, string op, string operands) {
	int length;
	char spaceChar = SPACE_CHAR;
	char zeroChar = ZERO_CHAR;
	string line;
	string lineNumberStr = intToString(++counter, false);
	length = LINE_NUMBER_LENGTH;
	string addressStr = intToString(address, true);
	adjustStringLength(&lineNumberStr, length, spaceChar, false);
	length = 6;
	adjustStringLength(&addressStr, length, zeroChar, true);
	length = ADDRESS_LENGTH;
	adjustStringLength(&addressStr, length, spaceChar, false);
	length = LABEL_LENGTH;
	if (op.at(0) == '+') length -= 1;
	adjustStringLength(&label, length, spaceChar, false);
	length = MNEMONIC_LENGTH;
	if (op.at(0) == '+') length += 1;
	adjustStringLength(&op, length, spaceChar, false);
	length = OPERANDS_LENGTH;
	adjustStringLength(&operands, length, spaceChar, false);
	line = lineNumberStr + addressStr + label + op + operands;
	return line;
}

void deleteFile(string name) {
	remove(name.c_str());

}

void writeLine(ofstream* file, string line)
{
	*file << line << endl;
}

string readLine(ifstream* file) {
	string line = "";
	getline(*file, line);
	return line;
}

void writeHeader(ofstream* file) {

	int fileLineLength = FILE_LINE_LENGTH;
	int lineNumberLength = LINE_NUMBER_LENGTH;
	int addressLength = ADDRESS_LENGTH;
	int labelLength = LABEL_LENGTH;
	int mnemonicLength = MNEMONIC_LENGTH;
	int operandsLength = OPERANDS_LENGTH;
	char spaceChar = SPACE_CHAR;
	char equalChar = EQUAL_CHAR;
	string line = "";
	line = "> > \t P a s s\t1 . . . \n";
	writeLine(file, line);
	line = "";
	string temp = "line number";
	adjustStringLength(&temp, lineNumberLength, spaceChar, false);
	line += temp;
	temp = "address";
	adjustStringLength(&temp, addressLength, spaceChar, false);
	line += temp;
	temp = "label";
	adjustStringLength(&temp, labelLength, spaceChar, false);
	line += temp;
	temp = "op";
	adjustStringLength(&temp, mnemonicLength, spaceChar, false);
	line += temp;
	temp = "operands";
	adjustStringLength(&temp, operandsLength, spaceChar, false);
	line += temp;
	writeLine(file, line);
	line = "";
	adjustStringLength(&line, fileLineLength, equalChar, false);
	writeLine(file, line);

}

void writeError(ofstream* file, string error) {
	vector<string> vecOfStrs = split(error, '\n');

	for (unsigned int i = 0; i < vecOfStrs.size(); i++) {
		error = vecOfStrs.at(i);
		int errLength = error.length();
		int offset = 19;
		int excess;
		char spaceChar = SPACE_CHAR;
		char asterisk = ASTERISK_CHAR;

		adjustStringLength(&error, errLength + 3, asterisk, true);
		adjustStringLength(&error, errLength + offset, spaceChar, true);
		excess = 63 - errLength;

		adjustStringLength(&error, errLength + excess, spaceChar, false);

		writeLine(file, error);

	}
}

void writeBorder(ofstream* file)
{
	char newLine = NEW_LINE_CHAR;
	int fileLineLength = FILE_LINE_LENGTH;
	string line = "";
	char asterickChar = ASTERISK_CHAR;
	for (int i = 0; i < fileLineLength; i++) line += asterickChar;
	writeLine(file, newLine + line + newLine);
}

void writeSymTab(ofstream* file, map<string, int>* symTab)
{
	if (symTab->empty()) return;
	char spaceChar = SPACE_CHAR;
	char dashChar = DASH_CHAR;
	char equalChar = EQUAL_CHAR;
	char zeroChar = ZERO_CHAR;
	string temp;
	writeLine(file, "> > \t s y m b o l\t\t t a b l e\t\t (values in hex)\n");
	temp = "";
	adjustStringLength(&temp, 25, equalChar, false);
	writeLine(file, temp);
	temp = "|\tname";
	adjustStringLength(&temp, 9, spaceChar, false);
	string headerLine = temp;
	temp = "address";
	adjustStringLength(&temp, 9, spaceChar, true);
	temp += "\t|";
	headerLine += temp;
	writeLine(file, headerLine);
	temp = "|\t";
	adjustStringLength(&temp, 18, dashChar, false);
	temp += "\t|";
	writeLine(file, temp);
	for (map<string, int>::iterator it = symTab->begin();
				it != symTab->end(); ++it) {
		string symbol = "|\t" + it->first;
		string address = intToString(it->second, true);
		adjustStringLength(&symbol, 9, spaceChar, false);
		string line = symbol;
		adjustStringLength(&address, 4, zeroChar, true);
		adjustStringLength(&address, 9, spaceChar, true);
		address += "\t|";
		line += address;
		writeLine(file, line);
	}
	temp = "";
	adjustStringLength(&temp, 25, equalChar, false);
	writeLine(file, temp);

}

void writeComment(ofstream* file, string comment) {
	int lineNumberLength = LINE_NUMBER_LENGTH;
	int addressLength = ADDRESS_LENGTH;
	char spaceChar = SPACE_CHAR;
	adjustStringLength(&comment, comment.size() + lineNumberLength + addressLength, spaceChar, true);
	writeLine(file, comment);
}
