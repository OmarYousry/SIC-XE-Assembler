#include "OpCodeGenerator.h"
#include "Parser.h"
#include "OpTab.h"
#include "StringUtilities.h"

void fillRegMap() {

	registers = new map<string, int>();
	registers->insert(pair<string, int>('A', 0));
	registers->insert(pair<string, int>('X', 1));
	registers->insert(pair<string, int>('L', 2));
	registers->insert(pair<string, int>('B', 3));
	registers->insert(pair<string, int>('S', 4));
	registers->insert(pair<string, int>('T', 5));
	registers->insert(pair<string, int>('F', 6));
}

opCode generateOpCode(parsedLine pl) {

	opCode op;
	op.flags (0b110000);
	map<string, OpInfo*>::iterator it;
	if (format == 1) {
		it = opTable->find(pl.opcode);
		OpInfo* info = it->second;
		unsigned char opCode = info->opCode;
		op.operation = opCode;
		op.displacement = 0;
		op.format = FORMAT_1;
	}

	else if (format == 2) {
		it = opTable->find(pl.opcode);
		OpInfo* info = it->second;
		unsigned char opCode = info->opCode;
		op.operation = opCode;
		op.reg1 = parseDecimal(pl.operand1);
		op.reg2 = parseDecimal(pl.operand2);
		op.format = FORMAT_2;
	}

	else { // format 3 or 4
		// format 3 and 4 code here
	}

}


