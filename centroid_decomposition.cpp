#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define emp emplace
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> ii;

const int N = 112345;

int n, m;
vector<int> tree[N], c_tree[N];
int tree_sz[N], ans[N], parent[N];
bool ok[N];
map<int, int> dist[N];

void calc_dist(int u, int c, int p = 0, int d = 0) {
	dist[c][u] = d;
	for (int v: tree[u]) {
		if (v != p and !ok[v]) calc_dist(v, c, u, d+1);
	}
}

int get_sizes(int u, int p) {
	int sz = 0;
	for (int v : tree[u]) {
		if (v != p && !ok[v]) sz += get_sizes(v, u);
	}
	return tree_sz[u] = sz+1;
}

int find_centroid(int u, int p, int sz) {
	for (int v : tree[u]) {
		if (v != p && !ok[v] && tree_sz[v] > sz/2)
			return find_centroid(v, u, sz);
	}
	return u;
}

int build_ctree(int root) {
	int sz = get_sizes(root, 0);
	int centroid = find_centroid(root, 0, sz);
	ok[centroid] = true;
	
	calc_dist(centroid, centroid);

	for (int v : tree[centroid]) {
		if (!ok[v]) {
			int child_centroid = build_ctree(v);
			c_tree[centroid].emplace_back(child_centroid);
			parent[child_centroid] = centroid;
		}
	}

	return centroid;
}

void update(int x) {
	for (int u = x; u != 0; u = parent[u]) {
		ans[u] = min(ans[u], dist[u][x]);
	}
}

int query(int x) {
	int ret = 0x3f3f3f3f;

	for (int u = x; u != 0; u = parent[u]) {
		ret = min(ret, dist[u][x]+ans[u]);	
	}

	return ret;
}

int main(void) {
	memset(ans, 0x3f, sizeof ans);

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n-1; i++) {
		int a, b; scanf("%d %d", &a, &b);
		tree[a].eb(b);
		tree[b].eb(a);
	}

	parent[build_ctree(1)] = 0;

	update(1);

	for (int i = 0; i < m; i++) {
		int t, x; scanf("%d %d", &t, &x);

		if (t == 1) update(x);
		else printf("%d\n", query(x));
	}
    

	return 0;
}
