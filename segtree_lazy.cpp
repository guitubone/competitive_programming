#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define emp emplace
#define fi first
#define se second
#define INF 0x3f3f3f3f
typedef long long ll;
typedef pair<int, int> ii;

const int N = 112345;

ll v[N], seg[4*N], lazy[4*N];
int n, a, b, val;

void build(int r, int i, int j) {
	if (i == j) {
		seg[r] = v[i];
	} else {
		int m = (i+j)/2;
		build(2*r, i, m);
		build(2*r+1, m+1, j);
		seg[r] = seg[2*r] + seg[2*r+1];
	}
}

void prop(int r, int i, int j) {
	seg[r] += lazy[r] * (j-i+1);

	if (i != j) {
		lazy[2*r] += lazy[r];
		lazy[2*r+1] += lazy[r];
	}

	lazy[r] = 0;
}

void update(int r, int i, int j) {
	prop(r, i, j);

	if (i > b or j < a) return;

	if (a <= i and j <= b) {
		lazy[r] = val;
		prop(r, i, j);
	} else {
		int m = (i+j)/2;
		update(2*r, i, m);
		update(2*r+1, m+1, j);
		seg[r] = seg[2*r] + seg[2*r+1];
	}
}

ll query(int r, int i, int j) {
	prop(r, i, j);

	if (i > b or j < a) return 0;

	if (a <= i and j <= b) {
		return seg[r];
	} else {
		int m = (i+j)/2;
		ll L = query(2*r, i, m);
		ll R = query(2*r+1, m+1, j);
		return L+R;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
