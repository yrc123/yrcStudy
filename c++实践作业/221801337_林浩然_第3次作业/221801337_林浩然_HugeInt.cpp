#include"221801337_¡÷∫∆»ª_HugeInt.h"
map<char,int> ctoh;
map<int,char> htoc;
HugeInt::HugeInt(const int num) {
	setMap();
	int td,tn=abs(num);
	if(num<0)
		op=-1;
	else 
		op=1;
	fSize=ceil(getNumLen(num)/4.0)*2;
	len=0;
	ar=new int[fSize];
	memset(ar,0,fSize*sizeof(int));
	while(tn>MAXN) {
		td=tn-(tn/(MAXN+1))*(MAXN+1);
		tn=tn/(MAXN+1);
		ar[len++]=td;
	}
	ar[len++]=abs(tn);
}

HugeInt::HugeInt(const string &s) {
	setMap();
	HugeInt t1(1),t2;
	int l,r,type=10;
	l=0;
	r=s.size();
	len=1;
	fSize=r*4;
	ar=new int[fSize];
	memset(ar,0,fSize*sizeof(int));
	if(s[l]=='-'){
		l++;
		op=-1;
	}else{
		op=1;
	}
	if(s[l]=='0'){
		type=8;
		l++;
		if(s[l]=='x'||s[l]=='X'){
			type=16;
			l++;
		}
	}
	per(i,l,r){
		if(ctoh.count(s[i])==0){
			throw WrongNum();
		}
		if(ctoh[s[i]]>type){
			throw WrongNum();
		}
		*this=*this+ctoh[s[i]]*t1;
		t1=t1*type;
	}
}

