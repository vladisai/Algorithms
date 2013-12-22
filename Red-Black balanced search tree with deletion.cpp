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
    int height;

    RedBlackBST()
    {
       root = 0;
       height = 0;
    }

    void add(Key key, Value value)
    {
       root = add(root, key, value);
       if (root->isRed)
       {
           root->isRed = false;
           height++;
       }
    }

    bool isRed(Node *x)
    {
       if (x == 0)
           return false;
       else
           return x->isRed;
    }

    bool is34Node(Node *x)
    {
       if (x == 0)
           return false;

       if (x->left != 0 && x->left->isRed)
           return true;
       if (x->right != 0 && x->right->isRed)
           return true;

       return false;
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

    Node*& getSuccessor(Node *x)
    {
       x = x->right;
       while (x->left != 0)
       {
           x = x->left;
       }
       return x;
    }

    Node*& find(Key key)
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

    void shiftColorsDeletion(Node *&x)
    {
        x->left->isRed = true;
        x->right->isRed = true;
        x->isRed = false;
    }

    Node* balance(Node *x)
    {
       if (isRed(x->right))
           rotateLeft(x);

       if (isRed(x->right) && !isRed(x->left))
           rotateLeft(x);
       if (isRed(x->left) && x->left != 0 && isRed(x->left->left))
           rotateRight(x);
       if (isRed(x->left) && isRed(x->right))
           shiftColors(x);

       return x;
    }

    Node* moveRedLeft(Node *x)
    {
       shiftColorsDeletion(x);
       if (isRed(x->right->left))
       {
           rotateRight(x->right);
           rotateLeft(x);
       }
       return x;
    }

    Node* moveRedRight(Node *x)
    {
       shiftColorsDeletion(x);
       if (isRed(x->left->left))
           rotateRight(x);
       return x;
    }

    void deleteMin()
    {
        if (root == 0)
           return;

        if (!isRed(root->left) && !isRed(root->right))
           root->isRed = true;

        root = deleteMin(root);

        if (root != 0)
            root->isRed = false;
    }

    Node* deleteMin(Node *x)
    {
       if (x->left == 0)
           return x->left;

       if (!isRed(x->left) && !isRed(x->left->left))
           x = moveRedLeft(x);

       x->left = deleteMin(x->left);
       return balance(x);
    }

    void deleteMax()
    {
        if (root == 0)
           return;

        if (!isRed(root->left) && !isRed(root->right))
           root->isRed = true;

        root = deleteMax(root);

        if (root != 0)
            root->isRed = false;
    }

    Node *deleteMax(Node *x)
    {
        if (isRed(x->left))
            rotateRight(x);

        if (x->right == 0)
            return 0;

        if (!isRed(x->right) && !isRed(x->right->left))
            x = moveRedRight(x);

        x->right = deleteMax(x->right);

        return balance(x);
    }

    void erase(Key key)
    {
        if (find(key) == 0)
           return;
        root = erase(root, key);
        if (root != 0)
           root->isRed = false;
    }

    Node* erase(Node *x, Key key)
    {
       if (x->key > key)
       {
           if (!isRed(x->left) && !isRed(x->left->left))
               x = moveRedLeft(x);
           x->left = erase(x->left, key);
       }
       else
       {
           if (isRed(x->left))
               rotateRight(x);
           if (key  == x->key && x->right == 0)
               return 0;
           if (!isRed(x->right) && !isRed(x->right->left))
               x = moveRedRight(x);
           if (key == x->key)
           {
               Node *k = getSuccessor(x);
               x->value = k->value;
               x->key = k->key;
               x->right = deleteMin(x->right);
           }
           else
           {
               x->right = erase(x->right, key);
           }
       }

       return balance(x);
    }

    int getMaxHeight()
    {
       return getMaxHeight(root);
    }

    int getMaxHeight(Node *x)
    {
       if (x == 0)
           return 0;
       else
           return max(getMaxHeight(x->right), getMaxHeight(x->left))+1;
    }

    bool isRedBlackBST()
    {
       return isRedBlackBST(root) && balanced();
    }

    bool balanced()
    {
        int mx = 0, mn = INF;
        go(root, 0, mx, mn);
        printf("\n%d %d\n", mx, mn);
        return mx == mn;
    }

    void go(Node *x, int depth, int &mx, int &mn)
    {
        if (x == 0)
        {
            mx = max(mx, depth);
            mn = min(mn, depth);
            return;
        }

        if (!x->isRed)
            depth++;

        go(x->left, depth, mx, mn);
        go(x->right, depth, mx, mn);
    }

    bool isRedBlackBST(Node *x)
    {
        if (x == 0)
            return true;

       if (isRed(x->right))
           return false;

       if (isRed(x) && isRed(x->left))
           return false;

       return isRedBlackBST(x->left) && isRedBlackBST(x->right);
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

   RedBlackBST<int, int> t;
   //map<int, int> t;

   vector<int> test;

   int n = 2000000;

   for(int i = 0; i<n; i++)
   {
       int k = rand();
       t[k] = i;
       test.pb(k);
       if (i % 3 == 0)
       {
           t.erase(test[rand()%test.size()]);
       }
   }

   printf("%d, should be around %d\n", t.getMaxHeight(), static_cast<int>(2*ceil(log2(n))));

   if (t.isRedBlackBST())
   {
       printf("OK");
   }
   else
   {
       printf("THAT'S AIN'T NO TREE, MAN");
   }

   return 0;
}
