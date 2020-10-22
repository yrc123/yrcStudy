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
int main(){
    ios::sync_with_stdio(false);
	int n,a[1000];
	cin>>n;
	n+=1;
	rep(i,0,n){
		cin>>a[i];
	}
	per(i,1,n+1){
		if(a[n-i]!=0){
			if(i!=n&&a[n-i]>0){
				cout<<"+";
			}else if(a[n-i]<0){
				cout<<"-";
			}
			if(abs(a[n-i])!=1||i==1)
				cout<<abs(a[n-i]);
			if(i-1==1){
				cout<<"x";
			}else if(i-1!=0){
				cout<<"x^"<<i-1;
			}
		}
	}
    return 0;
}


