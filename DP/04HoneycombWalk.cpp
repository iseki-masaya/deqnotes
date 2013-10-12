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

#define MAX_N 50

int dx[2][6] = { {-1,0,1,-1,-1,0} , {0,1,1,-1,0,1} };
int dy[6] = {-1,-1,0,0,1,1};

int dp[15][MAX_N][MAX_N];
int N;

void
solve()
{
    memset(dp, 0, sizeof(dp));
    int c = MAX_N/2;
    dp[0][c][c] = 1;
    for (int i=0; i<N; ++i) {
        for (int y=0; y<MAX_N; ++y) {
            for (int x=0; x<MAX_N; ++x) {
                if (dp[i][y][x] == 0) {
                    continue;
                }

                for (int j=0; j<6; ++j) {
                    int cx = x + dx[y&1][j];
                    int cy = y + dy[j];
                    dp[i+1][cy][cx] += dp[i][y][x];
                }
            }
        }
    }

    printf("%d\n",dp[N][c][c]);
}

int
main()
{
    int num;
    scanf("%d",&num);
    for (int i=0; i<num; ++i) {
        scanf("%d",&N);
        solve();
    }
}