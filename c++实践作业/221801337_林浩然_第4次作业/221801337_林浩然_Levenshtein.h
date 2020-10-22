#ifndef LEVENSHTEIN
#define LEVENSHTEIN
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class Levenshtein{
public:
	Levenshtein(const string &,const string &);
	bool check();
	double same=0;
private:
	int ldistance();
	bool delDef(string &);
	string source,target;
};
#endif