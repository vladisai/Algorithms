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

int n, m;

struct Edge
{
    Edge* reversed;
    int x, y, flow, capacity;
    int other;

    Edge(int s, int f, int cap, int flow = 0)
    {
        this->flow = flow;
        x = s;
        y = f;
        capacity = cap;
        other = y;
        reversed = 0;
    }


    int residualCap()
    {
        return capacity - flow;
    }

};

vector<vector<Edge> > v;
Edge *p[N];

bool getWay(vector<Edge*> &w, int s = 0, int f = n - 1)
{
    w.clear();

    memset(p, 0, sizeof(p));

    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int i = 0; i<v[cur].size(); i++)
        {
            if (v[cur][i].residualCap() > 0 && p[v[cur][i].other] == 0)
            {
                p[v[cur][i].other] = &v[cur][i];
                q.push(v[cur][i].other);
            }
        }
    }

    if (p[f] == 0)
        return false;

    int cur = f;

    while (p[cur] != 0)
    {
        w.pb(p[cur]);
        cur = p[cur]->x;
    }

    reverse(w.begin(), w.end());

    return true;
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

    for(int i = 0; i<n; i++)
    {
        int x, y, f;
        scanf("%d%d%d", &x, &y, &f);
        x--;
        y--;

        v[x].pb(Edge(x, y, f, 0));
        v[y].pb(Edge(y, x, f, f));

        v[x].back().reversed = &(v[y].back());
        v[y].back().reversed = &(v[x].back());
    }

    vector<Edge*> way;

    int ans = 0;

    while (getWay(way))
    {
        int bottleneck = INF;
        for(int i = 0; i<way.size(); i++)
            bottleneck = min(bottleneck, way[i]->residualCap());

        for(int i = 0; i<way.size(); i++)
        {
            way[i]->flow += bottleneck;
            way[i]->reversed->flow -= bottleneck;
        }

        ans += bottleneck;
    }

    printf("%d", ans);

    return 0;
}
