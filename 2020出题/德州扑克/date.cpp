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
string c[]={"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char name[]="abcdefghijklmnopqrstuvwxyz";
int s[6];
int ok(){
	int a=s[0];
	bool b=1;
	rep(i,0,5){
		if(s[i]!=a)b=0;
	}
	if(b)return 1;
	return 0;
}
void RAND(){
	do{
		rep(i,0,5)s[i]=(rand()%(13-1+1))+1;
		sort(s,s+5);
	}while(ok());
}
int nn[100005];
int main(){
	ios::sync_with_stdio(false);
	srand((unsigned)time(NULL));
	cin>>n;
//	n=10000;
	rep(i,0,n)nn[i]=i;
	per(i,0,n)swap(nn[i],nn[rand()%(i+1)]);
	cout<<n<<endl;
	rep(i,0,n){
		while(1){
			cout<<name[nn[i]%26];
			nn[i]/=26;
			if(nn[i]==0)break;
		}
		cout<<" ";
		RAND();
		rep(i,0,5){
			cout<<c[s[i]];
		}
		cout<<endl;
	}
	return 0;
}
