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
stack<ll>s;
ll stll(string st){
    ll ans=0,l=st.size(),w=1;
    while(l--){
		ans+=(st[l]-'0')*w;
		w*=10;
    }
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	int n;
    cin>>n;
    n=n*2-1;
	string st;
	while(n--){
		cin>>st;
        if(st[0]>='0'&&st[0]<='9'){
            s.push(stoi(st));
        }else{
			ll a,b;
			a=s.top();
			s.pop();
			b=s.top();
			s.pop();
			if(st[0]=='+')
				s.push(a+b);
			if(st[0]=='-')
				s.push(b-a);
			if(st[0]=='*')
				s.push(a*b);
		}
	}
	cout<<s.top();
	return 0;
}
