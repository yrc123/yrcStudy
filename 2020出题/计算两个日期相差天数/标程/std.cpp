#include<iostream>
using namespace std;
long long days(int y,int m,int d){
	if((m-=2)<=0){
		m+=12;
		y-=1;
	}
	return y/4-y/100+y/400+367*m/12+d+y*365;
}

int main(){
	int y1,m1,d1,y2,m2,d2;
	while(cin>>y1>>m1>>d1>>y2>>m2>>d2)cout<<-days(y2,m2,d2)+days(y1,m1,d1)<<endl;
}
