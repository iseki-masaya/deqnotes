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

#define INF (1<<28)
#define EPS 1e-8

using namespace std;

typedef pair<int, int> P;

#define MAX_W 25
#define MAX_H 25

const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};

int W,H;
vector<string> m;
int cost[MAX_H][MAX_W];
int dp[12][(1<<12)];

struct Q {
  P p;
    int depth;
    Q(P p,int d) : p(p) , depth(d) {}
};

void
make_mat(vector<P> &ps)
{
    for (int y=0; y<H; ++y) {
        for (int x=0; x<W; ++x) {
            if (m[y][x] == '*') {
                ps.push_back(P(x,y));
            }
        }
    }
}

P
find_start()
{
    P p;
    for (int y=0; y<H; ++y) {
        for (int x=0; x<W; ++x) {
            if (m[y][x] == 'o') {
                p.first = x , p.second = y;
                return p;
            }
        }
    }
    return P(-1,-1);
}

int
make_dist_mat()
{
    vector<P> ps;
    ps.push_back(find_start());
    make_mat(ps);
    int N = (int)ps.size();

    int dist[MAX_H][MAX_W];
    for (int i=0; i<N; ++i) {
        memset(dist, -1, sizeof(dist));
        queue<Q> que;
        que.push(Q(ps[i],0));

        while (!que.empty()) {
            Q q = que.front();
            que.pop();
            int x = q.p.first , y = q.p.second;

            if (m[y][x] == 'x' || dist[y][x] != -1) {
                continue;
            }
            dist[y][x] = q.depth;

            for (int j=0; j<4; ++j) {
                int cx = x + dx[j] , cy = y + dy[j];
                if (0 <= cx && cx < W && 0 <= cy && cy < H && dist[cy][cx] == -1) {
                    que.push(Q(P(cx,cy),q.depth+1));
                }
            }
        }

        for (int j=0; j<ps.size(); ++j) {
            if (i != j) {
                int x = ps[j].first , y = ps[j].second;
                cost[i][j] = dist[y][x];
                if (dist[y][x] < 0) {
                    return -1;
                }
            }
        }
    }

    return N;
}

bool
init()
{
    scanf("%d%d",&W,&H);
    if (W == 0 && H == 0) {
        return false;
    }
    m.clear();
    for (int i=0; i<H; ++i) {
        string str;
        cin >> str;
        m.push_back(str);
    }

    for (int i=0; i<H; ++i) {
        fill(cost[i], cost[i]+W, INF);
    }
    return true;
}

void
solve()
{
    int N = make_dist_mat();
    if (N == -1) {
        puts("-1");
        return;
    }

    for (int i=0; i<11; ++i) {
        fill(dp[i], dp[i] + (1<<11), INF);
    }

    int lim = (1<<N);
    dp[0][1] = 0;
    for (int mask = 1; mask < lim-1 ; ++mask) {
        for (int from=0; from<N; ++from) {
            for (int to=0; to<N; ++to) {
                if (!(mask >> to & 1) && (mask >> from & 1)) {
                    dp[to][mask + (1<<to)] = min( dp[to][mask + (1<<to)] , dp[from][mask] + cost[from][to] );
                }
            }
        }
    }

    int ans = INF;
    for (int i=0; i<N; ++i) {
        ans = min( ans , dp[i][lim-1] );
    }
    printf("%d\n",ans);
}

int
main()
{
    while (init()) {
        solve();
    }
    return 0;
}