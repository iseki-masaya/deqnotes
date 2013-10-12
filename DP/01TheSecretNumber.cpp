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

#define MAX_W 71
#define MAX_H 71

int W,H;
char t[MAX_H][MAX_W];
string c[MAX_H][MAX_W];

bool
init()
{
    scanf("%d %d",&W,&H);
    if (W == 0 && H == 0) {
        return false;
    }
    for (int y=0; y<H; ++y) {
        scanf("%*c");
        for (int x=0; x<W; ++x) {
            scanf("%c",&t[y][x]);
        }
    }
    return true;
}

string
string_max(string lhs,string rhs)
{
    if (lhs.size() > rhs.size())
        return lhs;
    else if (rhs.size() > lhs.size())
        return rhs;
    else
        return max(lhs, rhs);
}

void
solve()
{
    string ans = "";
    for (int y=0; y<H; ++y) {
        for (int x=0; x<W; ++x) {
            c[y][x] = "";
            if (t[y][x] < '0' || '9' < t[y][x]) {
                continue;
            }

            if (y>0) {
                c[y][x] = string_max(c[y][x], c[y-1][x]);
            }
            if (x>0) {
                c[y][x] = string_max(c[y][x], c[y][x-1]);
            }
            c[y][x] += t[y][x];
            if (c[y][x] == "0") {
                c[y][x] = "";
            }
            ans = string_max(ans, c[y][x]);
        }
    }
    printf("%s\n",ans.c_str());
}

int
main()
{
    while (init()) {
        solve();
    }
    return 0;
}