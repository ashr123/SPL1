#include "../include/Environment.h"

// ... You may not change this file

unsigned int verbose=0;

int main(int, char **)
{
//	Environment env;
//	env.start();
	File a("ababa", 3), b("qqqqq", 5),
			c(a);
	a=b;
	a=File("sss", 7);
	return 0;
}