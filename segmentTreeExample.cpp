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

const int N = 1111111;

int n, a[N];

class Tree
{
public:

    class Node
    {
    public:
        bool flag;
        Node *left, *right;
        int l, r;
        int64_t val;

        Node(int lo, int hi) : val(0), l(lo), r(hi), flag(false)
        {
            left = 0, right = 0;
            if (l != r)
            {
                left = new Node(l, (l+r)/2);
                right = new Node((l+r)/2+1, r);
            }
        }
    };

    Node *root;

    Tree(int sz = N)
    {
        root = new Node(0, sz);
    }

    void modify(int ind, int64_t val)
    {
        root = modify(root, ind ,val);
    }

    Node *modify(Node *x, int ind, int64_t val)
    {
        if (x->l > ind || x->r < ind)
            return x;

        if (x->l == x->r && x->l == ind)
            x->val += val;
        else if (x->right != 0 && x->left != 0)
        {
            x->left = modify(x->left, ind, val);
            x->right = modify(x->right, ind, val);
            x->val = x->left->val + x->right->val;
        }

        return x;
    }

    void zero(int l, int r)
    {
        root = zero(root, l, r);
    }

    Node *zero(Node *x, int l, int r)
    {
        if (l > r)
            return x;
        if (x->l > r || x->r < l)
            return x;

        l = max(x->l, l);
        r = min(x->r, r);

        if (l == x->l && r == x->r)
        {
            x->flag = true;
            x->val = 0;
        }
        else
        {
            x->left = zero(x->left, l, r);
            x->right = zero(x->right, l, r);
            x->val = x->left->val + x->right->val;
        }
        return x;
    }

    int64_t getSum(int l, int r)
    {
        return getSum(root, l, r);
    }

    int64_t getSum(Node *x, int l, int r)
    {
        if (l>r)
            return 0;

        if (x->l > r || x->r < l)
            return 0;

        if (x->flag)
            return 0;

        l = max(x->l, l);
        r = min(x->r, r);

        if (l == x->l && r == x->r)
        {
            return x->val;
        }
        else
        {
            int64_t res = 0;
            res += getSum(x->left, l, r);
            res += getSum(x->right, l, r);
            return res;
        }
    }
} *t;

void pourIn(int ind, int64_t v)
{
    int lo = ind, hi = n - 1;

    while (lo < hi)
    {
        int m = (lo+hi)/2;
        int64_t sum = t->getSum(ind, m);

        if (sum > v)
            hi = m;
        else
            lo = m+1;
    }

    if (lo == n-1 && t->getSum(ind, n-1) <= v)
    {
        t->zero(ind, n-1);
        return;
    }

    int64_t sum = 0;
    sum = t->getSum(ind, lo-1);
    t->zero(ind, lo-1);

    t->modify(lo, -(v-sum));
}

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

    t = new Tree(n);

    for(int i = 0; i<n; i++)
    {
        scanf("%d", a+i);
        t->modify(i, a[i]);
    }


    int m;
    scanf("%d", &m);

    while (m--)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int ind, v;
            scanf("%d%d", &ind, &v);
            ind--;
            pourIn(ind, v);
        }
        else
        {
            int ind;
            scanf("%d", &ind);
            ind--;
            int64_t res = t->getSum(ind, ind);
            printf("%I64d\n", a[ind] - res);
        }
    }

    return 0;
}
