#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
typedef long long ll;
const int maxn=1e5+500;
struct node
{
    string name;
    int ranks;
    int val;
    int a[50];
}p[maxn];
pair<int,int> calrank(int e,int d,int c,int b,int a)
{
    pair<int,int> pa;
    if(a==13&&b==12&&c==11&&d==10&&e==1){pa.first=0;pa.second=13;}
    else if(a-b==1&&b-c==1&&c-d==1&&d-e==1){pa.first=1;pa.second=a;}
    else if(b==e){pa.first=2;pa.second=b*100+a;}
    else if(a==d){pa.first=2;pa.second=a*100+e;}
    else if(a==c&&d==e){pa.first=3;pa.second=a*100+d;}
    else if(a==b&&c==e){pa.first=3;pa.second=c*100+a;}
    else if(a==c){pa.first=4;pa.second=a*100+d+e;}
    else if(b==d){pa.first=4;pa.second=b*100+a+e;}
    else if(c==e){pa.first=4;pa.second=c*100+a+b;}
    else if(a==b&&c==d){pa.first=5;pa.second=a*10000+c*100+e;}
    else if(a==b&&d==e){pa.first=5;pa.second=a*10000+e*100+c;}
    else if(b==c&&d==e){pa.first=5;pa.second=b*10000+d*100+a;}
    else if(a==b){pa.first=6;pa.second=a*100+c+d+e;}
    else if(b==c){pa.first=6;pa.second=b*100+a+d+e;}
    else if(c==d){pa.first=6;pa.second=c*100+a+b+e;}
    else if(d==e){pa.first=6;pa.second=d*100+a+b+c;}
    else{pa.first=7;pa.second=a+b+c+d+e;}
    return pa;
}

bool cmp(node a,node b)
{
    if(a.ranks==b.ranks)
    {
        if(a.val==b.val)return a.name<b.name;
        return a.val>b.val;
    }
    else return a.ranks<b.ranks;

}
bool cmp2(int a,int b)
{
    return a<b;
}
int main()
{
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n)
    {
        for(int i=1;i<=n;i++)
        {
            string pai;
            cin>>p[i].name>>pai;
            for(int k=0,j=0;pai[k];k++)
            {
                if(pai[k]=='0')continue;
                if(pai[k]>='2'&&pai[k]<='9')p[i].a[j]=pai[k]-48;
                else if(pai[k]=='A')p[i].a[j]=1;
                else if(pai[k]=='J')p[i].a[j]=11;
                else if(pai[k]=='Q')p[i].a[j]=12;
                else if(pai[k]=='K')p[i].a[j]=13;
                else if(pai[k]=='1')p[i].a[j]=10;
                j++;
            }
            sort(p[i].a,p[i].a+5,cmp2);
            pair<int,int>pa2;
            pa2=calrank(p[i].a[0],p[i].a[1],p[i].a[2],p[i].a[3],p[i].a[4]);
            p[i].ranks=pa2.first;
            p[i].val=pa2.second;
        }
        sort(p+1,p+n+1,cmp);
        for(int i=1;i<=n;i++)
        cout<<p[i].name<<endl;
    }
    return 0;
}
