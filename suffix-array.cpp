#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define mp make_pair
#define pb push_back
#define F first
#define S second
#define INF (1<<30)

using namespace std;
const int N = 1111;

ostream &operator << (ostream &os, const vector<int> &v)
{
	for(auto a : v)
	{
		os<<a<<" ";		
	}
	return os;
}

int &getPrev(vector<int> &a, int ind, int i)
{
	ind -= (1<<i);
	ind += 5 * a.size();
	ind %= a.size();
	return a[ind];
}

vector<int> getSuffixArray(string s)
{
	s += char(0);
	vector<int> a(s.size()), b(s.size()), inds(s.size()), ord(s.size());
	vector<int> nInd(s.size());
	vector<int> nb(s.size());

	int count[N] = {0};
	
	for(int i = 0; i < s.size(); i++)
		count[s[i] + 1]++;

	for(int i = 0; i < N - 1; i++)
		count[i+1] += count[i];
	
	for(int i = 0; i < s.size(); i++)
	{		
		a[i] = count[s[i]]++;		
		b[i] = s[i];
	}

	for(int i = 0; (1<<i) < s.size(); i++)
	{
		fill(count, count + N, 0);	

		for(int i = 0; i < a.size(); i++)
			count[a[i] + 1]++;

		for(int i = 0; i < N - 1; i++)
			count[i + 1] += count[i];

		for(int i = 0; i < a.size(); i++)
		{
			ord[i] = count[a[i]]++;
			inds[ord[i]] = i;
		}

		fill(count, count + N, 0);

		for(int j = 0; j < inds.size(); j++)		
			count[getPrev(b, inds[j], i) + 1]++;		

		for(int i = 1; i < N; i++)
			count[i] += count[i-1];

		for(int j = 0; j < inds.size(); j++)
		{
			ord[inds[j]] = count[getPrev(b, inds[j], i)]++;
			nInd[ord[inds[j]]] = inds[j];
		}

		int curClass = 0;
		nb[nInd[0]] = 0;
		for(int j = 1; j < nInd.size(); j++)
		{
			if (b[nInd[j]] != b[nInd[j-1]] || getPrev(b, nInd[j], i) != getPrev(b, nInd[j-1], i))
				curClass++;

			getPrev(nb, nInd[j], i) = curClass;
		}

		for(int j = 0; j < ord.size(); j++)
		{
			getPrev(a, j, i) = ord[j];
		}

		b = nb;		

	}

	return a;
}

vector<int> getSuffixArrayNaive(string s)
{
	vector<pair<string, int>> v;

	for(int i = 0; i<s.size(); i++)
		v.pb(mp(s.substr(i), i));

	sort(v.begin(), v.end());

	vector<int> res(s.size());

	for(int i = 0; i<v.size(); i++)
	{
		res[v[i].S] = i + 1;
	}

	return res;
}

int main()
{
	freopen("input.txt", "r", stdin);

	string s;

	getline(cin, s);

	vector<int> res = getSuffixArray(s);
	vector<int> naive = getSuffixArrayNaive(s);

	cout<<res<<endl<<naive;

	return 0;
}
