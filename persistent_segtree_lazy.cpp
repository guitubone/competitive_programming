// Persistent Segment Tree with range update
// Solves problem http://www.spoj.com/problems/TTM/
 
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
const int LOGN = 18;
 
ll v[N], seg[4*N+3*N*LOGN], lazy[4*N+3*N*LOGN], L[4*N+3*N*LOGN], R[4*N+3*N*LOGN], root[N];
int a, b, max_nodes;
ll val;
 
int build(int i, int j) {
	int curr = max_nodes++;
 
	if (i == j) {
		seg[curr] = v[i];
	} else {
		int m = (i+j)/2;
		L[curr] = build(i, m);
		R[curr] = build(m+1, j);
		seg[curr] = seg[L[curr]] + seg[R[curr]];
	}
 
	return curr;
}
 
int update(int id, int i, int j) {
	if (j < a or i > b) return id;
 
	int curr = max_nodes++;

	if (a <= i and j <= b) {
		seg[curr] = seg[id];
		lazy[curr] = lazy[id] + val;
		L[curr] = L[id];
		R[curr] = R[id];
	} else {
		int m = (i+j)/2;
		seg[curr] = seg[id] + val * (min(j, b) - max(i, a) + 1);
		lazy[curr] = lazy[id];
		L[curr] = update(L[id], i, m);
		R[curr] = update(R[id], m+1, j);
	}
 
	return curr;
}
 
ll query(int id, int i, int j, ll sum_lazy) {
	if (j < a or i > b) return 0;

	sum_lazy += lazy[id];
	
	if (a <= i and j <= b) {
		return seg[id] + (j-i+1) * sum_lazy;
	} else {
		int m = (i+j)/2;
		return query(L[id], i, m, sum_lazy) + query(R[id], m+1, j, sum_lazy);
	}
}
 
int main(void) {
	ios_base::sync_with_stdio(false);
 
	int n, q; cin >> n >> q;
 
	for (int i = 0; i < n; i++) cin >> v[i];
 
	root[0] = build(0, n-1);
 
	int curr_time = 0;
	for (int i = 0; i < q; i++) {
		char type; cin >> type;
 
		if (type == 'C') {
			cin >> a >> b >> val; a--; b--;
			curr_time++;
			root[curr_time] = update(root[curr_time-1], 0, n-1);
		} else if (type == 'Q') {
			cin >> a >> b; a--; b--;
			cout << query(root[curr_time], 0, n-1, 0) << endl;
		} else if (type == 'H') {
			cin >> a >> b; a--; b--;
			int t; cin >> t;
			cout << query(root[t], 0, n-1, 0) << endl;
		} else if (type == 'B') {
			cin >> curr_time;
		}
	}
 
	return 0;
}

