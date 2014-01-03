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
#include <stack>
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

const int N = 555;

int n, m;

struct Edge
{
    Edge* reversed;
    int x, y, flow, capacity;
    int other;

    Edge(int s, int f, int cap, int flow)
    {
        this->flow = flow;
        x = s;
        y = f;
        capacity = cap;
        other = y;
        reversed = 0;
    }

    int residualCapacity()
    {
        return capacity - flow;
    }
};

vector<vector<Edge*> > v;
Edge *p[N];
int dist[N];
int g[N];

void bfs(int ind)
{
    fill_n(dist, n, INF);

    queue<int> q, d;

    dist[ind] = 0;
    q.push(ind);

    while (!q.empty())
    {
        int curInd = q.front(); q.pop();

        for(int i = 0; i<v[curInd].size(); i++)
        {
            if (dist[v[curInd][i]->other] == INF && v[curInd][i]->residualCapacity() != 0)
            {
                dist[v[curInd][i]->other] = dist[curInd] + 1;
                q.push(v[curInd][i]->other);
            }
        }
    }
}

bool recalcDist()
{
    bfs(0);

    return dist[n-1] != INF;
}

int dfs(int ind, int flow)
{
    if (flow == 0)
        return 0;

    if (ind == n-1)
        return flow;

    int cur = 0;

    for(int &i = g[ind]; i<v[ind].size() && flow > 0; i++)
    {
        if (dist[v[ind][i]->other] == dist[ind] + 1)
        {
            int f = dfs(v[ind][i]->other, min(flow, v[ind][i]->residualCapacity()));

            if (f)
            {
                v[ind][i]->flow += f;
                v[ind][i]->reversed->flow -= f;
                return f;
            }
        }
    }

    return 0;
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

    scanf("%d%d", &n, &m);
    v.resize(n);

    for(int i = 0; i<m; i++)
    {
        int x, y, f;
        scanf("%d%d%d", &x, &y, &f);
        x--;
        y--;

        Edge *e = new Edge(x, y, f, 0);
        Edge *r = new Edge(y, x, f, f);

        e->reversed = r;
        r->reversed = e;

        v[x].pb(e);
        v[y].pb(r);
    }

    int64_t ans = 0;

    while (recalcDist())
    {
        fill(g, g+n, 0);

        while (int flow = dfs(0, INF))
            ans += flow;
    }

    cout<<ans;

    return 0;
}
