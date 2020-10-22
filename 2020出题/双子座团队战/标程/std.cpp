#include<bits/stdc++.h>
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
int n,a,b,k;
int m[200005];
int ans;
priority_queue<int,vector<int>,greater<int>>q;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>a>>b>>k;
	rep(i,0,n){
		cin>>m[i];
		m[i]%=(a+b);
		if(m[i]<=a&&m[i]!=0){
			ans++;
		}else{
			if(m[i]==0)m[i]=a+b;
			int tp=m[i]/a-1;
			if(m[i]%a)tp++;
			q.push(tp);
		}
	}
	while(!q.empty()){
		int tp=q.top();
		q.pop();
		if(tp>k)break;
		k-=tp;
		ans++;
	}
	cout<<ans;
	return 0;
}
