#include <iostream>
#include "math.h"
#include <stdio.h>
#include <string.h>
using namespace std;

long long dp[200];

double phi = (1 + sqrt(5)) / 2;
double phiHat = 1.0 - phi;

unsigned long long fib(int n) {
	if (n <= 2) {
		return 1;
	}

	if (dp[n - 1] == -1)
		dp[n - 1] = fib(n - 1);

	if (dp[n - 2] == -1)
		dp[n - 2] = fib(n - 2);

	dp[n] = dp[n - 1] + dp[n - 2];

	return dp[n];
}

unsigned long long fibSexy(int n) {
	return (unsigned long long) ((pow(phi, n) - pow(phiHat, n)) / sqrt(5));
}

int main() {
	memset(dp, -1, 200 * sizeof(unsigned long long));
	int i = 1;

	do {
		unsigned long long x = fib(i);
		unsigned long long y = fibSexy(i);
		cout << i << " : " << x << " : " << y << " : " << (x == y) << endl;
	} while (++i < 200);

	return 0;
}
