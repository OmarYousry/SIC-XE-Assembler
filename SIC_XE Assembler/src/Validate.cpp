#include "Validate.h"
#include "OpTab.h"
#include <string>
#include "StringUtilities.h"

string reg[] = { "A", "X", "L", "B", "S", "T", "F" };
map<string, char>* directives = new map<string,char>();
int validate(parsedLine pl) {

	fillDirectives();
	string opCode = toUpperCase(pl.opcode);
	map<string, OpInfo*>* op = getOpTab();
	map<string, OpInfo*>::iterator it;
	map<string, char>::iterator it2;
	string l = toUpperCase(pl.lable);
	string o1 = toUpperCase(pl.operand1);
	string o2 = toUpperCase(pl.operand2);
	int ret = -1;
	cout << "label  : " << l << endl << "opCode : " << opCode << endl
			<< "op 1   : " << o1 << endl << "op 2   : " << o2 << endl;
	if (o2.at(0) == ',')
		throw new string("Extra characters");

	it = op->find(l);
	it2 = directives->find(l);
	if(it2 != directives->end() || it != op->end()){
		throw new string("Invalid Label field");
	}
	it2 = directives->find(opCode);
	if (it2 != directives->end()) {

		if (opCode.compare("START") == 0) {
			if (!isHexa(o1) || o2.compare("") != 0)
				throw new string("START error");
		} else if (opCode.compare("END") == 0) {
			if (o2.compare("") != 0)
				throw new string("END error");
		} else {
			if (o2.compare("") != 0)
				throw new string("Invalid operands , directives");
			if (o1.compare("") == 0)
				throw new string("missing operands , directives");
			if (!isNumeric(o1))
				throw new string("not numeric operand");
		}

	} else if (opCode.at(0) == '+') {
		opCode = opCode.substr(1, opCode.length() - 1);
		it = op->find(opCode);
		if ((it->second->format) != FORMAT_3_4) {
			if (f34(opCode, o1, o2) == 3)
				ret = 4;
		}
	} else {
		it = op->find(opCode);

		if (it == op->end()) {
			throw new string("Invalid opcode");
		} else {

			if ((it->second->format) == FORMAT_1) {
				ret = f1(o1, o2);
			} else if (it->second->format == FORMAT_2) {
				ret = f2(opCode, o1, o2);
			} else // (it->second->format == FORMAT_3_4)
			{
				ret = f34(opCode, o1, o2);
			}

//			if ((it->second->format) == FORMAT_1) {
//				if (o1.compare("") != 0 || o2.compare("") != 0)
//					throw new string("Invalid format 1");
//
//			} else if (it->second->format == FORMAT_2) {
//				if (opCode.compare("TIXR") == 0 || opCode.compare("SVC") == 0
//						|| opCode.compare("CLEAR") == 0) {
//					if (o2.compare("") != 0)
//						throw new string("Invalid format 2");
//					if (o1.compare("") == 0)
//						throw new string("Invalid format 2");
//				} else {
//					if (o1.compare("") == 0 || o2.compare("") == 0)
//						throw new string("Invalid format 2");
//				}
//			} else if (it->second->format == FORMAT_3_4) {
//				if (opCode.compare("RSUB") == 0) {
//					if (o1.compare("") != 0 || o2.compare("") != 0)
//						throw new string("Invalid format 3/4 1");
//				} else if (o2.compare("X") == 0) {
//					if (o1.compare("") == 0)
//						throw new string("Invalid format 3/4 2");
//				} else {
//					if (o2.compare("") != 0)
//						throw new string("Invalid format 3/4 3");
//					if (o1.compare("") == 0)
//						throw new string("Invalid format 3/4 4");
//				}
//			}

		}

	}
	return ret;
}

int f1(string o1, string o2) {
	if (o1.compare("") != 0 || o2.compare("") != 0)
		throw new string("Invalid format 1");
	return 1;
}
int f2(string op, string o1, string o2) {
	if (op.compare("CLEAR") == 0 || op.compare("TIXR") == 0) {
		if (o2.compare("") != 0)
			throw new string("Invalid format 2");
		if (!isReg(o1))
			throw new string("Invalid format 2 / not reg");

	} else if (op.compare("SVC") == 0) {
		if (o2.compare("") != 0)
			throw new string("Invalid format 2");
		if (!isNumeric(o1))
			throw new string("Invalid format 2");
	} else if (op.compare("SHIFTL") == 0 || op.compare("SHIFTR") == 0) {
		if (o1.compare("") == 0 || o2.compare("") == 0)
			throw new string("Invalid format 2");
		if (!isReg(o1))
			throw new string("Invalid format 2");
		if (!isNumeric(o2))
			throw new string("Invalid format 2");
	} else {
		if (!isReg(o1) || !isReg(o2))
			throw new string("Invalid format 2");
	}
	return 2;
}
int f34(string op, string o1, string o2) {
	if (op.compare("RSUB") == 0) {
		if (o1.compare("") != 0 || o2.compare("") != 0)
			throw new string("Invalid format 3/4 1");
	}
	if (o2.compare("") != 0)
		if (o2.compare("X") != 0)
			throw new string("Invalid format 3/4");
	if (o1.compare("") == 0)
		throw new string("Invalid format 3/4");

	return 3;
}
bool isReg(string o) {
	for (int i = 0; i < 7; i++) {
		if (o.compare(reg[i]) == 0)
			return true;
	}
	return false;
}
bool isNumeric(string s) {
	if (s.length() == 0)
		return false;
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) - '0' < 0 || s.at(i) - '0' > 9)
			return false;
	}
	return true;
}
bool isHexa(string s) {
	if (s.length() == 0)
		return false;
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) != 'A' && s.at(i) != 'B' && s.at(i) != 'C' && s.at(i) != 'D'
				&& s.at(i) != 'E' && s.at(i) != 'F'
				&& (s.at(i) - '0' < 0 || s.at(i) - '0' > 9))
			return false;
	}
	return true;
}
void fillDirectives() {

	directives->insert(pair<string, char>("BYTE", 'a'));
	directives->insert(pair<string, char>("WORD", 'a'));
	directives->insert(pair<string, char>("RESB", 'a'));
	directives->insert(pair<string, char>("RESW", 'a'));
	directives->insert(pair<string, char>("START", 'a'));
	directives->insert(pair<string, char>("END", 'a'));
	directives->insert(pair<string, char>("ORG", 'a'));
	directives->insert(pair<string, char>("EQU", 'a'));
	directives->insert(pair<string, char>("BASE", 'a'));
	directives->insert(pair<string, char>("NOBASE", 'a'));
	directives->insert(pair<string, char>("LTORG", 'a'));
}

//int main() {
//
//	try {
//		cout<<validate(parse("         LDA     BETA"))<<endl;
//
//	} catch (string* e) {
//		cout << *e << endl;
//	}
//
//	return 0;
//}
