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
char buff[300];

int getCharacterInd(const char &c)
{
	return c - 'a';
}

void LSD(vector<string> &v)
{
	//assuming that all characters in v are lowercase latin letters, i.e. between 'a' and 'z'	
	//and all the strings are of the same length

	for(int k = 0; k<v[0].size(); k++)
	{
		int count[100] = {0};	
		vector<string> aux(v.size(), "");

		for (int i = 0; i < v.size(); i++)
		{
			count[getCharacterInd(v[i][k]) + 1]++;		
		}

		for (int i = 0; i < 99; i++)
		{
			count[i+1] += count[i];
		}

		for (int i = 0; i < v.size(); i++)
		{
			aux[count[getCharacterInd(v[i][k])]++] = v[i];
		}

		v = aux;
	}

}

int main()
{
	#ifdef DEBUG
		freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
	#else
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	vector<string> v;
	string s;
	int n;
	cin>>n;
	getline(cin, s);
	
	for (int i = 0; i < n; i++)
	{		
		getline(cin, s);
		v.push_back(s);
	}

	LSD(v);

	for (int i = 0; i < v.size(); i++)
		cout<<v[i]<<endl;

	return 0;
}