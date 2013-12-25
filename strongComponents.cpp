#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <list>
#include <queue>
#include <map>
#include <ctime>
#include <iterator>
#include <numeric>

#define F first
#define S second
#define pb push_back
#define INF 1<<30
#define mp make_pair
#define pi pair<int, int>
#define LL long
#define readString(s) gets(buff);s = buff
#define y1 yyy1
#define y2 yyy2
#define SQR(a) ((a)*(a))

#define swag swap

using namespace std;

const int N = 511111;

vector< vector<int> > v, r;
vector<int> order, res;
int n, m;
int p[N];

void dfst(int x)
{
    p[x] = 1;
    for(int i = 0; i<v[x].size(); i++)
    {
        if (!p[v[x][i]])
            dfst(v[x][i]);
    }

    order.pb(x);
}

void topSort()
{
    for(int i = 0; i<v.size(); i++)
    {
        if (p[i] == 0)
            dfst(i);
    }
}

void dfs(int x)
{
    for(int i = 0; i<r[x].size(); i++)
    {
        if (res[r[x][i]] == -1)
        {
            res[r[x][i]] = res[x];
            dfs(order[r[x][i]]);
        }
    }
}

int main()
{

    #ifdef DEBUG
       freopen("input.txt", "r", stdin);
       //freopen("output.txt", "w",stdout);
    #else
       //freopen(TASKNAME".in", "r", stdin);
       //freopen(TASKNAME".out", "w", stdout);
    #endif

    scanf("%d %d", &n, &m); //n vertices, m edges

    v.resize(n);
    r.resize(n);

    for(int i = 0; i<m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        v[x].pb(y);
        r[y].pb(x);
    }

    topSort();

    fill_n(inserter(res, res.begin()), n, -1);

    int cur = 0;

    for(int i = 0; i<order.size(); i++)
    {
        if (res[i] == -1)
        {
            res[i] = ++cur;
            dfs(i);
        }

    }

    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));

    return 0;
}