HugeInt::HugeInt(const HugeInt &a){
	setMap();
	int *tar=a.getData();
	fSize=a.getfSize();
	len=a.size();
	op=a.getOp();
	ar=new int[a.getfSize()];
	memset(ar,0,fSize*sizeof(int));
	rep(i,0,len)
		ar[i]=tar[i];
}
HugeInt::~HugeInt(){
	if(ar!=NULL){
		//delete[] ar;
		ar=NULL;
	}
}
HugeInt &HugeInt::operator=(const HugeInt &a) {
	delete[] ar;
	int *tar=a.getData();
	fSize=a.getfSize();
	len=a.size();
	op=a.getOp();
	ar=new int[fSize];
	memset(ar,0,fSize*sizeof(int));
	rep(i,0,len)
		ar[i]=tar[i];
	return *this;
}
istream& operator>>(istream &is,HugeInt &a) {
	string s;
	int i=-1;
	is>>s;
	HugeInt t(s);
	a=t;
	return is;
}
ostream& operator<<(ostream &os,const HugeInt &a) {
	int len=a.size(),*p=a.getData();
	if(a.getOp()==-1&&(a.size()!=1||a.getData()[0]!=0))os<<"-";
	os<<p[len-1];
	per(i,0,len-1){
		os<<setfill('0')<<setw(4)<<p[i];
	}
	return os;
}
HugeInt operator+(const HugeInt &a,const HugeInt &b){
	HugeInt ta(a),tb(b);
	if(ta.getOp()==1&&tb.getOp()==-1){
		tb.setOp(1);
		return ta-tb;
	}
	if(ta.getOp()==-1&&tb.getOp()==1){
		ta.setOp(1);
		return tb-ta;
	}
	int big;
	big=a.size()>b.size()?a.size():b.size();
	if(big>=ta.getfSize())ta.resize(big*2);
	int *pa=ta.getData(),*pb=tb.getData();
	rep(i,0,big){
		pa[i]+=pb[i];
		if(pa[i]>MAXN) {
			pa[i+1]++;
			pa[i]-=MAXN+1;
		}
	}
	if(pa[big]!=0)
		ta.setLen(big+1);
	else ta.setLen(big);
	return ta;
}
HugeInt operator-(const HugeInt &a,const HugeInt &b){
	HugeInt ta(a),tb(b);
	if(ta.getOp()==-1&&tb.getOp()==1){
		tb.setOp(-1);
		return tb+ta;
	}
	if(ta.getOp()==1&&tb.getOp()==-1){
		tb.setOp(1);
		return ta+tb;
	}
	HugeInt t1,t2;
	int small,big;
	bool flag;
	if(abs(a)>abs(b)) {
		t1=a;
		t2=b;
		flag=0;
	}else{
		t1=b;
		t2=a;
		flag=1;
	}
	big=t1.size();
	small=t2.size();
	int *p1=t1.getData(),*p2=t2.getData();
	rep(i,0,small){
		if(p1[i]<p2[i]) {
			int j=i+1;
			while(p1[j]==0)
				j++;
			p1[j--]--;
			while(j>i)
				p1[j--]+=MAXN;
			p1[i]+=MAXN+1-p2[i];
		} else p1[i]-=p2[i];
	}
	t1.setLen(big);
	while(p1[t1.size()-1]==0 && t1.size()>1) {
		t1.setLen(big-1);
		big--;
	}
	if(t1.size()<t1.getfSize()/4)t1.resize(t1.size()*2);
	if(flag)
		t1.setOp(t1.getOp()*-1);
	return t1;
}
HugeInt operator*(const HugeInt &a,const HugeInt &b){
	HugeInt t;
	t.resize((a.size()+b.size())*2);
	int up,i,j;
	int t1,t2;
	int *pa=a.getData(),*pb=b.getData(),*pt=t.getData();
	for(i=0;i<a.size();i++){
		up=0;
		for(j=0;j<b.size();j++){
			t1=pa[i]*pb[j]+pt[i+j]+up;
			if(t1>MAXN) {
				t2=t1-t1/(MAXN+1)*(MAXN+1);
				up=t1/(MAXN+1);
				pt[i+j]=t2;
			} else {
				up=0;
				pt[i+j]=t1;
			}
		}
		if(up!=0)
			pt[i+j]=up;
	}
	t.setLen(i+j);
	while(pt[t.size()-1]==0 && t.size()>1)t.setLen(t.size()-1);
	t.setOp(a.getOp()*b.getOp());
	return t;
}
HugeInt operator/(const HugeInt &a,const HugeInt &b){
	if(abs(b)>abs(a))return 0; 
	if(abs(b)==0)throw HugeInt::DivideByZero();
	int up=0,*t,cnt=0,l1=1;
	HugeInt ans,t1,ta(abs(a)),tb(abs(b));
	t1.resize(b.size()+1);
	t=new int[(a.size()-b.size()+1)*4];
	memset(t,0,sizeof(int)*((a.size()-b.size()+1)*4));
	per(i,0,a.size()-b.size()+1){
		t1.setLen(ta.size()-i);
		rep(k,i,ta.size()){
			t1.ar[k-i]=ta.ar[k];
		}
		l1=t1.size();
		if(tb>t1){
			rep(j,0,4)
				t[cnt++]=0;
			continue;
		}

		//int asda=1;
		while(t1>=tb){
			if(t1>=tb*1000){
				t1=t1-tb*1000;
				t[cnt]+=1000;
			}else if(t1>=tb*100){
				t1=t1-tb*100;
				t[cnt]+=100;
			}else if(t1>=tb*10){
				t1=t1-tb*10;
				t[cnt]+=10;
			}else if(t1>=tb){
				t1=t1-tb;
				t[cnt]+=1;
			}
		}
		t1.op=1;
		//cout<<t1<<endl;
		//cout<<ta<<endl;
		rep(k,0,t1.size()){
			ta.ar[k+i]=t1.ar[k];
			//cout<<ta<<endl;
		}
		//cout<<"1."<<ta<<endl;
		//cout<<ta.size()<<endl;
		ta.setLen(ta.size()-l1+(t1==0?0:t1.size()));
		//cout<<"2."<<ta<<endl;
		//cout<<ta.size()<<endl;
		int tmp=cnt;
		while(t[cnt]>10||cnt-tmp<3){
			t[cnt+1]=t[cnt];
			t[cnt++]%=10;
			t[cnt]/=10;
		}
		cnt++;
		reverse(t+tmp,t+cnt);
	}
	ans.resize(cnt/2);
	int tmp=0;
	int flag=0,lt;
//	rep(i,0,cnt){
//		cout<<t[i];
//	}
//	cout<<endl;
	for(int i=cnt-1;i>=0;i-=4){
		flag=0;
		per(j,0,4){
			if(i-j>=0){
				ans.ar[tmp]+=t[i-j];
				if(t[i-j]!=0)flag=1;
			}
			else
				continue;
			if(j>0)
				ans.ar[tmp]*=10;
		} 
		tmp++;
		if(flag==1)lt=tmp;
	}
	//if(t!=NULL){
	//	delete[] t;
	//	t=NULL;
//	}
	ans.setLen(lt);
	ans.setOp(a.getOp()*b.getOp());
	return ans;
}
HugeInt operator%(const HugeInt &a,const HugeInt &b){
	HugeInt ta(a),tb(b),t;
	t=ta/tb;
	//cout<<t;
	ta=ta-tb*t;
	return ta;
}
HugeInt &operator+=(HugeInt &a,const HugeInt &b){
	a=a+b;
	return a;
}
HugeInt &operator-=(HugeInt &a,const HugeInt &b){
	a=a-b;
	return a;
}
HugeInt &operator*=(HugeInt &a,const HugeInt &b){
	a=a*b;
	return a;
}
HugeInt &operator/=(HugeInt &a,const HugeInt &b){
	a=a/b;
	return a;
}
HugeInt &operator%=(HugeInt &a,const HugeInt &b){
	a=a%b;
	return a;
}
HugeInt HugeInt::operator++(int){
	HugeInt t(*this);
	*this=*this+1;
	return t;
}
HugeInt HugeInt::operator--(int){
	HugeInt t(*this);
	*this=*this-1;
	return t;
}
HugeInt &HugeInt::operator++(){
	*this=*this+1;
	return *this;
}
HugeInt &HugeInt::operator--(){
	*this=*this-1;
	return *this;
}
bool operator>(const HugeInt &a,const HugeInt &b){
	if(a.getOp()!=b.getOp()){
		return a.getOp()>b.getOp();	
	}
	int ln;
	int *pa=a.getData(),*pb=b.getData();
	if(a.size()!=b.size()){
		if(a.size()>b.size())return a.getOp()==1?1:0;
		else return a.getOp()==1?0:1;
	}else if(a.size()==b.size()) {
		ln=a.size()-1;
		while(pa[ln]==pb[ln]&&ln>=0)
			ln--;
		if(ln>=0 && pa[ln]>pb[ln])
			return a.getOp()==1?1:0;
		else if(ln>=0)
			return a.getOp()==1?0:1;
		else return 0;
	}
}
bool operator<(const HugeInt &a,const HugeInt &b){
	if(a>=b)return 0;
	return 1;
}
bool operator>=(const HugeInt &a,const HugeInt &b){
	if(a>b)return 1;
	if(a==b)return 1;
	return 0;
}
bool operator<=(const HugeInt &a,const HugeInt &b){
	if(a>b)return 0;
	return 1;
}
bool operator==(const HugeInt &a,const HugeInt &b){
	int ln;
	int *pa=a.getData(),*pb=b.getData();
	if(a.getOp()==b.getOp()&&a.size()==b.size()){
		ln=a.size()-1;
		while(pa[ln]==pb[ln]&&ln>=0)
			ln--;
		if(ln<0)
			return 1;
	}
	return 0;
}
bool operator!=(const HugeInt &a,const HugeInt &b){
	return !(a==b);
}

