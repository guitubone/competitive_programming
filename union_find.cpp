const int N = 112345;
int uf[N];

int find(int x) { 
  if (uf[x] < 0) return x;
  return uf[x] = find(uf[x]);
}

void uni(int a, int b) {
    int aa = find(a), bb = find(b);

	if (uf[aa] < uf[bb]) swap(aa, bb);

    uf[bb] += uf[aa];
	uf[aa] = bb;
}
