bool dfs(int u) {
    visit[u] = true;

    for(int i = 0; i < g[u].size(); i++) {
        int adj = g[u][i];
        if (match[adj] == 0){
            match[adj] = u;
            return true;
        } else if (!visit[match[adj]]) {
            if (dfs(match[adj])) {
                match[adj] = u;
                return true;
            }
        }
    }

    return false;
}

for(int i = 0; i < n; i++) memset(visit, 0, sizeof visit);
dfs(i);
