#include<bits/stdc++.h>
using namespace std;
#define int long long int

int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;
    
    cout<<a<<" "<<b<<endl;
    // general solution
    cout<<x<<" "<<y<<endl;

    for(int i = -5; i < 6; i++){
        int x1 = x + i*b;
        int y1 = y - i*a;
        cout<<x1<<" "<<y1<<endl;
    }

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;

    // printing answers
    int xx = lx;
    for(int i = 0; xx <= rx ; i++){
        int yy = (c - a * g * xx) / (b * g);
        cout<<xx<<" "<<yy<<endl;
        xx += b;
    }
    return (rx - lx) / abs(b) + 1;
}


signed main(){

#ifndef ONLINE_JUDGE
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

ios_base::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);

int a, b, c, mnx, mxx, mny, mxy;
cin>>a>>b>>c>>mnx>>mxx>>mny>>mxy;
cout<<find_all_solutions(a, b, c, mnx, mxx, mny, mxy);

return 0;
}