int *HugeInt::getData()const{
	return ar;
}
int HugeInt::getfSize()const{
	return fSize;
}
int HugeInt::getOp()const{
	return op;
}
int HugeInt::size()const{
	return len;
}
bool HugeInt::setOp(int op){
	this->op=op;
	return 1;
}
bool HugeInt::setLen(int len){
	this->len=len;
	return 1;
}
bool HugeInt::resize(int l){
	fSize=l;
	int *t=new int[fSize];
	memset(t,0,fSize*sizeof(int));
	rep(i,0,len){
		t[i]=ar[i];
	}
	delete[] ar;
	ar=t;
	return 1;
}

bool HugeInt::print(){
		cout<<*this;
		return 1;
}
bool HugeInt::printOctal(){
	int *t=new int[len*5],cnt=0;
	HugeInt th(*this);
	memset(t,0,len*sizeof(int));
	while(th!=0){
		t[cnt++]=(th%8).getData()[0];
		th=th/8;
		//cout<<th<<endl;
	}
	if(cnt==0){
		cout<<"0";
		return 1;
	}
	cout<<"0";
	per(i,0,cnt){
		cout<<t[i];
	}
	return 1;
}
bool HugeInt::printHex(){
	int *t=new int[len*4],cnt=0;
	HugeInt th(*this);
	memset(t,0,len*sizeof(int));
	while(th!=0){
		t[cnt++]=(th%16).getData()[0];
		th=th/16;
	}
	if(op==-1&&(len!=1||ar[0]!=0))cout<<"-";
	if((len!=1||ar[0]!=0))cout<<"0X";
	per(i,0,cnt){
		cout<<htoc[t[i]];
	}
	return 1;
}
int HugeInt::getNumLen(int num){
	int l=0;
	while(num){
		l++;
		num/=10;
	}
	return l==0?1:l;
}
bool HugeInt::setMap(){
	if(ctoh.empty()){
		for(int i=0;i<10;i++){
			ctoh.insert(make_pair(char(i+'0'),i));
		}
		for(int i=0;i<7;i++){
			ctoh.insert(make_pair(char(i+'A'),i+10));
			ctoh.insert(make_pair(char(i+'a'),i+10));
		}
	}
	if(htoc.empty()){
		for(int i=0;i<10;i++){
			htoc.insert(make_pair(i,char(i+'0')));
		}
		for(int i=0;i<7;i++){
			htoc.insert(make_pair(i+10,char(i+'A')));
		}
	}
	return 1;
}

HugeInt abs(const HugeInt &a){
	HugeInt t(a);
	t.setOp(1);
	return t; 
}
