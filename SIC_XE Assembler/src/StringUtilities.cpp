#include <string>
#include <iostream>
#include <vector>

using namespace std;

string toUpperCase(string x) {
	unsigned int i;
	string toRet = "";
	for (i = 0; i < x.length(); i++) {
		char pos = x.at(i);
		if (pos <= 122 && pos >= 97) {
			pos -= 32;
		}
		toRet += pos;
	}
	return toRet;
}

/*
 * Trims the leading and forwarding spaces.
 */
string trim(string x) {
	unsigned int i;
	for (i = 0; i < x.length() && x.at(i) == ' '; i++)
		;

	unsigned int j;
	for (j = x.length() - 1; j >= 0 && x.at(j) == ' '; j--)
		;

	string toRet = "";
	unsigned int k;
	for (k = i; k <= j; k++)
		toRet += x.at(k);

	return toRet;
}

/*
 * Parses a decimal integer from a string.
 */
int parseDecimal(string x) {
	char first = x.at(0);
	unsigned int i = first == '-' || first == '+' ? 1 : 0;

	int result = 0;
	for (; i < x.length(); i++) {
		result *= 10;
		result += (x.at(i) - 48);
	}
	return first == '-' ? -result : result;
}

/*
 * Parses a hexadecimal integer from a string.
 */

int parseHexaDecimal(string x) {
	char first = x.at(0);
	unsigned int i = first == '-' || first == '+' ? 1 : 0;

	int result = 0;
	for (; i < x.length(); i++) {
		result *= 16;

		if (x.at(i) >= 48 && x.at(i) <= 57)
			result += (x.at(i) - 48);
		else
			result += (x.at(i) - 55);
	}
	return first == '-' ? -result : result;
}

/*
 * Parses a float from a string.
 */
float parseFloat(string x) {
	float resFrac = 0.0, resInt = 0.0;
	unsigned int i;

	unsigned int dotPos = x.find(".");

	if (dotPos != x.npos) {
		for (i = dotPos + 1; i < x.length(); i++) {
			resFrac += (x.at(i) - 48);
			resFrac *= 0.1;
		}
	}

	char first = x.at(0);
	i = first == '-' || first == '+' ? 1 : 0;

	for (; i <= dotPos - 1; i++) {
		resInt *= 10;
		resInt += (x.at(i) - 48);
	}
	float res = resFrac;
	res += resInt;

	return first == '-' ? -res : res;
}

/*
 * Splits the given string using the character s as a delimiter.
 */
vector<string>* split(string x, char s) {
	vector<string>* toRet = new vector<string>();
	string* temp = new string("");
	for (unsigned int i = 0; i < x.length(); i++) {
		if (x.at(i) == s) {
			if (temp->length() == 0)
				continue;

			toRet->push_back(*temp);
			temp = new string("");
			continue;
		}
		(*temp) += x.at(i);
	}
	if (temp->length() != 0)
		toRet->push_back(*temp);

	return toRet;
}
