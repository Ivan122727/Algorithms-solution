/*
Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает, что все обычные символы совпадают с соответствующими из текста, а вместо символа “?” в тексте встречается произвольный символ.
Гарантируется, что сам “?” в тексте не встречается.
Время работы - O(n + m + Z), где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте.
Время: T(n, m, Z) = O(n + m + Z)
Память: M(n, m) = O(n + m)
ID: 68782454
*/
#include <iostream>
#include <vector>
#include <string>

const int alphabet = 26;  // количество символов в алфавите

struct Node
{
    std::vector<int> next;  // next[i] - вершина в которую переходим по букве i в обычном Боре
    bool isTerminal;  // является ли вершина терминальной
    int parent;  // номер вершины-родителя
    int parentCh;  // символ, по которому попадаем из родителя в нашу вершину
    int link;  // суффиксная ссылка
    std::vector<int> go;  // переходы по каждому из символов (в модифицированном Боре)
    std::vector<int> answers;  // все терминальные вершины, в которые можно попасть по суфф. ссылкам
    std::vector<int> patternNumbers;  // номера шаблонов, которым соответствует вершина
};

class Automate
{
public:
    Automate();
    void AddString(const std::string& s, const int& patternNumber);
    int Go(const int& vertex, const int& ch);
    int SuffLink(const int& vertex);
    std::vector<int> FindingTerminalVertices(const int& vertex);
    std::vector<int> GetPattern(const int& vertex);
private:
    std::vector<Node> bor;
};

Automate::Automate() 
{
    Node root;
    root.next.assign(alphabet, -1);
    root.isTerminal = false;
    root.link = 0;
    root.go.assign(alphabet, -1);
    root.parent = -1;
    bor.push_back(root);
}

void Automate::AddString(const std::string& s, const int& patternNumber)
{
    int currentVertex = 0;
    for (auto& ch : s) 
    {
        int c = (int)(ch - 'a');
        if(bor[currentVertex].next[c] == -1)
        {
            size_t borSize = bor.size();
            Node newVertex;
            newVertex.next.assign(alphabet, -1);
            newVertex.isTerminal = false;
            newVertex.go.assign(26, -1);
            newVertex.link = -1;
            newVertex.parent = currentVertex;
            newVertex.parentCh = c;
            bor.push_back(newVertex);
            bor[currentVertex].next[c] = bor.size() - 1;
        }
        currentVertex = bor[currentVertex].next[c];
    }
    bor[currentVertex].isTerminal = true;
    bor[currentVertex].patternNumbers.push_back(patternNumber);
}

int Automate::Go(const int& vertex, const int& ch)
{
    if (bor[vertex].go[ch] == -1)
    {
        if (bor[vertex].next[ch] != -1)
        {
            bor[vertex].go[ch] = bor[vertex].next[ch];
        }
        else
        {
            if (vertex == 0)
            {
                bor[vertex].go[ch] = 0;
            }
            else
            {
                bor[vertex].go[ch] = Go(SuffLink(vertex), ch);
            }
        }
    }
    return bor[vertex].go[ch];
}

int Automate::SuffLink(const int& vertex) 
{
    if (bor[vertex].link == -1) 
    {
        if (vertex == 0 || bor[vertex].parent == 0) 
        {
            bor[vertex].link = 0;
        }
        else 
        {
            bor[vertex].link = Go(SuffLink(bor[vertex].parent), bor[vertex].parentCh);
        }
    }
    return bor[vertex].link;
}

std::vector<int> Automate::FindingTerminalVertices(const int& vertex)
{
    if (bor[vertex].answers.size() > 0)
    {
        return bor[vertex].answers;
    }
    int current_vertex = vertex;
    while (current_vertex != 0) 
    {
        if (bor[current_vertex].isTerminal) 
        {
            bor[vertex].answers.push_back(current_vertex);
        }
        current_vertex = SuffLink(current_vertex);
    }
    return bor[vertex].answers;
}

std::vector<int> Automate::GetPattern(const int& vertex)
{
    if (bor[vertex].isTerminal) 
    {
        return bor[vertex].patternNumbers;
    }
    else 
    {
        return std::vector<int>(0);
    }
}

std::vector<int> GetOccurrences(const std::string& sample, const std::string& s)
{
    auto automate = new Automate;
    std::string currentStr = "";
    std::vector<int> l(0);  // вхождения шаблонов без '?' в исходном шаблоне
    std::vector<int> d(0);  // длины шаблонов без '?'
    bool flag = true;  // последний прочитанный символ - '?' ?
    for (int i = 0; i < sample.length(); i++) 
    {
        char ch = sample[i];
        if (ch != '?') 
        {
            currentStr += ch;
            if (flag)
            {
                l.push_back(i);
            }
            flag = false;
        }
        else 
        {
            if (currentStr != "")
            {
                automate->AddString(currentStr, l.size() - 1);
                d.push_back(currentStr.length());
                currentStr = "";
            }
            flag = true;
        }
    }
    automate->AddString(currentStr, l.size() - 1);
    d.push_back(currentStr.length());
    std::vector<int> countOccurrences(s.length(), 0);  // c[i] - количество возможных вхождений на i символе
    int currentVertex = 0;
    for (int i = 0; i < s.length(); i++) 
    {
        int ch = s[i] - 'a';
        currentVertex = automate->Go(currentVertex, ch);
        std::vector <int> terminalVertices = automate->FindingTerminalVertices(currentVertex); 
        // для каждой вершины из terminalVertices найдем, какому шаблону она соответствует, а затем по номеру шаблона
        // определим, на какой позиции она находится в исходном шаблоне с "?"
        for(auto& vertex : terminalVertices) 
        {
            std::vector<int> patternNumbers = automate->GetPattern(vertex);
            for (auto& patternNumber : patternNumbers) 
            {
                if (i - d[patternNumber] - l[patternNumber] + 1 >= 0) 
                {
                    countOccurrences[i - d[patternNumber] - l[patternNumber] + 1]++;
                }
            }
        }
    }
    std::vector<int> occurrences;
    for (int i = 0; i < countOccurrences.size(); i++) 
    {
        if (countOccurrences[i] == l.size() && i + sample.length() <= s.length())
        {
            occurrences.push_back(i);
        }
    }
    return occurrences;
}

int main() 
{
    std::string sample, s;
    std::cin >> sample >> s;
    std::vector<int> occurrences = GetOccurrences(sample, s);
    for (auto& occurrence : occurrences)
    {
        std::cout << occurrence << " ";
    }
    std::cout << "\n";
    return 0;
}