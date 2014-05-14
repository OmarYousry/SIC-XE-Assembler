#include "Validate.h"
#include "Parser.h"
#include "IO.h"
#include "OpTab.h"

map<string, OpInfo*>* mainOpTab;

int main(int argc, char **argv) {

	mainOpTab = getOpTab();

	string line;
	ifstream ipfile;
	ipfile.open("pass1.txt");

	ofstream opfile;
	opfile.open("pass1_op.txt", std::ios::app);
	deleteFile("pass1_op.txt");

	int format, locCtr = 0;

	string errorMessage = "";
	line = readLine(&ipfile);

	while (line != "") {
		try {
			format = validate(parse(line));
		} catch (int e) {
			// handle errors
			switch (e) {
			case 0:
				errorMessage = "/*message*/";
			}
			throw;
		}

		writeLine(&opfile, line);
		if (errorMessage != "") {
			writeError(&opfile, errorMessage);
		} else {
			locCtr += format;
		}

		line = readLine(&ipfile);
	}
	opfile.close();
	ipfile.close();
	//You must delete all pointers to OpInfos before deleting the map
	delete mainOpTab;
}
