#include <map>
#include <string>

using namespace std;

const unsigned char FORMAT_1 = 1;
const unsigned char FORMAT_2 = 2;
const unsigned char FORMAT_3_4 = 3;

struct OpInfo {
	string mnmoneic;
	unsigned char format;
	unsigned char opCode;
};

void fillOpTab(map<string, OpInfo*>* opTab) {

	OpInfo* info;
	info = new OpInfo;
	info->mnmoneic = "FIX";
	info->format = FORMAT_1;
	info->opCode = 0xC4;
	opTab->insert(pair<string, OpInfo*>("FIX", info));

	info = new OpInfo;
	info->mnmoneic = "NORM";
	info->format = FORMAT_1;
	info->opCode = 0xC8;
	opTab->insert(pair<string, OpInfo*>("NORM", info));

	info = new OpInfo;
	info->mnmoneic = "TIO";
	info->format = FORMAT_1;
	info->opCode = 0xF8;
	opTab->insert(pair<string, OpInfo*>("TIO", info));

	info = new OpInfo;
	info->mnmoneic = "SIO";
	info->format = FORMAT_1;
	info->opCode = 0xF0;
	opTab->insert(pair<string, OpInfo*>("SIO", info));

	info = new OpInfo;
	info->mnmoneic = "FLOAT";
	info->format = FORMAT_1;
	info->opCode = 0xC0;
	opTab->insert(pair<string, OpInfo*>("FLOAT", info));

	info = new OpInfo;
	info->mnmoneic = "HIO";
	info->format = FORMAT_1;
	info->opCode = 0xF4;
	opTab->insert(pair<string, OpInfo*>("HIO", info));

	info = new OpInfo;
	info->mnmoneic = "ADDR";
	info->format = FORMAT_2;
	info->opCode = 0x90;
	opTab->insert(pair<string, OpInfo*>("ADDR", info));

	info = new OpInfo;
	info->mnmoneic = "CLEAR";
	info->format = FORMAT_2;
	info->opCode = 0xB4;
	opTab->insert(pair<string, OpInfo*>("CLEAR", info));

	info = new OpInfo;
	info->mnmoneic = "COMPR";
	info->format = FORMAT_2;
	info->opCode = 0xA0;
	opTab->insert(pair<string, OpInfo*>("COMPR", info));

	info = new OpInfo;
	info->mnmoneic = "DIVR";
	info->format = FORMAT_2;
	info->opCode = 0x9C;
	opTab->insert(pair<string, OpInfo*>("DIVR", info));

	info = new OpInfo;
	info->mnmoneic = "MULR";
	info->format = FORMAT_2;
	info->opCode = 0x98;
	opTab->insert(pair<string, OpInfo*>("MULR", info));

	info = new OpInfo;
	info->mnmoneic = "RMO";
	info->format = FORMAT_2;
	info->opCode = 0xAC;
	opTab->insert(pair<string, OpInfo*>("RMO", info));

	info = new OpInfo;
	info->mnmoneic = "SHIFTL";
	info->format = FORMAT_2;
	info->opCode = 0xA4;
	opTab->insert(pair<string, OpInfo*>("SHIFTL", info));

	info = new OpInfo;
	info->mnmoneic = "SHIFTR";
	info->format = FORMAT_2;
	info->opCode = 0xA8;
	opTab->insert(pair<string, OpInfo*>("SHIFTR", info));

	info = new OpInfo;
	info->mnmoneic = "SUBR";
	info->format = FORMAT_2;
	info->opCode = 0x94;
	opTab->insert(pair<string, OpInfo*>("SUBR", info));

	info = new OpInfo;
	info->mnmoneic = "SVC";
	info->format = FORMAT_2;
	info->opCode = 0xB0;
	opTab->insert(pair<string, OpInfo*>("SVC", info));

	info = new OpInfo;
	info->mnmoneic = "TIXR";
	info->format = FORMAT_2;
	info->opCode = 0xB8;
	opTab->insert(pair<string, OpInfo*>("TIXR", info));

	info = new OpInfo;
	info->mnmoneic = "ADD";
	info->format = FORMAT_3_4;
	info->opCode = 0x18;
	opTab->insert(pair<string, OpInfo*>("ADD", info));

	info = new OpInfo;
	info->mnmoneic = "ADDF";
	info->format = FORMAT_3_4;
	info->opCode = 0x58;
	opTab->insert(pair<string, OpInfo*>("ADDF", info));

	info = new OpInfo;
	info->mnmoneic = "AND";
	info->format = FORMAT_3_4;
	info->opCode = 0x40;
	opTab->insert(pair<string, OpInfo*>("AND", info));

	info = new OpInfo;
	info->mnmoneic = "COMP";
	info->format = FORMAT_3_4;
	info->opCode = 0x28;
	opTab->insert(pair<string, OpInfo*>("COMP", info));

	info = new OpInfo;
	info->mnmoneic = "COMPF";
	info->format = FORMAT_3_4;
	info->opCode = 0x88;
	opTab->insert(pair<string, OpInfo*>("COMPF", info));

	info = new OpInfo;
	info->mnmoneic = "DIV";
	info->format = FORMAT_3_4;
	info->opCode = 0x24;
	opTab->insert(pair<string, OpInfo*>("DIV", info));

	info = new OpInfo;
	info->mnmoneic = "DIVF";
	info->format = FORMAT_3_4;
	info->opCode = 0x64;
	opTab->insert(pair<string, OpInfo*>("DIVF", info));

	info = new OpInfo;
	info->mnmoneic = "OR";
	info->format = FORMAT_3_4;
	info->opCode = 0x44;
	opTab->insert(pair<string, OpInfo*>("OR", info));

	info = new OpInfo;
	info->mnmoneic = "RD";
	info->format = FORMAT_3_4;
	info->opCode = 0xD8;
	opTab->insert(pair<string, OpInfo*>("RD", info));

	info = new OpInfo;
	info->mnmoneic = "RSUB";
	info->format = FORMAT_3_4;
	info->opCode = 0x4C;
	opTab->insert(pair<string, OpInfo*>("RSUB", info));

	info = new OpInfo;
	info->mnmoneic = "SSK";
	info->format = FORMAT_3_4;
	info->opCode = 0xEC;
	opTab->insert(pair<string, OpInfo*>("SSK", info));

	info = new OpInfo;
	info->mnmoneic = "STA";
	info->format = FORMAT_3_4;
	info->opCode = 0x0C;
	opTab->insert(pair<string, OpInfo*>("STA", info));

	info = new OpInfo;
	info->mnmoneic = "STB";
	info->format = FORMAT_3_4;
	info->opCode = 0x78;
	opTab->insert(pair<string, OpInfo*>("STB", info));

	info = new OpInfo;
	info->mnmoneic = "STCH";
	info->format = FORMAT_3_4;
	info->opCode = 0x54;
	opTab->insert(pair<string, OpInfo*>("STCH", info));

	info = new OpInfo;
	info->mnmoneic = "STF";
	info->format = FORMAT_3_4;
	info->opCode = 0x80;
	opTab->insert(pair<string, OpInfo*>("STF", info));

	info = new OpInfo;
	info->mnmoneic = "STI";
	info->format = FORMAT_3_4;
	info->opCode = 0xD4;
	opTab->insert(pair<string, OpInfo*>("STI", info));

	info = new OpInfo;
	info->mnmoneic = "STL";
	info->format = FORMAT_3_4;
	info->opCode = 0x14;
	opTab->insert(pair<string, OpInfo*>("STL", info));

	info = new OpInfo;
	info->mnmoneic = "STS";
	info->format = FORMAT_3_4;
	info->opCode = 0x7C;
	opTab->insert(pair<string, OpInfo*>("STS", info));

	info = new OpInfo;
	info->mnmoneic = "STSW";
	info->format = FORMAT_3_4;
	info->opCode = 0xE8;
	opTab->insert(pair<string, OpInfo*>("STSW", info));

	info = new OpInfo;
	info->mnmoneic = "STT";
	info->format = FORMAT_3_4;
	info->opCode = 0x84;
	opTab->insert(pair<string, OpInfo*>("STT", info));

	info = new OpInfo;
	info->mnmoneic = "STX";
	info->format = FORMAT_3_4;
	info->opCode = 0x10;
	opTab->insert(pair<string, OpInfo*>("STX", info));

	info = new OpInfo;
	info->mnmoneic = "SUB";
	info->format = FORMAT_3_4;
	info->opCode = 0x1C;
	opTab->insert(pair<string, OpInfo*>("SUB", info));

	info = new OpInfo;
	info->mnmoneic = "SUBF";
	info->format = FORMAT_3_4;
	info->opCode = 0x5C;
	opTab->insert(pair<string, OpInfo*>("SUBF", info));

	info = new OpInfo;
	info->mnmoneic = "TD";
	info->format = FORMAT_3_4;
	info->opCode = 0xE0;
	opTab->insert(pair<string, OpInfo*>("TD", info));

	info = new OpInfo;
	info->mnmoneic = "TIX";
	info->format = FORMAT_3_4;
	info->opCode = 0x2C;
	opTab->insert(pair<string, OpInfo*>("TIX", info));

	info = new OpInfo;
	info->mnmoneic = "WD";
	info->format = FORMAT_3_4;
	info->opCode = 0xDC;
	opTab->insert(pair<string, OpInfo*>("WD", info));

	info = new OpInfo;
	info->mnmoneic = "J";
	info->format = FORMAT_3_4;
	info->opCode = 0x3C;
	opTab->insert(pair<string, OpInfo*>("J", info));

	info = new OpInfo;
	info->mnmoneic = "JEQ";
	info->format = FORMAT_3_4;
	info->opCode = 0x30;
	opTab->insert(pair<string, OpInfo*>("JEQ", info));

	info = new OpInfo;
	info->mnmoneic = "JGT";
	info->format = FORMAT_3_4;
	info->opCode = 0x34;
	opTab->insert(pair<string, OpInfo*>("JGT", info));

	info = new OpInfo;
	info->mnmoneic = "JLT";
	info->format = FORMAT_3_4;
	info->opCode = 0x38;
	opTab->insert(pair<string, OpInfo*>("JLT", info));

	info = new OpInfo;
	info->mnmoneic = "JSUB";
	info->format = FORMAT_3_4;
	info->opCode = 0x48;
	opTab->insert(pair<string, OpInfo*>("JSUB", info));

	info = new OpInfo;
	info->mnmoneic = "LDA";
	info->format = FORMAT_3_4;
	info->opCode = 0x00;
	opTab->insert(pair<string, OpInfo*>("LDA", info));

	info = new OpInfo;
	info->mnmoneic = "LDB";
	info->format = FORMAT_3_4;
	info->opCode = 0x68;
	opTab->insert(pair<string, OpInfo*>("LDB", info));

	info = new OpInfo;
	info->mnmoneic = "LDCH";
	info->format = FORMAT_3_4;
	info->opCode = 0x50;
	opTab->insert(pair<string, OpInfo*>("LDCH", info));

	info = new OpInfo;
	info->mnmoneic = "LDF";
	info->format = FORMAT_3_4;
	info->opCode = 0x70;
	opTab->insert(pair<string, OpInfo*>("LDF", info));

	info = new OpInfo;
	info->mnmoneic = "LDL";
	info->format = FORMAT_3_4;
	info->opCode = 0x08;
	opTab->insert(pair<string, OpInfo*>("LDL", info));

	info = new OpInfo;
	info->mnmoneic = "LDS";
	info->format = FORMAT_3_4;
	info->opCode = 0x6C;
	opTab->insert(pair<string, OpInfo*>("LDS", info));

	info = new OpInfo;
	info->mnmoneic = "LDT";
	info->format = FORMAT_3_4;
	info->opCode = 0x74;
	opTab->insert(pair<string, OpInfo*>("LDT", info));

	info = new OpInfo;
	info->mnmoneic = "LDX";
	info->format = FORMAT_3_4;
	info->opCode = 0x04;
	opTab->insert(pair<string, OpInfo*>("LDX", info));

	info = new OpInfo;
	info->mnmoneic = "LPS";
	info->format = FORMAT_3_4;
	info->opCode = 0xD0;
	opTab->insert(pair<string, OpInfo*>("LPS", info));

	info = new OpInfo;
	info->mnmoneic = "MUL";
	info->format = FORMAT_3_4;
	info->opCode = 0x20;
	opTab->insert(pair<string, OpInfo*>("MUL", info));

	info = new OpInfo;
	info->mnmoneic = "MULF";
	info->format = FORMAT_3_4;
	info->opCode = 0x60;
	opTab->insert(pair<string, OpInfo*>("MULF", info));

	info = NULL;
}

//int main(int argc, char **argv) {
//	map<string, OpInfo*>* opTab = new map<string, OpInfo*>();
//	cout << opTab->size() << endl;
//	fill(opTab);
//	cout << opTab->size() << endl;
//}

