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

vector<string> aux;

void MSD(vector<string> &v, int b, int e, int k)
{
	//assuming that all characters in v are lowercase latin letters, i.e. between 'a' and 'z'	
	//and all the strings are of the same length

	if (b >= e)
		return;
	if (k >= v[0].size())
		return;

	int count[100] = {0};	

	for (int i = b; i <= e; i++)
	{
		count[getCharacterInd(v[i][k]) + 1]++;		
	}

	for (int i = 0; i < 99; i++)
	{
		count[i+1] += count[i];
	}

	for (int i = b; i <= e; i++)
	{
		aux[b + count[getCharacterInd(v[i][k])]++] = v[i];
	}

	for (int i = b; i <= e; i++)
		v[i] = aux[i];
	
	for (int i = 0; i < 99; i++)
	{
		if (i == 0)
			MSD(v, b, b + count[i] - 1, k + 1);
		else
			MSD(v, b + count[i-1], b + count[i] - 1, k + 1);
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

	aux = v;

	MSD(v, 0, v.size() - 1, 0);

	for (int i = 0; i < v.size(); i++)
		cout<<v[i]<<endl;

	return 0;
}