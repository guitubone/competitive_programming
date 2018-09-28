#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename tA, typename tB=null_type> using ord_set = tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update>;

ord_set<int> s;

int main(void) {
	ios_base::sync_with_stdio(false);

	s.insert(1);
	s.insert(3);
	s.insert(4);
	s.insert(7);
	cout << *s.find_by_order(2) << endl;
	cout << s.order_of_key(1) << endl;
	return 0;
}
