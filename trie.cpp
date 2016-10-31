#include <bits/stdc++.h>
using namespace std;

struct Trie {
    bool hasWord;
    map <char, Trie> adj;

    void insertt(string &s, int i) {
        if (i==s.size()) hasWord = true;
        else adj[s[i]].insertt(s, i+1);
    }

    bool searchh(string &s, int i) {
        if (i==s.size()) return hasWord;
        else {
            if (adj.count(s[i])) return adj[s[i]].searchh(s, i+1);
	    else return false;
        }
    }
};

int main (void){
    struct Trie t;
    string str = "abcd";
    string key = "abcd";

    t.insertt(str, 0);

    if (t.searchh(key,0)) cout << "Yee" << endl;

    return 0;
}
