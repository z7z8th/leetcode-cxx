#include <bits/stdc++.h>
using namespace std;
unordered_map<long, int> dic;
 
int main(void)
{
//    freopen("input.txt", "r", stdin);
    int n, m, k, t, x, y, c, Q, a, b, ans;
    cin >> n >> m >> k;
    int pointX[n], pointY[m];
    for (int i = 0; i < n; ++i) {
        pointX[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        pointY[i] = i;
    }
    for(int i = 0; i < k; i++) {
        scanf("%d%d%d", &x, &y, &c);
        dic[x * m + y] = c;
    }
    cin >> t;
    while(t--) {
        scanf("%d%d%d", &Q, &a, &b);
        if(Q == 2) {
            int key = pointX[a] * m + pointY[b];
            int ans;
            if(dic.find(key) == dic.end()) ans = -1;
            else ans = dic[key];
            printf("%d\n", ans);
        } else if(Q == 0) {
            swap(pointX[a], pointX[b]);
        } else {
            swap(pointY[a], pointY[b]);
        }
    }
    return 0;
}