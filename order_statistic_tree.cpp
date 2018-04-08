#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> s;

#define eb emplace_back
#define emp emplace
#define fi first
#define se second
#define INF 0x3f3f3f3f
typedef long long ll;
typedef pair<int, int> ii;

int main(void) {
	ios_base::sync_with_stdio(false);
    
	s.insert(1);
	s.insert(3);
	s.insert(4);
	s.insert(7);
	s.find_by_order(2);
	s.order_of_key(1);
	return 0;
}

