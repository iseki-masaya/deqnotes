#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <sstream>
#include <set>
#include <cmath>
#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <numeric>

#define INF (1<<30)
#define EPS 1e-6

using namespace std;

#define MAX_N 1001

string a,b;
int dp[MAX_N][MAX_N];

void
solve()
{
    int N = (int)a.size();
    int M = (int)b.size();
    if (N == 0 || M == 0) {
        puts("0");
        return;
    }
    memset(dp, 0, sizeof(dp));

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=M; ++j) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    printf("%d\n",dp[N][M]);
}

int
main()
{
    while (cin >> a >> b) {
        solve();
    }
    return 0;
}