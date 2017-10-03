#include <bits/stdc++.h>
using namespace std;

const int N = 1123456;

int n;
string s;
int Z[N];

void genZ() {
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) Z[i] = min(Z[i-l], r-i+1);
		while (Z[i]+i < n && s[Z[i]+i] == s[Z[i]]) Z[i]++;
		if (r < i+Z[i]-1) l = i, r = i+Z[i]-1;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin >> s;
	n = s.size();

	genZ();

	for (int i = 0; i < n; i++) cout << Z[i] << " ";
	cout << endl;

	return 0;
}
