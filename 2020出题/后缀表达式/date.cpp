#include<bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll<<(a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
/*并查集
 * int f[];
 * int Find(int x){x==f[x]?return f[x]:f[x]=Find(f[x]);}
 * int join(int x,int y){if(Find(x)!=Find(y))f[Find(x)]=Find(y);}
 * 快速幂*/
int qpow(ll a,ll b,ll m){ll c=1;while(b){if(b&1)c=c*a%m;b>>=1;a=a*a%m;}return c;}
int n;
ll RAND1(){
	return rand()%1000;
}
int RAND2(int f,int t){
	return rand()%(t-f)+f;
}
stack<ll>s;
char cmd[]={"-+*"};
int main(){
	ios::sync_with_stdio(false);
	srand((unsigned)time(NULL));
	cin>>n;
//	n=10000;
	cout<<n<<endl;
	int n1=n;
	int n2=n-1;
	int cnt=0;
	while(1){
		if(cnt<=1&&n1!=0){
			s.push(RAND1());
			cout<<s.top()<<" ";
			cnt++;
			n1--;
		}else{
			if(n1!=0&&RAND2(0,4)<=1){
				s.push(RAND1());
				cout<<s.top()<<" ";
				cnt++;
				n1--;
			}else{
				ll a,b;
				a=s.top();
				s.pop();
				b=s.top();
				s.pop();
				int f=0,t=3;
				if(abs(a*b)>=1e9)t--;
				if(a+b>=1e9)t--;
				if(abs(b-a)>=1e9)f++;
				int c=RAND2(f,t);
				if(c==0)s.push(b-a);
				if(c==1)s.push(a+b);
				if(c==2)s.push(a*b);
				cnt--;
				n2--;
	//			de(s.top());
				cout<<cmd[c]<<" ";
			}
		}
		if(n1==0&&n2==0)break;
	}
	return 0;
}
