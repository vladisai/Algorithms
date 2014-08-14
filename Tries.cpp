#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>

#define mp make_pair
#define pb push_back
#define F first
#define S second
#define INF (1<<30)

using namespace std;

const int N = 10;

class Trie
{
public:

	Trie()
	{
		root = new Node();
	}

	void add(string key, int value)
	{
		add(root, key, value, 0);
	}

	int get(string key)
	{
		return get(root, key, 0);
	}

	bool isPresent(string key)
	{
		return isPresent(root, key, 0);
	}

	void remove(const string &key)
	{
		remove(root, key, 0);
	}

private:

	struct Node
	{
		Node *next[300];
		bool isNull;
		int value;

		Node ()
		{
			fill(next, next + 300, (Node*)0);
			isNull = true;
			value = 0;
		}

		bool isEmpty()
		{
			for(int i = 0; i < 300; i++)
				if (next[i] != 0)
					return false;
			return true;
		}

		Node *& operator [] (const int &ind)
		{
			return next[ind];
		}

	};

	Node *root;

	void add(Node *&x, const string &key, int value, int ind)
	{
		if (ind == key.size())
		{
			x->value = value;
			return;
		}

		if (x->next[key[ind]] == 0)
			x->next[key[ind]] = new Node();

		add(x->next[key[ind]], key, value, ind + 1);
	}	

	int get(Node *&x, const string &key, int ind)
	{
		if (key.size() == ind)
			return x->value;
		if (x->next[key[ind]] == 0)
			return 0;
		return get(x->next[key[ind]], key, ind + 1);
	}


	bool isPresent(Node *&x, const string &key, int ind)
	{
		if (key.size() == ind)
			return true;
		if (x->next[key[ind]] == 0)
			return false;
		return isPresent(x->next[key[ind]], key, ind + 1);
	}

	void remove(Node *&x, const string &key, int ind)
	{

		if (ind == key.size())
		{
			x = 0;
			return;
		}

		if ((*x)[key[ind]] == 0)
			return;

		remove((*x)[key[ind]], key, ind + 1);

		if (x->isEmpty() && root != x)
			x = 0;
	}

};

int main()
{
	#ifdef DEBUG
		freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
	#else
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	Trie t;
	t.add("YO", 10);
	t.add("YOU", 21);
	cout<<t.get("YO")<<endl;
	t.remove("YO");
	cout<<t.get("YO");

	return 0;
}