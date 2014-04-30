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

const int N = 111111;

int getCharacterInd(const char &c)
{
	return c - 'a';
}

void keyIndexedSort(string &s)
{
	//assuming that all characters in s are lowercase latin letters, i.e. between 'a' and 'z'	
	string res(s.size(), ' ');
	int count[100] = {0};	

	for (int i = 0; i < s.size(); i++)
	{
		count[getCharacterInd(s[i]) + 1]++;		
	}

	for (int i = 0; i < 99; i++)
	{
		count[i+1] += count[i];
	}

	for (int i = 0; i < s.size(); i++)
	{
		res[count[getCharacterInd(s[i])]++] = s[i];
	}

	s = res;
}

int main()
{
	#ifdef DEBUG
		//freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
	#else
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	string s;
	getline(cin, s);

	keyIndexedSort(s);

	cout<<s<<endl;

	return 0;
}