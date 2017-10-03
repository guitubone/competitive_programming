#include <bits/stdc++.h>
using namespace std;

const int N = 112345;
int vis[N];
vector <int> g[N];
vector <int> w[N];

void dijkstra(int beg) {
	for (int i = 0; i < N; i++)
		vis[i] = -1;

	vis[beg] = 0;
	priority_queue <pair <int,int> > pq;
	pq.push(make_pair(0, beg));
	
	while(!pq.empty()) {
		int curr = pq.top().second;
		int d = -pq.top().first;
		pq.pop();

		if (d > vis[curr]) continue;

		for (int i = 0; i < g[curr].size(); i++) {
			int next = g[curr][i];
			int p = w[curr][i];
			if (vis[next] == -1 or vis[next] > d+p) {
				vis[next] = d+p;
				pq.push(make_pair(-(d+p), next));
			}
		}
	}
}

int main(void) {
	int v, a;

	cin >> v >> a;

	for (int i = 0; i < a; i++) {
		int x, y, dist;

		cin >> x >> y;
		cin >> dist;

		g[x].push_back(y);
		g[y].push_back(x);

		w[x].push_back(dist);
		w[y].push_back(dist);
	}

	int z;
	cin >> z;

	dijkstra(z);

	int p;
	cin >> p;
	cout << vis[p];

	return 0;
}
