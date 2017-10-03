#include <bits/stdc++.h>
#define N 500
using namespace std;

const int max_x = N;
const int max_y = N;
int bit[N][N];

void update_y(int x, int y, int value){
    while(y <= max_y){
        bit[x][y] += value;
        y += y & -y;
    }
}

void update(int x, int y, int value){
    while(x <= max_x){
        update_y(x, y, value); 
        x += x & -x;
    }
}

int query_y(int x, int y){
    int sum = 0;
    while(y > 0){
        sum += bit[x][y];
        y -= y & -y;
    }
    return sum;
}

int query(int x, int y){
    int sum = 0;
    while(x > 0){
        sum += query_y(x, y);
        x -= x & -x;
    }
    return sum;
}

int main(void){
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int p;
            cin >> p;
            update(i, j, p);
        }
    }
   for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << endl;
   } 
}
