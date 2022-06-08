/*
Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z.
Время: T(n) = O(n)
Память: M(n) = O(n)
ID: 68779417
*/
#include <iostream>
#include <vector>
#include <string>

std::string BuildString(const std::vector<int>& p)
{
    if (p.size() == 0) 
    {
        return "";
    }
    std::string ans = "a";
    for (int i = 1; i < p.size(); i++) 
    {
        if (p[i] != 0) 
        {
            ans += ans[p[i] - 1];
        }
        else 
        {
            std::vector<bool> alphabet(26, false);
            int k = p[i - 1];
            while (k > 0) 
            {
                alphabet[ans[k] - 'a'] = true;
                k = p[k - 1];
            }
            char c = 'b';
            while (alphabet[c - 'a']) 
            {
                c++;
            }
            ans += c;
        }
    }
    return ans;
}

int main() 
{
    int num;
    std::vector<int> p;
    while(std::cin >> num) 
    {
        p.push_back(num);
    }
    std::cout << BuildString(p) << "\n";
    return 0;
}