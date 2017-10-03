#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

const int INF = 1000000000; 
const int N= 22000;

struct edge {
	int a, b, cap, flow;
	edge() {}
	edge(int a, int b, int cap, int flow):a(a), b(b), cap(cap), flow(flow){}
};

int so, si, d[N], ptr[N], q[N];
vector<edge> e;
vi g[N];

void add_edge (int a, int b, int cap) {
	edge e1(a, b, cap, 0 );
	edge e2(b, a, 0, 0 ); //back edge
	g[a].push_back ((int) e.size());
	e.push_back(e1);
	g[b].push_back ((int) e.size());
	e.push_back(e2);
}

bool bfs() {
	int qh=0, qt=0;
	q[qt++]=so;
	memset (d, -1, sizeof d);
	d[so] = 0;
	while(qh<qt && d[si]==-1) {
		int v=q[qh++];
		for(size_t i=0; i<g[v].size(); ++i) {
			int id = g[v][i],
			to = e[id].b;
			if(d[to] == -1 && e[id].flow < e[id].cap) {
				q[qt++]=to;
				d[to] = d[v] + 1;
			}
		}
	}
	return d[si]!=-1;
}

int dfs (int v, int flow) {
	if (!flow)  return 0;
	if (v == si)  return flow;
	for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
		int id = g[v][ptr[v]],
		to = e[id].b;
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
		if (pushed) {
			e[id].flow += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}

int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs())  break;
		memset (ptr, 0, sizeof ptr);
		while (int pushed = dfs (so, INF)) 
			flow += pushed;
	}
	return flow;
}

int main() {

	return 0;
}
