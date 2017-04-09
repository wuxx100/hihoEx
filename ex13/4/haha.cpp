#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define inf -0x3f3f3f3f
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define MP(x,y) make_pair(x,y)
typedef long long ll;
void fre() { freopen("input.in", "r", stdin); freopen("output.out", "w", stdout); }
template <class T1, class T2>inline void gmax(T1 &a, T2 b) { if (b>a)a = b; }
template <class T1, class T2>inline void gmin(T1 &a, T2 b) { if (b<a)a = b; }
const int MOD=1000000007;

struct Matrix{
    long long m[64][64];
    void init(){
        memset(m,0,sizeof(m));
    }
    Matrix operator *(const Matrix &b) const{
        Matrix ret;
        ret.init();
        for(int i=0;i<64;i++)
            for(int j=0;j<64;j++){
                if(m[i][j]!=0){
                    for(int k=0;k<64;k++)
                        ret.m[i][k]=(ret.m[i][k]+m[i][j]*b.m[j][k])%MOD;
                }
            }
        return ret;
    }
};
Matrix base;

Matrix Pow(int n){
    Matrix ans;
    for(int i=0;i<64;i++)
        for(int j=0;j<64;j++){
            if(i==j)
                ans.m[i][j]=1;
            else
                ans.m[i][j]=0;
        }
    while(n){
        if(n&1)
            ans=base*ans;   //不能颠倒顺序,因为乘法不满足交换律
        n>>=1;
        base=base*base;
    }
    return ans;
}

bool check(int x1,int y1,int x2,int y2){
    int x=abs(x1-x2),y=abs(y1-y2);
    if(x+y==3&&(x==1||x==2))
        return true;
    return false;
}

void init(){
    base.init();
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            for(int x=0;x<8;x++)
                for(int y=0;y<8;y++)
                    if(check(i,j,x,y))
                        base.m[i*8+j][x*8+y]=1;
}

int main(){
    int R,C,n;
    while(scanf("%d%d%d",&n,&R,&C)!=EOF){
        init();

        R--,C--;
        Matrix ans=Pow(n);
        long long Ans=0;
        /*
        for(int i=0;i<64;i++)
        {
            for(int j=0;j<64;j++)
            {
                cout<<ans.m[i][j]<<' ';
            }
            cout<<endl;
        }
        */
        for(int j=0;j<64;j++)
            Ans=(Ans+ans.m[R*8+C][j])%MOD;
        printf("%lld\n",Ans);
    }
    return 0;
}

