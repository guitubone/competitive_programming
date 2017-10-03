void gauss(vector<size_t> & nums) {
	for (size_t bit = 63; bit--;) {
		size_t findmask = 1ull << bit;
		size_t maxmask = 2*findmask-1;
		// search for number with given highest bit,
		// i.e. a number with `findmask` not greater than `maxmask`
		size_t j = 0;
		while (j < nums.size()) {
			if (nums[j] & findmask && nums[j] <= maxmask) break;
			++j;
		}
		if (j == nums.size()) continue;
		// eliminate bit in all entries but one
		for (size_t i = 0; i < nums.size(); ++i) {
			if (i == j) continue;
			if (nums[i] & findmask) nums[i] ^= nums[j];
		}
	}
}

vector<int> c; // vetores

int i = 0;
for (int b = 30; b >= 0 && i < c.size(); b--) {
	swap(c[i], *max_element(c.begin() + i, c.end()));
	if (!((c[i] >> b) & 1)) continue;
	for (int j = i + 1; j < c.size(); j++) {
		if ((c[j] >> b) & 1) c[j] ^= c[i];
	}
	i++;
}

// c ta escalonado e decrescente
