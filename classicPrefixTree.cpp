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

#define F first
#define S second
#define pb push_back
#define INF 1<<30
#define mp make_pair
#define pi pair<int, int>
#define readString(s) gets(rs);s = rs
#define y1 yyy1
#define y2 yyy2
#define SQR(a) ((a)*(a))
#define for3(i) for(int i = 0; i<3; i++)

#define swag swap

using namespace std;

const int N = 1111;

int n, m;
char buff[N];

class prefixTree
{
public:

    static const int alphSize = 300;

    struct Node
    {
        Node* a[alphSize];
        int finish;

        Node() : finish(0)
        {
            for(int i = 0; i<alphSize; i++)
                a[i] = 0;
        }
    };

    Node *root;

    prefixTree()
    {
        root = new Node();
    }

    bool check(string s)
    {
        Node *x = root;
        int cur = 0;

        while (cur < s.size() && x->a[s[cur]] != 0)
            x = x->a[s[cur++]];

        return (cur == s.size() && x->finish);
    }

    void add(string s)
    {
        Node *x = root;
        int cur = 0;

        while (cur < s.size() && x->a[s[cur]] != 0)
            x = x->a[s[cur++]];

        while (cur < s.size())
        {
            x->a[s[cur]] = new Node();
            x = x->a[s[cur++]];
        }

        x->finish++;
    }
};

int main()
{
    #define TASKNAME "disease"

    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w",stdout);
    #else
        //freopen(TASKNAME".in", "r", stdin);
        //freopen(TASKNAME".out", "w", stdout);
    #endif

    scanf("%d", &n);
    gets(buff);

    prefixTree p;

    for(int i = 0; i<n; i++)
    {
        gets(buff);
        p.add(buff);
    }

    scanf("%d", &m);
    gets(buff);

    for(int i = 0; i<m; i++)
    {
        gets(buff);
        printf("%d", p.check(buff));
    }

    return 0;
}
