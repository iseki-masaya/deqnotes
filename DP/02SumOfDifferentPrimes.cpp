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

#define MAX_N 1125
#define MAX_K 15

vector<int> primes;
int cache[MAX_N][MAX_K][200];

void
sieve()
{
    bool is_prime[MAX_N];
    memset(is_prime, false, sizeof(is_prime));
    for (int i = 2; i < MAX_N; ++i) {
        if (!is_prime[i]) {
            is_prime[i] = true;
            primes.push_back(i);
            for (int j=2*i; j < MAX_N; j += i) {
                is_prime[j] = true;
            }
        }
    }
}

int
solve(int n,int k,int idx)
{
    if (n == 0 && k == 0) {
        return 1;
    }
    if (n == 0 || k == 0) {
        return 0;
    }
    if (cache[n][k][idx] >= 0) {
        return cache[n][k][idx];
    }

    int sum = 0;
    for (int i=idx; i<primes.size(); ++i) {
        if (primes[i] > n) {
            break;
        }
        else {
            sum += solve(n - primes[i], k-1, i+1);
        }
    }
    return cache[n][k][idx] = sum;
}

bool
init(int &n,int &k)
{
    scanf("%d %d",&n,&k);
    return n > 0;
}

int
main()
{
    sieve();
    memset(cache, -1, sizeof(cache));
    int n,k;
    while (init(n,k)) {
        int ans = solve(n,k,0);
        printf("%d\n",ans);
    }
    return 0;
}