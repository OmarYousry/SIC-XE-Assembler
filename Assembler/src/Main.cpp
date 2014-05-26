#include "Validate.h"
#include "Parser.h"
#include "IO.h"
#include "OpTab.h"
#include "StringUtilities.h"
#include <stdexcept>

map<string, OpInfo*>* mainOpTab;
map<string, int>* mainSymTab;

int locCtr;
bool ended;
bool started;
string errorMessage;

ifstream ipfile;
ofstream opfile;

int handelBYTE(string x) {
	string val = "";
	if (x.at(0) == 'x' || x.at(0) == 'X' || x.at(0) == 'c' || x.at(0) == 'C') {
		if (x.at(1) == '\'' && x.at(x.length() - 1) == '\'') {
			for (unsigned int i = 2; i < x.length() - 1; i++) {
				val += x.at(i);
			}
		} else {
			errorMessage += "\nnot a hexadecimal/character string";
			return 0;
		}
	} else {
		errorMessage += "\nillegal operand";
		return 0;
	}

	if (x.at(0) == 'c' || x.at(0) == 'C')
		return val.length();

	return val.length() % 2 == 0 ? val.length() / 2 : val.length() / 2 + 1;
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

void handleStreams(string in, string out) {
	ipfile.open(in.c_str());
	deleteFile(out.c_str());
	opfile.open(out.c_str(), std::ios::app);
}

void writeFomatted(parsedLine pl) {
	writeLine(&opfile,
			constructLine(locCtr, pl.lable, pl.opcode,
					mergeStrings(pl.operand1, pl.operand2, ',')));
}

void writeAndIncr(int incr, parsedLine pl) {
	if (!started) {
		started = true;
		locCtr = 0;
		writeFomatted(pl);
		addLableToSymTab(pl.lable);
		locCtr += incr;
		if (locCtr > 0x3039) {
			errorMessage += "\nout of range address";
		}
	} else if (started && !ended) {
		writeFomatted(pl);
		addLableToSymTab(pl.lable);
		locCtr += incr;
		if (locCtr > 0x3039) {
			errorMessage += "\nout of range address";
		}
	} else if (ended) {
		errorMessage += "\nDefinition After END";
	}
}

void getlocCtrIncr(parsedLine pl) {
	int incr = validate(pl);
	if (incr == -1) { // Directive
		if (toUpperCase(pl.opcode).compare("START") == 0) {
			if (!started) {
				started = true;
				locCtr = parseHexaDecimal(pl.operand1);
				if (locCtr > 0x3038) {
					errorMessage += "\nout of range address";
				}
				writeFomatted(pl);
				addLableToSymTab(pl.lable);
			} else {
				errorMessage += "\nMisplaced START";
			}
		} else if (toUpperCase(pl.opcode).compare("END") == 0) {
			if (!started) {
				errorMessage += "\nEnded before START";
			} else if (started && !ended) {
				ended = true;
				if(locCtr >= 0x3039){
					errorMessage += "\nout of range address";
				}
				writeFomatted(pl);
				addLableToSymTab(pl.lable);
			} else if (ended) {
				errorMessage += "\nMultiple END clauses.";
			}
		} else if (toUpperCase((pl.opcode)).compare("BYTE") == 0) {
			writeAndIncr(handelBYTE(pl.operand1), pl);
		} else if (toUpperCase((pl.opcode)).compare("WORD") == 0) {
			writeAndIncr(3, pl);
		} else if (toUpperCase((pl.opcode)).compare("RESB") == 0) {
			writeAndIncr(parseDecimal(pl.operand1), pl);
		} else if (toUpperCase((pl.opcode)).compare("RESW") == 0) {
			writeAndIncr(parseDecimal(pl.operand1) * 3, pl);
		}
	} else { //Operations (formats)
		if (!started) {
			started = true;
			locCtr = 0;
			writeFomatted(pl);
			addLableToSymTab(pl.lable);
			locCtr += incr;
			if (locCtr > 0x3039) {
				errorMessage += "\nout of range address";
			}
		} else if (started && !ended) {
			writeFomatted(pl);
			addLableToSymTab(pl.lable);
			locCtr += incr;
			if (locCtr > 0x3039) {
				errorMessage += "\nout of range address";
			}
		} else if (ended) {
			errorMessage += "\nDefinition After END";
		}
	}
}

parsedLine readAndParse() {
	string before = readLine(&ipfile);
	string x = trim(before);
	return parse(x);
}

bool isComment(parsedLine pl) {

	return trim(pl.opcode).at(0) == '.';
}

bool isEmptyLine(parsedLine pl) {
	if (pl.lable.compare("") == 0 && pl.opcode.compare("") == 0
			&& pl.operand1.compare("") == 0 && pl.operand2.compare("") == 0)
		return true;

	return false;
}

int main(int argc, char **argv) {
	parsedLine pl;
	ended = false;
	started = false;
	locCtr = 0;
	initTables();

	if (argc != 2) {
		cout << "\aInvalid number of parameters" << endl;
		return 1;
	}
	handleStreams(argv[1], "/tmp/pass1_op.txt");
	writeHeader(&opfile);

	while (!ipfile.eof()) {

		try {
			pl = readAndParse();
		} catch (string* e) {
			writeFomatted(pl);
			errorMessage += "\n";
			errorMessage += *e;
			delete e;
		}

		if (isEmptyLine(pl)) {
			continue;
		}

		if (isComment(pl)) {
			writeComment(&opfile, pl.opcode);
			continue;
		}

		try {
			getlocCtrIncr(pl);
		} catch (string* e) {
			writeFomatted(pl);
			errorMessage += "\n";
			errorMessage += *e;
			delete e;
		}

		if (errorMessage.compare("") != 0) {
			writeError(&opfile, errorMessage);
			errorMessage = "";
		}
	}

	if (!ended) {
		writeError(&opfile, "The program has no END clause");
	}
	writeBorder(&opfile);
	writeSymTab(&opfile, mainSymTab);
	opfile.close();
	ipfile.close();
	deleteOpTab();
	deleteSymTab();

	return 0;
}
