#include "Validate.h"
#include "OpTab.h"
#include <string>
#include "StringUtilities.h"

string reg[] = { "A", "X", "L", "B", "S", "T", "F" };
map<string, char>* directives = new map<string, char>();
int validate(parsedLine pl) {
	fillDirectives();
	string opCode = toUpperCase(pl.opcode);
	map<string, OpInfo*>* op = getOpTab();
	map<string, OpInfo*>::iterator it;
	map<string, char>::iterator it2;
	string label =pl.lable;
	if(isRubbish(label))
	{
		throw new string("Invalid declaration of Label Field");
	}
	string o1 = toUpperCase(pl.operand1);
	string o2 = toUpperCase(pl.operand2);
	int ret = -1;
//	cout << "label  : " << l << endl << "opCode : " << opCode << endl
//			<< "op 1   : " << o1 << endl << "op 2   : " << o2 << endl;

	if (o2.compare("") != 0 && o2.at(0) == ',')
		throw new string("Extra characters");
	label = toUpperCase(label);
	it = op->find(label);
	it2 = directives->find(label);
	//if label is reserved word
	if (it2 != directives->end() || it != op->end()) {
//		cout << "the wrong label " << l << endl;
		throw new string("Invalid Label field");
	}

	it2 = directives->find(opCode);
	//IF directive
	if (it2 != directives->end()) {
		if (opCode.compare("BYTE") == 0) {
			if (o1.compare("") != 0) {
				if (!checkBYTE(o1) || o2.compare("") != 0)
					throw new string("Invalid operands  for Byte");
			} else {
				throw new string("Invalid operands for Byte");
			}
		} else if (opCode.compare("START") == 0) {
			if (!isHexa(o1) || o2.compare("") != 0)
				throw new string("START ERROR");
		} else if (opCode.compare("END") == 0) {
			if (o2.compare("") != 0)
				throw new string("END error");
		} else if (opCode.compare("EQU") == 0) {
			if (label.compare("") == 0)
				throw new string("Missing label Field in Equate");
			if (o2.compare("") != 0)
				throw new string("Invalid operands , directives");
			if (o1.compare("") == 0)
				throw new string("missing operands , directives");
		} else if (opCode.compare("ORG") == 0 || opCode.compare("BASE") == 0) {
			if (label.compare("") != 0)
				throw new string("Label Field should be Empty");
			if (o2.compare("") != 0)
				throw new string("Invalid operands , directives");
			if (o1.compare("") == 0)
				throw new string("missing operands , directives");
		} else if (opCode.compare("LTORG") == 0
				|| opCode.compare("NOBASE") == 0) {
			if (label.compare("") != 0)
				throw new string("Label Field should be Empty");
			if (o2.compare("") != 0 || o1.compare("") != 0)
				throw new string("operand fields should be kept empty");
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
		if (it == op->end()) {
			throw new string("Invalid opcode field");
		}
		if ((it->second->format) == FORMAT_3_4) {
			if (f34(opCode, o1, o2) == 3)
				ret = 4;
		}
	} else {

		it = op->find(opCode);

		if (it == op->end()) {
			throw new string("Invalid opcode 1");
		} else {

			if ((it->second->format) == FORMAT_1) {
				ret = f1(o1, o2);
			} else if (it->second->format == FORMAT_2) {
				ret = f2(opCode, o1, o2);
			} else // (it->second->format == FORMAT_3_4)
			{
				ret = f34(opCode, o1, o2);
			}
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
			throw new string("Invalid format 3/4");
		else
			return 3;
	} else if (o1.at(0) == '=') {
		if (op.compare("LDCH") == 0) {
			if (!checkLiteral(o1, false) || o2.compare("") != 0) {
				throw new string("Invalid Literal");
			}
		} else {
			if (!checkLiteral(o1, true) || o2.compare("") != 0) {
				throw new string("Invalid Literal");
			}
		}
	} else {
		if (o2.compare("") != 0)
			if (o2.compare("X") != 0)
				throw new string("Invalid format 3/4");
		if (o1.compare("") == 0)
			throw new string("Invalid format 3/4");
	}
	return 3;
}
bool isReg(string o) {
	for (int i = 0; i < 7; i++) {
		if (o.compare(reg[i]) == 0)
			return true;
	}
	return false;
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
bool checkBYTE(string x) {
//	cout<<x<<endl;
	if (x.at(0) == 'X' || x.at(0) == 'C') {
		if (!(x.length() > 0
				&& (x.at(1) == '\'' && x.at(x.length() - 1) == '\'')))
			throw new string("not a hexadecimal\\character string");
		else {
//			cout<<"aaaaaaaaa"<<endl;
			return true;
		}
	}
	throw new string("Illegal operand");
}
bool checkLiteral(string x, bool isReg) {
	if (x.at(0) == '=') {
		if (x.at(1) == 'X') {
			if (x.length() >= 2) {
				if (x.at(2) == '\'' && x.at(x.length() - 1) == '\'') {
					int numChars = x.length() - 4;
					string inner = x.substr(3, x.length() - 2);
					if (!isHexa(inner))
						throw new string("Invalid operands for Literal");
					if (isReg && numChars == 6)
						return true;
					else if (!isReg && numChars == 2)
						return true;
					else
						throw new string("Invalid Literal Length");
				}
			} else {
				throw new string("Invalid Literal");
			}
		} else if (x.at(1) == 'C') {
			if (x.length() > 0) {
				if (x.at(2) == '\'' && x.at(x.length() - 1) == '\'') {
					int numChars = x.length() - 4;
					if (isReg && numChars == 3)
						return true;
					else if (!isReg && numChars == 1)
						return true;
					else
						throw new string("Invalid Literal Length");
				}
			} else {
				throw new string("Invalid Literal");
			}
		} else {
			string inner = x.substr(1, x.length());
			if (isNumeric(inner)) {
				return true;
			} else {
				throw new string("Invalid Literal");
			}
		}
	}
	throw new string("Invalid Literal");

	/*if (x.at(0) == 'X' || x.at(0) == 'C')
	 {
	 if (!(x.length() >0 && (x.at(1) == '\'' && x.at(x.length() - 1) == '\'')))
	 throw new string("not a hexadecimal\\character string");
	 else {
	 int numChars =
	 }
	 return true;
	 }
	 throw new string("Illegal operand");
	 */
}
bool isChar(char a){
	int ascii = a;
	if(ascii >= 65 && ascii<=90)
		return true;
	if(ascii >= 97 && ascii <=122)
		return true;
	return false;
}

bool isRubbish(string x){
	if(x.length()== 0 )
		return true;
	if(x.compare("") == 0)
		return true;
	if(isNumber(x.at(0)))
		return true;
	for (unsigned int i = 0; i < x.length(); i++) {
		if(!isChar(x.at(i)) && !isNumber(x.at(i)))
		{
			return true;
		}
	}
	return false;
}
bool isNumber (char a){
	int ascii = a;
	if(ascii>=48 && ascii <=57)
		return true;
	return false;
}
//int main() {
//
//	try {
//		cout << validate(parse("bfs   LDCH     =1S0")) << endl;
//
//	} catch (string* e) {
//		cout << *e << endl;
//	}
//
//	return 0;
//}
