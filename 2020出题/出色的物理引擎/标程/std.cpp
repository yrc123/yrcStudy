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
int qpow(ll a,ll b,ll m){ll c=1;while(b){if(b&1)c=c*a%m;b>>=1;a=a*a%m;}return c;}
int n,m;
queue<int>q;
int main(){
    ios::sync_with_stdio(false);
	cin>>n>>m;
	rep(i,0,n){
		q.push(i+1);	
	}
	rep(i,0,n){
		int tmp;
		rep(j,0,m-1){
			q.push(q.front());
			q.pop();
		}
		if(i==n-1)cout<<q.front()<<' ';
		q.pop();
	}
    return 0;
}
