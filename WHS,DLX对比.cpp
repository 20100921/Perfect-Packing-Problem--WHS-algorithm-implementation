#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// ====================== WHS 2D ======================
vector<vector<int>> g;
vector<int> items;
int n;

bool dfs_whs(int idx) {
    if (idx == items.size()) return 1;
    int s = items[idx], x=-1,y=-1;
    for(int i=0;i<n&&x<0;i++)for(int j=0;j<n&&x<0;j++)if(!g[i][j])x=i,y=j;
    for(int i=x;i<=n-s;i++)for(int j=y;j<=n-s;j++){
        bool ok=1;
        for(int a=0;a<s&&ok;a++)for(int b=0;b<s&&ok;b++)if(g[i+a][j+b])ok=0;
        if(!ok)continue;
        for(int a=0;a<s;a++)for(int b=0;b<s;b++)g[i+a][j+b]=1;
        if(dfs_whs(idx+1))return 1;
        for(int a=0;a<s;a++)for(int b=0;b<s;b++)g[i+a][j+b]=0;
    }
    return 0;
}

double run_whs(int N) {
    n=N; g.assign(N,vector<int>(N,0)); items.clear();
    int area=0; for(int s:{2,3})while(area+s*s<=N*N)items.push_back(s),area+=s*s;
    auto t1=steady_clock::now();
    dfs_whs(0);
    auto t2=steady_clock::now();
    return duration_cast<microseconds>(t2-t1).count()/1000.0;
}

// ====================== DLX 2D ======================
struct DLX {
    vector<int> l,r,u,d,col;
    DLX(int cols){
        l.resize(cols+1),r.resize(cols+1),u.resize(cols+1),d.resize(cols+1),col.resize(cols+1);
        for(int i=0;i<=cols;i++)l[i]=i-1,r[i]=i+1,u[i]=d[i]=i;
        l[0]=cols,r[cols]=0;
    }
    void add(vector<int> cc){
        int f=col.size();
        for(int c:cc){
            col.push_back(c),u.push_back(u[c]),d.push_back(c),d[u[c]]=col.size()-1,u[c]=col.size()-1;
            l.push_back(col.size()-1),r.push_back(col.size()-1);
        }
        r.back()=f,l[f]=col.size()-1;
    }
    bool solve(){
        if(r[0]==0)return 1;
        int c=r[0];
        auto rm=[&](int x){ r[l[x]]=r[x],l[r[x]]=l[x]; for(int i=d[x];i!=x;i=d[i])for(int j=r[i];j!=i;j=r[j])d[u[j]]=d[j],u[d[j]]=u[j]; };
        auto rs=[&](int x){ for(int i=u[x];i!=x;i=u[i])for(int j=l[i];j!=i;j=l[j])d[u[j]]=j,u[d[j]]=j; r[l[x]]=x,l[r[x]]=x; };
        rm(c);
        for(int i=d[c];i!=c;i=d[i]){ for(int j=r[i];j!=i;j=r[j])rm(col[j]); if(solve())return 1; for(int j=l[i];j!=i;j=l[j])rs(col[j]); }
        rs(c);
        return 0;
    }
};

double run_dlx(int N) {
    DLX dlx(N*N); vector<int> it; int area=0;
    for(int s:{2,3})while(area+s*s<=N*N)it.push_back(s),area+=s*s;
    for(int k=0;k<it.size();k++){
        int s=it[k];
        for(int i=0;i<=N-s;i++)for(int j=0;j<=N-s;j++){
            vector<int> c;
            for(int a=0;a<s;a++)for(int b=0;b<s;b++)c.push_back(i*N+j+a*N+b+1);
            dlx.add(c);
        }
    }
    auto t1=steady_clock::now();
    dlx.solve();
    auto t2=steady_clock::now();
    return duration_cast<microseconds>(t2-t1).count()/1000.0;
}

// ====================== 对比主函数 ======================
int main() {
    cout << "========== WHS vs DLX (2D) ==========\n";
    cout << "40x40 WHS: " << run_whs(40) << " ms\n";
    cout << "40x40 DLX: " << run_dlx(40) << " ms\n";
    return 0;
}
