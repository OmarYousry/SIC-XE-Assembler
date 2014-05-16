#include "Validate.h"
#include "Parser.h"
#include "IO.h"
#include "OpTab.h"
#include "StringUtilities.h"
#include <stdexcept>

map<string, OpInfo*>* mainOpTab;
map<string, int>* mainSymTab;

int locCtr;

string errorMessage;

ifstream ipfile;
ofstream opfile;

int handelBYTE(string x) {
	string val = "";
	if (x.at(0) == 'x' || x.at(0) == 'X' || x.at(0) == 'c' || x.at(0) == 'C') {
		if (x.at(0) == '\'' && x.at(x.length() - 1) == '\'') {
			for (unsigned int i = 2; i < x.length() - 1; i++) {
				val += x.at(i);
			}
		} else {
			return -1;
		}
	} else {
		return -1;
	}

	if (x.at(0) == 'c' || x.at(0) == 'C')
		return val.length();

	return val.length() % 2 == 0 ? val.length() / 2 : val.length() / 2 + 1;
}

void setErrorMessage(string x) {
	errorMessage = x;
}

void addLableToSymTab(string x) {
	if (x.compare("") != 0) {
		try {
			mainSymTab->at(x);
			errorMessage += "\nduplicate label definition";
		} catch (out_of_range& oor) {
			mainSymTab->insert(pair<string, int>(x, locCtr));
		}
	}
}

void deleteSymTab() {
	mainSymTab->clear();
	delete mainSymTab;
}

void initTables() {
	mainOpTab = getOpTab();
	mainSymTab = new map<string, int>();
}

void handleStreams() {
	ipfile.open("pass1.txt");
	deleteFile("pass1_op.txt");
	opfile.open("pass1_op.txt", std::ios::app);
}

int getlocCtrIncr(parsedLine pl) {
	int incr = validate(pl);

	if (incr == -1) {
		if (toUpperCase((pl.opcode)).compare("BYTE") == 0) {
			incr = handelBYTE(pl.operand1);
		} else if (toUpperCase((pl.opcode)).compare("WORD") == 0) {
			incr = 3;
		} else if (toUpperCase((pl.opcode)).compare("RESB") == 0) {
			incr = parseDecimal(pl.operand1) * 1;
		} else if (toUpperCase((pl.opcode)).compare("RESW") == 0) {
			incr = parseDecimal(pl.operand1) * 3;
		}
	}

	return incr;
}

bool isEndofProgram(string x) {
	return toUpperCase(x).compare("END") == 0;
}

parsedLine readAndParse() {
	return parse(readLine(&ipfile));
}

int main(int argc, char **argv) {
	parsedLine pl;
	int incr;

	initTables();
	handleStreams();
	pl = readAndParse();

	if ((toUpperCase(pl.opcode)).compare("START") == 0) {
		locCtr = parseDecimal(pl.operand1);
	} else {
		locCtr = 0;
	}

	while (1) {
		pl = readAndParse();
		addLableToSymTab(pl.lable);

		if (isEndofProgram(pl.opcode))
			break;

		try {
			incr = getlocCtrIncr(pl);
		} catch (string* e) {
			errorMessage += "\n" + *e;
			//incr = 0;
		}

		writeLine(&opfile,
				constructLine(locCtr, pl.lable, pl.opcode,
						mergeStrings(pl.operand1, pl.operand2, ',')));

		if (errorMessage.compare("") != 0) {
			writeError(&opfile, errorMessage);
			errorMessage = "";
		}
//		else {
//			locCtr += incr;
//		}
		locCtr += incr;
	}

	writeBorder(&opfile);
	writeSymTab(&opfile, mainSymTab);
	opfile.close();
	ipfile.close();
	deleteOpTab();
	deleteSymTab();
}
