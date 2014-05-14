#include "Validate.h"
#include "Parser.h"
#include "IO.h"

int main(int argc, char **argv) {

	string line;
	ifstream ipfile;
	ipfile.open("pass1.txt");

	ifstream opfile;
	deleteFile("pass1_op.txt");

	int format, pc = 0;
	string errorMessage = "";

	line = readLine(&ipfile);
	while(line != "")
	{
		try{
			format = validate(parse(line));
		}catch(int e){
			// handle errors
			switch(e){
			case 0:
				errorMessage = "/*message*/";
			}
			throw;
		}

		writeLine(line, "pass1.txt");
		if(errorMessage != ""){
			writeLine(errorMessage, "pass1.txt");
		}
		else{
			pc += format;
		}

		line = readLine(&ipfile);
	}
}
