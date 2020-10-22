#ifndef HUGEINT
#define HUGEINT
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define de(a) cout << #a << "=" << (a) << endl
#define dd(a) cout << #a << "=" << (a) << "  "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll<<(a))
#define endl "\n"
#define MAXN 9999
#define MAXSIZE 1010
#define DLEN 4
extern map<char,int> ctoh;
extern map<int,char> htoc;
class HugeInt {
public:
	HugeInt(const int num=0);
	HugeInt(const string &);
	HugeInt(const HugeInt &);
	HugeInt &operator=(const HugeInt &);
	~HugeInt();

	friend istream& operator>>(istream&,HugeInt&);
	friend ostream& operator<<(ostream&,const HugeInt&);

	friend HugeInt operator+(const HugeInt &,const HugeInt &);
	friend HugeInt operator-(const HugeInt &,const HugeInt &);
	friend HugeInt operator*(const HugeInt &,const HugeInt &);
	friend HugeInt operator/(const HugeInt &,const HugeInt &);
	friend HugeInt operator%(const HugeInt &,const HugeInt &);
	friend HugeInt &operator+=(HugeInt &,const HugeInt &);
	friend HugeInt &operator-=(HugeInt &,const HugeInt &);
	friend HugeInt &operator*=(HugeInt &,const HugeInt &);
	friend HugeInt &operator/=(HugeInt &,const HugeInt &);
	friend HugeInt &operator%=(HugeInt &,const HugeInt &);

	friend bool operator>(const HugeInt &,const HugeInt &);
	friend bool operator<(const HugeInt &,const HugeInt &);
	friend bool operator>=(const HugeInt &,const HugeInt &);
	friend bool operator<=(const HugeInt &,const HugeInt &);
	friend bool operator==(const HugeInt &,const HugeInt &);
	friend bool operator!=(const HugeInt &,const HugeInt &);

	HugeInt operator++(int);
	HugeInt operator--(int);
	HugeInt &operator++();
	HugeInt &operator--();

	int *getData()const;
	int getfSize()const;
	int getOp()const;
	int size()const;
	bool setOp(int);
	bool setLen(int);
	bool resize(int);

	bool print();
	bool printOctal();
	bool printHex();

	class DivideByZero{}; 
	class WrongNum{};
private:
	int *ar;
	int len,fSize;
	int op;
	int getNumLen(int);
	bool setMap();
};
HugeInt abs(const HugeInt &);
#endif