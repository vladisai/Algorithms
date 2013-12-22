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

vector<int> v;

void shuffle(vector<int>::iterator begin, vector<int>::iterator end)
{
    int l = int(end-begin);
    for(vector<int>::iterator i = begin; i != end-1; i++)
    {
        int k = rand()%int(end-i-1) + 1;
        swag(*i, *(i+k));
    }
}

void customSort(vector<int>::iterator begin, vector<int>::iterator end)
{
    vector<int>::iterator i = begin+1, j = end-1;

    while (i<=j)
    {
        while (*begin > *i) i++;
        while (*begin < *j) j--;
        if (i < j)
            swag(*i, *j);
    }

    swag(*begin, *j);

    if (begin < i-1)
        customSort(begin, i);
    if (i < end-1)
        customSort(i, end);
}

void customSortDuplicateKeys(vector<int>::iterator begin, vector<int>::iterator end)
{
    vector<int>::iterator trueEnd = end-1;
    if (begin >= end-1) return;

    vector<int>::iterator i = begin + 1, j = end - 1, x = begin;

    while (i <= j)
    {
        if (*i > *x)
        {
            swag(*i, *j);
            j--;
        }
        else
        if (*i == *x)
            i++;
        else
        if (*i < *x)
        {
            swap(*i, *x);
            x++;
            i++;
        }
    }

    customSortDuplicateKeys(begin, x);
    customSortDuplicateKeys(j+1, end);
}

void pascalStyleSort(vector<int>::iterator begin, vector<int>::iterator end)
{
    vector<int>::iterator i = begin, j = end-1;
    int x = *(begin + int(end - begin)/2);

    do
    {
        while (*i < x) i++;
        while (*j > x) j--;
        if (i<=j)
        {
            swag(*i, *j);
            i++;
            j--;
        }
    }while (i<=j);

    if (begin < j)
        pascalStyleSort(begin, j+1);
    if (i < end - 1)
        pascalStyleSort(i, end);
}

bool isSorted(vector<int>::iterator begin, vector<int>::iterator end)
{
    for(vector<int>::iterator i = begin; i<end-1; i++)
    {
        if (*i > *(i+1))
            return false;
    }
    return true;
}

void output(vector<int>::iterator begin, vector<int>::iterator end)
{
    printf("\n");
    for(vector<int>::iterator i = begin; i!=end; i++)
        printf("%d ", *i);
    printf("\n");
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

    srand(time(NULL));

    v.resize(100000);
    for(int i = 0; i<v.size(); i++)
    {
        v[i] = 4;
    }

    shuffle(v.begin(), v.end());

    //output(v.begin(), v.end());

    pascalStyleSort(v.begin(), v.end());

    //output(v.begin(), v.end());

    if (isSorted(v.begin(), v.end()))
        printf("Sorted");
    else
        printf("Not sorted");

    return 0;
}
