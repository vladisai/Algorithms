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

const int N = 511111;

template<class Key, class Value>
class BSearchTree
{
    public:
        class Node;

        class Node
        {
        public:
            Node *left, *right;
            Key key;
            Value value;

            Node(Key key, Value value)
            {
                this->key = key;
                this->value = value;
                left = NULL;
                right = NULL;
            }
        };

        Node *root;
        BSearchTree()
        {
            root = NULL;
        }

        void add(Key key, Value value)
        {
            root = add(key, value, root);
        }

        Node* add(Key key, Value value, Node* x)
        {
            if (x == NULL)
                return new Node(key, value);
            if (key < x->key)
                x->left = add(key, value, x->left);
            else if (key > x->key)
                x->right = add(key, value, x->right);
            else
                x->key = key;
            return x;
        }

        Value get(Key k)
        {
            Node *x = root;
            while (x != NULL)
            {
                if (x->key > k)
                    x = x->left;
                else if (x->key < k)
                    x = x->right;
                else if (x->key == k)
                    return x->value;
            }
        }

        Node* find(Key k)
        {
            Node *x = root;
            while (x != NULL && x->key != k)
            {
                if (k < x->key)
                    x = x->left;
                else if (k > x->key)
                    x = x->right;
            }
            return x;
        }

		void erase(Key k)
		{
			root = erase(k, root);
		}

        Node* erase(Key k, Node *x)
        {
            if (x == NULL)
				return x;
			if (k > x->key)
				x->right = erase(k, x->right);
			else if (k < x->key)
				x->left = erase(k, x->left);
			else
			{
				if (x->right == NULL)
					return x->left;

				Node *mn = minNode(x->right);

				x->key = mn->key;
				x->value = mn->value;

				eraseMin(x->right);
			}

			return x;
        }

        Node* eraseMin(Node *n)
        {
            if (n->left == 0)
                return n->right;
            else
                return eraseMin(n->left);
        }


        Node* minNode(Node *x)
        {
            while (x->left != 0)
            {
                x = x->left;
            }
            return x;
        }

        Value& operator [] (Key k)
        {
            Node *x = find(k);
            if (x == NULL)
            {
                add(k, Value());
                x = find(k);
            }
            return x->value;
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

    BSearchTree<string, int> bs;

    bs["life"] = 100;
    bs["magicka"] = 15;


    return 0;

}

