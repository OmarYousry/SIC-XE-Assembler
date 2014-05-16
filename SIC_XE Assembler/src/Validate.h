#ifndef VALIDATE_H_
#define VALIDATE_H_

#include "Parser.h"
#include "OpTab.h"
#include <string>

int validate(parsedLine pl);
bool isReg(string o);
int f1(string o1, string o2);
int f2(string op,string o1, string o2);
int f34(string op,string o1, string o2);
bool isNumeric(string s);
bool isHexa(string s);
void fillDirectives();
#endif /* VALIDATE_H_ */
