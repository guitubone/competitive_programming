#include <bits/stdc++.h>
using namespace std;

const int N = 100001;
int seg[4*N], v[N];
int a, b;

void init(int r, int i, int j) {
    if (i == j) {
        seg[r] = v[i];
    } else {
        init(2*r, i, (i+j)/2);
        init(2*r+1, (i+j)/2+1, j);
        seg[r] = seg[2*r] + seg[2*r+1];
    }
}

int query(int r, int i, int j) {
    if (b < i || a > j) return 0;
    if (i >= a && j <= b) {
        return seg[r];
    } else {
        int L = query(2*r, i, (i+j)/2);
        int R = query(2*r+1, (i+j)/2+1, j);
        return L+R;
    }
}

void update(int r, int i, int j, int pos, int val) {
    if (pos < i || pos > j) return;
    if (i == j) {
        seg[r] = val;
    } else {
        update(2*r, i, (i+j)/2, pos, val);
        update(2*r+1, (i+j)/2+1, j, pos, val);
        seg[r] = seg[2*r] + seg[2*r+1];
    }
}

int main(void) {

    return 0;
}
