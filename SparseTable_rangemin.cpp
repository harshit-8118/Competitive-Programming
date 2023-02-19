#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define ull unsigned long long
#define lld long double
#define nline "\n"
#define MOD 1000000007ll // 998244353ll
#define pi 3.141592653589793238462
#define fi first
#define se second
#define v32 vector<int>
#define v64 vector<ll>
#define vp32 vector<pair<int,int>>
#define vp64 vector<pair<ll, ll>>
#define pb push_back
#define mp32 map<int,int>
#define mp64 map<ll, ll>
#define mpr make_pair
#define all(x) (x).begin(), (x).end()
#define forf(i, s, e) for(int i = s; i < e; i++)
#define forb(i, e, s) for(int i = e; i >= s; i--)

#ifndef ONLINE_JUDGE
#include "../Algo/debug.h"
#else
#define fix(x)
#endif


vector<vector<int>> sparse;
vector<int> arr;
int sz, N;
void buildSparseTable(){
    sparse = vector<vector<int>> (sz+1, vector<int>(N));
    sparse[0] = arr;
    for(int i = 1; i <= sz; i++){
        for(int j = 0; j + (1 << i) <= N; j++){
            sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j + (1 << (i-1))]);
        }
    }
}

int rangeMinQuery(int l, int r){
    int mn = INT_MAX;
    int i = sz;
    while(i >= 0){
        if(l + (1 << i) <= r + 1){
            mn = min(mn, sparse[i][l]);
            l += (1 << i);
        } i--;
    }
    return mn;
}
int main(){

ios_base::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);

#ifndef ONLINE_JUDGE
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
   freopen("error.txt", "w", stderr);
#endif

    cin>>N;
    sz = log2(N);
    arr = vector<int>(N);
    for(auto &x: arr){
        cin>>x;
    }
    buildSparseTable();
    fix(sparse);
    int q, l, r;
    cin>>q;
    while(q--){
        cin>>l>>r;
        int val = rangeMinQuery(l, r);
        cout<<val<<endl;
    }

return 0;
}