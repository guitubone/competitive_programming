// github.com/Loppa/RepGod

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mk make_pair
#define fi first
#define se second
 
typedef long long ll;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
 
const int N = 1e5 + 5, M = 3e7 + 7;
int n, a[N];
int root[N], nodes, L[M], R[M], seg[M];
 
int build (int l, int r) {
	int at = nodes++;
 
	if (l == r) {
		seg[at] = a[at];
	} else {
		int m = (l + r)/2;
		L[at] = build (l, m);
		R[at] = build (m + 1, r);
		seg[at] = seg[L[at]] + seg[R[at]];
	}
 
	return at;
}
 
/* point update, v[p]++ */
int update (int i, int l, int r, int p) {
	int at = nodes++;
 
	if (l == r) {
		seg[at] = seg[i] + 1;
	} else {
		int m = (l + r)/2;
		if (p <= m) {
			L[at] = update (L[i], l, m, p);
			R[at] = R[i];
		} else {
			L[at] = L[i];
			R[at] = update (R[i], m + 1, r, p);
		}
		seg[at] = seg[L[at]] + seg[R[at]];
	}
 
	return at;
}
 
/* range query: v[A] + ... + v[B] */
int A, B;
int query (int i, int l, int r) {
	if (A > B)	return 0;
	if (r < A or l > B)	return 0;
 
 	if (l >= A and r <= B) {
		return seg[i];
	} else {
		int m = (l + r)/2;
		return query (L[i], l, m) + query (R[i], m + 1, r);
	}
}


// Minha versão com ponteiro

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node {
	node *left, *right;
	ll val;

	node() {}
	node(node *l, node *r, ll v) {
		left = l;
		right = r;
		val = v;
	}
};

const int N = 11234; // ?????

int n, q;
ll v[N];
node *roots[N];

void build(node *cur, int i, int j) {
	if (i == j) cur->val = v[i];
	else {
		cur->left = new node(nullptr, nullptr, 0);
		cur->right = new node(nullptr, nullptr, 0);

		build(cur->left, i, (i+j)/2);
		build(cur->right, (i+j)/2+1, j);

		cur->val = cur->left->val + cur->right->val;
	}
}

void update(node *prv, node *cur, int i, int j, int id, ll val) {
	if (id < i || id > j || i > j) return;

	if (i == j) {
		cur->val = val;
	} else {
		if (id <= (i+j)/2) {
			cur->left = new node(nullptr, nullptr, 0);
			cur->right = prv->right;
			update(prv->left, cur->left, i, (i+j)/2, id, val);	
		} else {
			cur->left = prv->left;
			cur->right = new node(nullptr, nullptr, 0);
			update(prv->right, cur->right, (i+j)/2+1, j, id, val);	
		}

		cur->val = cur->left->val + cur->right->val;
	}
}

ll query(node *cur, int i, int j, int a, int b) {
	if (i > b || j < a || i > j) return 0;

	if (i >= a && j <= b) {
		return cur->val;
	} else {
		ll left_val = query(cur->left, i, (i+j)/2, a, b);
		ll right_val = query(cur->right, (i+j)/2+1, j, a, b);

		return left_val+right_val;
	}
}

int main(void) {
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) scanf("%lld", &v[i]);

	roots[0] = new node(nullptr, nullptr, 0);
	build(roots[0], 0, n-1);

	int at_version = 0;

	for (int i = 0; i < q; i++) {
		int t; scanf("%d", &t);

		if (t == 1) { // Query
			int a, b, ver; scanf("%d %d %d", &a, &b, &ver);
			ll res = query(roots[ver], 0, n-1, a, b);
			printf("%lld\n", res);
		} else if (t == 2) { //Update
			int id; ll val; scanf("%d %lld", &id, &val);

			at_version++;
			roots[at_version] = new node(nullptr, nullptr, 0);

			update(roots[at_version-1], roots[at_version], 0, n-1, id, val);
		}
	}
    
	return 0;
}

