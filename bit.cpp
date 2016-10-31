#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100005;
ll bit[N];

ll query(int id) {
	ll sum  = 0;
	while (id > 0) {
		sum += bit[id];
		id -= id & -id;
	}
	return sum;
}

void update(int id, int val) {
	while (id <= N) {
		bit[id] += val;
		id += id & -id;
	}
}

int main() {
	int n; cin >> n;
 
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		update(a, b);
	}	

	cout << query(4) << endl;


	return 0;
}
