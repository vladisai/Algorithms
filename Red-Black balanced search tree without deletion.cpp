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
#define readString(s) gets(buff);s = buff
#define y1 yyy1
#define y2 yyy2
#define SQR(a) ((a)*(a))

#define swag swap

using namespace std;

const int N = 1111111;

template<class Key, class Value>
class RedBlackBST
{
public:

    struct Node
    {
        Node *left, *right;
        bool isRed;
        Key key;
        Value value;

        Node(Key key, Value value)
        {
            this->key = key;
            this->value = value;
            isRed = true;
            left = 0;
            right = 0;
        }
    };

    Node *root;

    RedBlackBST()
    {
        root = 0;
    }

    void add(Key key, Value value)
    {
        root = add(root, key, value);
    }

    bool isRed(Node *x)
    {
        if (x == 0)
            return false;
        else
            return x->isRed;
    }

    Node* add(Node *x, Key key, Value value)
    {
        if (x == 0)
            return new Node(key, value);

        if (key < x->key)
            x->left = add(x->left, key, value);
        else if (key > x->key)
            x->right = add(x->right, key, value);

        if (isRed(x->right) && !isRed(x->left))
            rotateLeft(x);
        if (isRed(x->left) && x->left != 0 && isRed(x->left->left))
            rotateRight(x);
        if (isRed(x->left) && isRed(x->right))
            shiftColors(x);

        return x;
    }

    Node* find(Key key)
    {
        Node *x = root;
        while (x != 0)
        {
            if (x->key > key)
                x = x->left;
            else if (x->key < key)
                x = x->right;
            else
                break;
        }
        return x;
    }

    Value& operator [] (Key key)
    {
        Node *x = find(key);
        if (x == 0)
        {
            add(key, Value());
            x = find(key);
        }
        return x->value;
    }

    void rotateRight(Node *&x)
    {
        Node *t = x->left;
        Node *k = t->right;
        t->right = x;
        t->right->left = k;
        t->isRed = x->isRed;
        x->isRed = true;
        x = t;
    }

    void rotateLeft(Node *&x)
    {
        Node *t = x->right;
        Node *k = t->left;
        t->left = x;
        t->left->right = k;
        t->isRed = x->isRed;
        x->isRed = true;
        x = t;
    }

    void shiftColors(Node *&x)
    {
        x->left->isRed = false;
        x->right->isRed = false;
        x->isRed = true;
    }

};


int main()
{

    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w",stdout);
    #else
        //freopen(TASKNAME".in", "r", stdin);
        //freopen(TASKNAME".out", "w", stdout);
    #endif

    RedBlackBST<int, int> t; 
    //map<int, int> t;

    vector<int> test;

    srand(time(NULL));

    for(int i = 0; i<10000000; i++)
    {
        int k = rand();
        t[k] = i;
        test.pb(k);
    }

    for(int i = 0; i<test.size(); i++)
    {
        printf("%d ", t[test[i]]);
    }

    return 0;
}
