#include <bits/stdc++.h>
using namespace std;

const int INF =  0x3f3f3f3f;
const int N = 1123;

int capacity[N][N], flow[N][N];
int prv[N];
vector<int> adj[N];
int source, sink;

bool bfs() {
    queue<int> q;
    memset(prv, -1, sizeof prv);
    prv[source] = -2;
    q.push(source);

    while (!q.empty()) {
        int u = q.front(); 
        q.pop();

        if (u == sink) return true;

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (prv[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                prv[v] = u;
                q.push(v);
            }
        }
    }

    return false;
}

int augment() {
    int max_flow = INF;

    for (int v = sink; v != source; v = prv[v]) {
        max_flow = min(max_flow, capacity[prv[v]][v] - flow[prv[v]][v]);
    }

    for (int v = sink; v != source; v = prv[v]) {
        flow[prv[v]][v] += max_flow;
        flow[v][prv[v]] -= max_flow;
    }

    return max_flow;
}

int max_flow() {
    int ret = 0; 

    while (bfs()) {
        ret += augment();
    }

    return ret;
}


int main() {
    //setar source e sink

    return 0;
}
