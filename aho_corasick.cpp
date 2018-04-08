#include <bits/stdc++.h>
using namespace std;

const int MAXS = 112345; //Sum of the lenght of all keywords
const int MAXC = 26; //Max chars in alphabet

int out[MAXS]; 

int f[MAXS];
int g[MAXS][MAXC];

int buildMatchingMachine(const vector<string> &words,
                         char lowestChar = 'a',
                         char highestChar = 'z') {
    memset(out, 0, sizeof out);
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    
    int states = 1;
        
    for (int i = 0; i < words.size(); ++i) {
        const string &keyword = words[i];
        int currentState = 0;
        for (int j = 0; j < keyword.size(); ++j) {
            int c = keyword[j] - lowestChar;
            if (g[currentState][c] == -1) {
                g[currentState][c] = states++;
            }
            currentState = g[currentState][c];
        }
        out[currentState] |= (1 << i);
    }
    
    for (int c = 0; c < MAXC; ++c) {
        if (g[0][c] == -1) {
            g[0][c] = 0;
        }
    }

    queue<int> q;
    for (int c = 0; c <= highestChar - lowestChar; ++c) {
        if (g[0][c] != -1 and g[0][c] != 0) {
            f[g[0][c]] = 0;
            q.push(g[0][c]);
        }
    }
    while (q.size()) {
        int state = q.front();
        q.pop();
        for (int c = 0; c <= highestChar - lowestChar; ++c) {
            if (g[state][c] != -1) {
                int failure = f[state];
                while (g[failure][c] == -1) {
                    failure = f[failure];
                }
                failure = g[failure][c];
                f[g[state][c]] = failure;

                out[g[state][c]] |= out[failure]; 
                q.push(g[state][c]);
            }
        }
    }

    return states;
}

int findNextState(int currentState, char nextInput,
                                    char lowestChar = 'a') {
    int answer = currentState;
    int c = nextInput - lowestChar;
    while (g[answer][c] == -1) answer = f[answer];
    return g[answer][c];
}

// Example:
//
// Assume keywords is a vector that contains
// {"he", "she", "hers", "his"} and text is a string that
// contains "ahishers".
//
// Consider this program:
//
// buildMatchingMachine(keywords, 'a', 'z');
// int currentState = 0;
// for (int i = 0; i < text.size(); ++i) {
//    currentState = findNextState(currentState, text[i], 'a');
//
//    Nothing new, let's move on to the next character.
//    if (out[currentState] == 0) continue;
//
//    for (int j = 0; j < keywords.size(); ++j) {
//        if (out[currentState] & (1 << j)) {
//            //Matched keywords[j]
//            cout << "Keyword " << keywords[j]
//                 << " appears from "
//                 << i - keywords[j].size() + 1
//                 << " to " << i << endl;
//        }
//    }
// }

int main() {
	string text;
	vector<string> keywords;

	cin >> text;

	string s;
	while (cin >> s) {
		keywords.emplace_back(s);
	}

	buildMatchingMachine(keywords, 'a', 'z');
	int currentState = 0;
	for (int i = 0; i < text.size(); ++i) {
	currentState = findNextState(currentState, text[i], 'a');

	if (out[currentState] == 0) continue;
		for (int j = 0; j < keywords.size(); ++j) {
			if (out[currentState] & (1 << j)) {

				cout << "Keyword " << keywords[j]
					 << " appears from "
					 << i - keywords[j].size() + 1
					 << " to " << i << endl;
					 
			}
		}
	}

	return 0;
}
