#include <bits/stdc++.h>
using namespace std;

const int N = 2501;
ll bit[N][N];

void update(int x, int y, ll val) {
	for (int i = x; i <= n; i += i & -i) {
		for (int j = y; j <= m; j += j & -j) {
			bit[i][j] += val;
		}
	}
}

ll query(int x, int y) {
	ll ret = 0;

	for (int i = x; i > 0; i -= i & -i) {
		for (int j = y; j > 0; j -= j & -j) {
			ret += bit[i][j];
		}
	}

	return ret;
}

int main(void){

	return 0;
}
