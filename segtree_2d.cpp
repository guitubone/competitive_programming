// Seg 2D O(N*log*log) para query e O(N*log) de memória
// Resolve o problema http://codeforces.com/gym/101055/problem/D

#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define emp emplace
#define fi first
#define se second
#define INF 0x3f3f3f3f
typedef long long ll;
typedef pair<int, int> ii;

ii ia, ib, ip;
int ival;
int gamb;

struct SegTree {
	int n;
	int *seg;
	vector<ii> v;

	SegTree() {}

	SegTree (int n) {
		seg = new int[4*n+1];
		for (int i = 0; i < 4*n+1; i++) seg[i] = 0;
		v.resize(n);
	}

	void update(int r, int i, int j, ii p, int val) {
		ip = p;
		ival = val;
		update(r, i, j);
		gamb = 0;
	}

	void update(int r, int i, int j) {
		if (ip < v[i] or ip > v[j]) return;

		if (v[i] == v[j]) {
			seg[r] = max(seg[r], ival);
		} else {
			update(2*r, i, (i+j)/2);
			update(2*r+1, (i+j)/2+1, j);
			seg[r] = max(seg[2*r], seg[2*r+1]);
		}
	}

	int query(int r, int i, int j, ii a, ii b) {
		ia = a;
		ib = b;
		return query(r, i, j);
	}

	int query(int r, int i, int j) {
		if (ia > v[j] or ib < v[i]) return 0;

		if (v[i] >= ia and v[j] <= ib) return seg[r];

		int L = query(2*r, i, (i+j)/2);
		int R = query(2*r+1, (i+j)/2+1, j);

		return max(L, R);
	}
};

const int N = 112345;

int n;
vector<ii> v, sv;
SegTree m_tree[4*N];
ii a, b, p;
int val;

void build(int r, int i, int j) {
	m_tree[r] = SegTree(j-i+1);

	if (i == j) {
		m_tree[r].v[0] = ii(sv[i].se, sv[i].fi);
	} else {
		build(2*r, i, (i+j)/2);	
		build(2*r+1, (i+j)/2+1, j);	

		merge(begin(m_tree[2*r].v), end(m_tree[2*r].v),
				begin(m_tree[2*r+1].v), end(m_tree[2*r+1].v),
				begin(m_tree[r].v));
	}
}

int query(int r, int i, int j) {
	if (b.fi < sv[i].fi or a.fi > sv[j].fi) return 0;

	if (a.fi <= sv[i].fi and b.fi >= sv[j].fi) {
		return m_tree[r].query(1, 0, j-i, ii(a.se, a.fi), ii(b.se, b.fi));
	} else {
		int L = query(2*r, i, (i+j)/2);
		int R = query(2*r+1, (i+j)/2+1, j);

		return max(L, R);
	}
}

void update(int r, int i, int j) {
	if (p.fi > sv[j].fi or p.fi < sv[i].fi) return;	

	if (sv[i].fi == sv[j].fi) {
		m_tree[r].update(1, 0, j-i, ii(p.se, p.fi), val);
	} else {
		update(2*r, i, (i+j)/2);
		update(2*r+1, (i+j)/2+1, j);

		m_tree[r].update(1, 0, j-i, ii(p.se, p.fi), val);
	}
}

int main(void) {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		v.eb(a, b); sv.eb(a, b);
	}

	sort(begin(sv), end(sv));

	build(1, 0, n-1);

	int ans = 0;
	for (int i = 0; i < n; i++) {
		a = ii(0,0); b = v[i];
		int ret = query(1, 0, n-1);

		ans = max(ans, ret+1);

		p = v[i]; val = ret+1;
		update(1, 0, n-1);
	}

	printf("%d\n", ans);

	return 0;
}
