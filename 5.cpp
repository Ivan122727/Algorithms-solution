/*
Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.
Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n).
Время: T(n) = O(n log n)
Память: M(n) = O(n)
ID: 68797284
*/
#include <iostream>
#include <vector>
#include <algorithm>

template<class T, class additionalArr>
void Merger(int lenFirst, T* firstArr, int lenSecond, T* secondArr, bool (*f)(T&, T&, additionalArr&, int&, int&), additionalArr& order, int& n, int& nowSuffAdd)
{
	T* tempArr = new T[lenSecond];
	for (int i = 0; i < lenSecond; i++)
	{
		tempArr[i] = secondArr[i];
	}
	int i = lenFirst - 1;
	int j = lenSecond - 1;
	int end = lenFirst + lenSecond - 1;
	while (j > -1)
	{
		if (i > -1 && f(tempArr[j], firstArr[i], order, n, nowSuffAdd))
		{
			firstArr[end--] = firstArr[i--];
		}
		else
		{
			firstArr[end--] = tempArr[j--];
		}
	}
	delete[] tempArr;
}

template<class T, class additionalArr>
void MergeSort(int right, T* arr, bool (*f)(T&, T&, additionalArr&, int&, int&), additionalArr& order, int& n, int& nowSuffAdd)
{
	if (right != 1)
	{
		int mid = right / 2;
		MergeSort(mid, arr, f, order, n, nowSuffAdd);
		MergeSort(right - mid, arr + mid, f, order, n, nowSuffAdd);
		Merger(mid, arr, right - mid, arr + mid, f, order, n, nowSuffAdd);
	}
}

int GetOrder(const int& pos, std::vector<int>& order, int& n)
{
    return (pos < n) ? order[pos] : -1;
}

bool cmp(std::pair<int, int>& a, std::pair<int, int>& b, std::vector<int>& order, int& n, int& nowSuffAdd)
{
    return (a.first != b.first) ? a.first < b.first : GetOrder(a.second + nowSuffAdd, order, n) < GetOrder(b.second + nowSuffAdd, order, n);
}

std::vector<int> BuildSufArr(const std::string& s, int& n, std::vector<int>& order)
{
    int cnt[26];
    for (int i = 0; i < 26; i++)
    {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        cnt[s[i] - 'a']++;
    }
    for (int i = 1; i < 26; i++)
    {
        cnt[i] += cnt[i - 1];
    }
    std::pair<int, int>* suf = new std::pair<int, int>[n];
    for (int i = 0; i < n; i++)
    {
        order[i] = cnt[s[i] - 'a'] - 1;
        suf[i] = { order[i], i };
    }
    int nowSuffAdd = 1;
    MergeSort(n, suf, cmp, order, n, nowSuffAdd);
    while (nowSuffAdd <= n)
    {
        MergeSort(n, suf, cmp, order, n, nowSuffAdd);
        for (int i = n - 2; i >= 0; i--)
        {
            if (order[suf[i].second + nowSuffAdd] < order[suf[i + 1].second + nowSuffAdd])
            {
                suf[i].first = i;
            }
            else
            {
                suf[i].first = std::min(suf[i + 1].first, suf[i].first);
            }
        }
        for (int i = 0; i < n; i++)
        {
            order[suf[i].second] = suf[i].first;
        }
        nowSuffAdd += nowSuffAdd;
    }
    std::vector<int> answer;
    for (int i = 0; i < n; i++)
    {
        answer.push_back(suf[i].second);
    }
    nowSuffAdd = 0;
    delete[] suf;
    return answer;
}

std::vector<int> BuildLCP(const std::string& s, const std::vector<int>& sa)
{
    int n = (int)s.size(), k = 0;
    std::vector<int> lcp(n, 0);
    std::vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
    {
        rank[sa[i]] = i;
    }
    for (int i = 0; i < n; i++, k ? k-- : 0)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
        {
            k++;
        }
        lcp[rank[i]] = k;
    }
    lcp.pop_back();
    return lcp;
}

int GetCount(const std::string& s)
{
    const int N = 20000;
    std::vector<int> order(N);
    int n = (int)s.size();
    std::vector<int> sufArr = BuildSufArr(s, n, order);
    std::vector<int> lcp = BuildLCP(s, sufArr);
    int c = 0;
    for (auto& x : lcp)
    {
        c += x;
    }
    return n * (n + 1) / 2 - c;
}

int main()
{
    std::string s;
    std::cin >> s;
    std::cout << GetCount(s) << "\n";
    return 0;
}
