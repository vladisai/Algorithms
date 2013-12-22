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
#define LL long
#define readString(s) gets(rs);s = rs
#define y1 yyy1
#define y2 yyy2
#define SQR(a) ((a)*(a))

#define swag swap

using namespace std;

const int N = 511111;

class PriorityQueue
{
public:

    int size;
    vector<int> v;

    PriorityQueue(int n = N)
    {
        this->size = 0;
        this->v.resize(n+1); /// we don'int want to use v[0]
    }

    void swim(int index)
    {
        while (index > 1 && compare(v[index], v[index/2]))
        {
            swag(v[index], v[index/2]);
            index /= 2;
        }
    }

    void sink(int index)
    {
        while (index * 2 < size)
        {
            int k = index * 2;
            if (k < size && compare(v[k+1], v[k])) k++;
            if (compare(v[k], v[index]))
            {
                swag(v[k], v[index]);
                index = k;
            }
            else break;
        }
    }

    void push(int n)
    {
        v[++size] = n;
        swim(size);
    }

    int pop()
    {
        int val = v[1];
        swag(v[1], v[size]);
        size--;
        sink(1);
        return val;
    }

    bool compare(int a, int b) const
    {
        return a<b;
    }

};

class HeapSort
{
public:
    int size;
    vector<int> v;

    void operator() (vector<int> &v)
    {
        this->v = v;
        size = v.size();
        makeTree(); ///make_heap(v.begin(), v.end()) will do the job too, but in reversed order
        while (size)
        {
            pop(); ///after we do pop, the top moves to the current end, i. e. minimums go to the end forming a sequence in descending order
        }
        v = this->v;
    }

    void makeTree()
    {
        int i = size-1;
        while(i >= 0)
        {
            if (i*2 < size)
                sink(i);
            i--;
        }
    }

    void swim(int index)
    {
        while (index > 0 && compare(v[index], v[(index-1)/2]))
        {
            swag(v[index], v[(index-1)/2]);
            index = (index-1)/2;
        }
    }

    void sink(int index)
    {
        while (index * 2 + 1 < size)
        {
            int k = index * 2 + 1;
            if (k < size-1 && compare(v[k+1], v[k])) k++;
            if (compare(v[k], v[index]))
            {
                swag(v[k], v[index]);
                index = k;
            }
            else break;
        }
    }

    void push(int n)
    {
        v[size++] = n;
        swim(size-1);
    }

    int pop()
    {
        int val = v[0];
        swag(v[0], v[size-1]);
        size--;
        sink(0);
        return val;
    }

    bool compare(int a, int b) const
    {
        return a>b;
    }
};

int main()
{

    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w",stdout);
    #else
        //freopen(TASKNAME".in", "r", stdin);
        //freopen(TASKNAME".out", "w", stdout);
    #endif

    vector<int> v;

    int n = 10;

    srand(time(NULL));

    for(int i = 0; i<n; i++)
    {
        v.pb(rand()%n);
    }

    HeapSort hs;
    hs(v);

    for(int i = 0; i<v.size(); i++)
    {
        printf("%d ", v[i]);
    }

    return 0;
}
