const int N = 30007;

vector<int> seg[4*N];
int v[N], a, b, k;

void build(int r, int i, int j) {
	if (i == j) {
		seg[r].pb(v[i]); 
	} else {
		int mi = (i+j)/2;
		build(2*r, i, mi);
		build(2*r+1, mi+1, j);
		seg[r].insert(seg[r].end(), seg[2*r].begin(), seg[2*r].end());
		seg[r].insert(seg[r].end(), seg[2*r+1].begin(), seg[2*r+1].end());
		sort(seg[r].begin(), seg[r].end());
	}
}

int query(int r, int i, int j) {
	if (i > b or j < a) {
		return 0;
	}

	if (i >= a and j <= b) {
		int ret = seg[r].size() - (upper_bound(seg[r].begin(), seg[r].end(), k) - seg[r].begin());
		return ret;
	}
	else {
		int mi = (i+j)/2;
		int L = query(2*r, i, mi);
		int R = query(2*r+1, mi+1, j);

		return L+R;
	}
}
