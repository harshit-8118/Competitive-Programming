#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define nline "\n"
#define v32 vector<int>
#define pb emplace_back
#define all(x) (x).begin(), (x).end()
#define forf(i, s, e) for(int i = s; i < e; i++)
#define forb(i, e, s) for(int i = e; i >= s; i--)

class segmentTree{
  public: 
  vector<int> t, lazy; int n;
  segmentTree(vector<int> &a){
    this->n = a.size();   t.resize(4*n, 0);   lazy.resize(4*n, 0);
    build(a, 1, 0, n-1);
  }
  template<class T> T operation(T a, T b){ return a + b; } 
  template<class T> void build(vector<int> &a, T v, T tl, T tr){ 
    if(tl == tr){
      t[v] = a[tl];
    }else{ int tm = (tl + tr) >> 1;
      build(a, v*2, tl, tm); build(a, v*2, tl, tm);
      t[v] = operation(t[v*2], t[v*2+1]);
    }   
  } 
  void push(int v, int tl, int tr){
    if(lazy[v]){
        t[v] += (tr - tl + 1) * lazy[v];
        if(tl != tr){
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }
        lazy[v] = 0;
    }
  }
  template<class T>  void update(T v, T tl, T tr, T l, T r, T val){
    if(tl > r || tr < l) return;
    push(v, tl, tr);
    if(tr <= r and tl >= l){
        t[v] += (tr - tl + 1) * val;
        if(tl != tr){
            lazy[v*2] += val;
            lazy[v*2+1] += val;
        }
        return;
    }
    T tm = (tl + tr)/2;
    update(v*2, tl, tm, l, r, val);
    update(v*2+1, tm+1, tr, l, r, val);
    t[v] = operation(t[v*2], t[v*2+1]);
  }
  template<class T>  T get_query(T v, T tl, T tr, T r){
    push(v, tl, tr);
    if(tr == tl){
        return t[v];
    }
    T tm = (tl + tr)/2;
    if(r <= tm)
    return get_query(v*2, tl, tm, r);
    else
    return get_query(v*2+1, tm+1, tr, r);
}
  template<class T> void update(T l, T r, T val){
    update(T(1), T(0), T(n-1), l, r, val);
  }
  template<class T> T get_query(T r){
    return get_query(T(1), T(0), T(n-1), r);
  }
};
template<typename T>    vector<T>& operator++(vector<T> &v){for (auto& i : v) ++i;  return  v;} // prefix incrementor
template<typename T>    vector<T>& operator--(vector<T> &v){for (auto& i : v) --i;  return  v;} // prefix decrementor
template<typename T>    istream& operator>>(istream& is, vector<T> &v){for (auto& i : v) is >> i;  return is;}
template<typename T>    ostream& operator<<(ostream& os, vector<T>  v){for (auto& i : v) os << i << ' ';   return os;}

int32_t main(){

ios_base::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);

int n, m, l, r, ty, val; cin>>n>>m;
v32 v(n, 0);
segmentTree st(v);
 
while (m--){
    cin>>ty;
    if(ty == 1){
        cin>>l>>r>>val; r--;
        st.update(l, r, val);
         
    }else{
        cin>>r;
        cout<<st.get_query(r)<<" ";
         
    }
}
return 0;
}