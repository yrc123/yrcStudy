#include"221801337_ÁÖºÆÈ»_Levenshtein.h"
#define min(a,b) ((a)>(b)?(b):(a))
Levenshtein::Levenshtein(const string &source,const string &target){
	this->source=source;
	this->target=target;
	delDef(this->source);
	delDef(this->target);
}
bool Levenshtein::delDef(string &s){
	string t;
	int size=s.size();
	int p=0,p1=0,p2=0,u=0,g=0,x=0,fi=0,gb=0,xb=0,v=0;
	while(p<size){
		if(xb!=1&&s[p]=='\n'||s[p]==EOF||p+1==size){
			fi=1;
			p2=p-1;
			if(gb==1){
				gb=0;
				p1=p+1;
				fi=0;
			}
			v=0;
		}else if(gb!=1&&xb!=1&&s[p]=='\"'){
			if(g==0){
				if(u==1){
					u=0;
					p1=p+1;
				}else if(u==0){
					u=1;
					fi=1;
					p2=p-1;
				}
			}
		}else if(gb!=1&&s[p]=='/'){
			if(g==1){
				fi=1;
				gb=1;
				p2=p-2;
			}
			g=2;
			if(xb==1&&x==1){
				xb=0;
				p1=p+1;
			}
		}else if(gb!=1&&s[p]=='*'){
			x=2;
			if(g==1){
				xb=1;
				fi=1;
				p2=p-2;
			}
		}else if(gb!=1&&xb!=1&&s[p]=='#'){
			gb=1;
			fi=1;
			p2=p-1;
		}else if(gb!=1&&xb!=1&&s[p]==' '||s[p]=='\t'){
			fi=1;
			p2=p-1;
		}
		if(g!=0)
			g--;
		if(x!=0)
			x--;
		if(fi==1){
			for(int i=p1;i<=p2;i++)
				t+=s[i];
			fi=0;
			p1=p+1;
		}
		//cout<<s[p];
		p++;
	}
	/*
	cout<<"test1\n";
	cout<<t;
	cout<<"test2\n";
	cout<<s;
	*/

	s=t;

	return 1;
}
bool Levenshtein::check(){
	int s=source.size();
	int t=target.size();
	same=1-(ldistance()/double(s>t?s:t));
	return 1;
}
int Levenshtein::ldistance()
{
	int n=source.length();
	int m=target.length();
	if (m==0) 
		return n;
	if (n==0) 
		return m;
	typedef vector<vector<int>>Tmatrix;
	Tmatrix matrix(n+1);
	for (int i=0;i<=n;i++)  
		matrix[i].resize(m+1);
	//step 2 Initialize
	for (int i=1;i<=n;i++)
		matrix[i][0]=i;
	for (int i=1;i<=m;i++)
		matrix[0][i]=i;
	//step 3
	for (int i=1;i<=n;i++){
		const char si =source[i-1];
		//step 4
		for (int j=1;j<=m;j++){
			const char dj=target[j-1];
			//step 5
			int cost;
			if (si==dj){
				cost=0;
			}else{
				cost=1;
			}
			//step 6
			const int above = matrix[i-1][j]+1;
			const int left = matrix[i][j-1]+1;
			const int diag = matrix[i-1][j-1]+cost;
			matrix[i][j]=min(above,min(left,diag));
		}
	}
	//step7
	return matrix[n][m];
}