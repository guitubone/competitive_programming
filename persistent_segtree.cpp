// github.com/Loppa/RepGod




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

