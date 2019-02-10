//Recursive
const int N = 100001;
int seg[4*N], v[N];
int a, b;

void init(int r, int i, int j) {
    if (i == j) {
        seg[r] = v[i];
    } else {
        init(2*r, i, (i+j)/2);
        init(2*r+1, (i+j)/2+1, j);
        seg[r] = seg[2*r] + seg[2*r+1];
    }
}

int query(int r, int i, int j) {
    if (b < i || a > j) return 0;
    if (i >= a && j <= b) {
        return seg[r];
    } else {
        int L = query(2*r, i, (i+j)/2);
        int R = query(2*r+1, (i+j)/2+1, j);
        return L+R;
    }
}

void update(int r, int i, int j, int pos, int val) {
    if (pos < i || pos > j) return;
    if (i == j) {
        seg[r] = val;
    } else {
        update(2*r, i, (i+j)/2, pos, val);
        update(2*r+1, (i+j)/2+1, j, pos, val);
        seg[r] = seg[2*r] + seg[2*r+1];
    }
}

//Iterative
// Ler t[i+n] para vetor inicial depois dar build

const int N = 1e5;
int n;
int t[2 * N];

void build() {
	for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

//Range Query and Point Update
void modify(int p, int value) {
	for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r)
	int res = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res += t[l++];
		if (r&1) res += t[--r];
	}
	return res;
}

//Range Update and Point Query
void modify(int l, int r, int value) {
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) t[l++] += value;
		if (r&1) t[--r] += value;
	}
}

int query(int p) {
	int res = 0;
	for (p += n; p > 0; p >>= 1) res += t[p];
	return res;
}
