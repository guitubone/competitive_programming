#include <iostream>
using namespace std;

int mod = 1e9+7;
int pot (int x, int y) {
	if (y == 0) return 1;
	int res = pot(x, y/2);
	res = (res * res) % mod;
	if (y % 2) res = (res * x) % mod;
	return res;
}

int main(int argc, char *argv[]) {
	long long result = pot(13, 2012);
	cout << result << endl;
	return 0;
}
