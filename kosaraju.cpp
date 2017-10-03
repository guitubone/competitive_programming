#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, m;
vector<int> g[N], rg[N];
stack<int> st;
int comp[N], vis[N];

void topo_sort(int u) {
	vis[u] = 1;
	for (int v : g[u]) {
		if (!vis[v]) topo_sort(v);
	}
	st.emplace(u);
}

void get_scc(int u, int c) {
	vis[u] = 1;
	comp[u] = c;
	for (int v : rg[u]) {
		if (!vis[v]) get_scc(v, c);
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		g[a].emplace_back(b);
		rg[b].emplace_back(a);
	}

	for (int i = 0; i < n; i++) {
		if (!vis[i]) topo_sort(i);
	}
	
	memset(vis, 0, sizeof vis);

	int curr_comp = 0;
	while (!st.empty()) {
		if (!vis[st.top()])
			get_scc(st.top(), curr_comp++);
		st.pop();
	}

	for (int i = 0; i < n; i++) cout << comp[i] << " ";
	cout << endl;
    
	return 0;
}

