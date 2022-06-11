/*
Заданы две строки s, t и целое число k.
Рассмотрим множество всех таких непустых строк, которые встречаются как подстроки в s и t одновременно. 
Найдите k-ую в лексикографическом порядке строку из этого множества.
Время: T(s, t) = O(s + t)
Память: M(s, t) = O(s + t)
ID: 68818555	
*/
#include <iostream>
#include <map>
#include <memory>
#include <vector>
 
class SuffixTree
{
private:
    struct Node
    {
        std::map<char, std::unique_ptr<Node>> edges;
        int st, end;
        Node* suffLink;
        bool beginInSecondString = false;
        bool beginInFirstString = false;
        Node* GetNext(const char& c)
        {
            return edges.find(c)->second.get();
        }
        bool HasTransfer(const char& c)
        {
            return (edges.find(c) != edges.end());
        }
        void InsertEdge(const char& c, Node* vertex)
        {
            auto it = edges.find(c);
            if (it != edges.end())
            {
                it->second.release();
                it->second.reset(vertex);
            }
            else
            {
                edges.emplace_hint(it, c, vertex);
            }
        }
        Node(const int& st, const int& end) : suffLink(nullptr), st(st), end(end) {};
    };
    struct ActivePoint 
    {
        Node* node;
        int edge;
        int len;
    };
    std::unique_ptr<Node> root;
    ActivePoint activePoint;
    int remain;
    size_t treeSize;
    std::string s;
    void CreateSuffixLink(Node*& from, Node* to);
    bool GoingEdge(Node* currentNode);
    bool FindKSubstringHelper(Node* node, long long& k, std::vector<char>& pathToResult) const;
    void MoveActivePoint(const int& pos);
    void Divide(Node* next, const int& posOnEdge, const int& pos, Node*& lastCreatedNode);
public:
    explicit SuffixTree(std::string str);
    void ProlongWithLetter(const int& pos);
    std::string FindKSubstring(long long k) const;
    void DFS(Node* node, const int& firstStringSize);
    Node* GetRoot() const 
    { 
        return root.get(); 
    }
};
 
SuffixTree::SuffixTree(std::string str) : root(nullptr), activePoint({ nullptr, 0, 0 }), s(std::move(str)), remain(0), treeSize(1) 
{
    root = std::make_unique<Node>(-1, 0);
    activePoint.node = root.get();
    for (int pos = 0; pos < s.size(); pos++)
    {
        ProlongWithLetter(pos);
    }
}
 
bool SuffixTree::GoingEdge(SuffixTree::Node* currentNode)
{
    int pathLen = currentNode->end - currentNode->st + 1;
    if (activePoint.len >= pathLen)
    {
        activePoint.node = currentNode;
        activePoint.len -= pathLen;
        activePoint.edge += pathLen;
        return true;
    }
    else
    {
        return false;
    }
}
 
void SuffixTree::CreateSuffixLink(SuffixTree::Node*& from, SuffixTree::Node* to) 
{
    if (from != nullptr) 
    {
        from->suffLink = to;
        from = nullptr;
    }
}
 
 
void SuffixTree::Divide(Node* next, const int& posOnPath, const int& pos, Node*& lastCreatedNode) 
{
    Node* newInternalNode = new Node(next->st, posOnPath - 1);
    activePoint.node->InsertEdge(s[next->st], newInternalNode);
    Node* newLeaf = new Node(pos, s.size() - 1);
    newInternalNode->InsertEdge(s[pos], newLeaf);
    newInternalNode->InsertEdge(s[next->st + activePoint.len], next);
    next->st += activePoint.len;
    CreateSuffixLink(lastCreatedNode, newInternalNode);
    lastCreatedNode = newInternalNode;
    treeSize += 2;
}
 
void SuffixTree::MoveActivePoint(const int& pos) 
{
    if (activePoint.node == root.get() && activePoint.len > 0) 
    {
        activePoint.len--;
        activePoint.edge = pos - remain + 1;
    }
    else 
    {
        activePoint.node = (activePoint.node->suffLink == nullptr) ? root.get() : activePoint.node->suffLink;
    }
}
 
void SuffixTree::ProlongWithLetter(const int& pos) 
{
    Node* lastCreatedNode = nullptr;
    for (remain++; remain > 0;) 
    {
        if (activePoint.len == 0)
        {
            activePoint.edge = pos;
        }
        if (!activePoint.node->HasTransfer(s[activePoint.edge])) {
            treeSize++;
            Node* newLeaf = new Node(pos, s.size() - 1);
            activePoint.node->InsertEdge(s[activePoint.edge], newLeaf);
            CreateSuffixLink(lastCreatedNode, activePoint.node);
        }
        else 
        {
            Node* next = activePoint.node->GetNext(s[activePoint.edge]);
            if (GoingEdge(next)) 
            {
                continue;
            }
            int posOnEdge = next->st + activePoint.len;
            if (s[posOnEdge] == s[pos])
            {
                activePoint.len++;
                if (activePoint.node != root.get())
                {
                    CreateSuffixLink(lastCreatedNode, activePoint.node);
                }
                break;
            }
            else
            {
                Divide(next, posOnEdge, pos, lastCreatedNode);
            }
        }
        remain--;
        MoveActivePoint(pos);
    }
}
 
void SuffixTree::DFS(Node* node, const int& firstStringSize) 
{
    if (node->edges.empty())
    {
        if (node->st <= firstStringSize)
        {
            node->beginInFirstString = true;
        }
        else 
        {
            node->beginInSecondString = true;
        }
    }
    for (const auto& vertexEdge : node->edges) 
    {
        DFS(vertexEdge.second.get(), firstStringSize);
        node->beginInFirstString |= vertexEdge.second->beginInFirstString;
        node->beginInSecondString |= vertexEdge.second->beginInSecondString;
    }
}
 
bool SuffixTree::FindKSubstringHelper(SuffixTree::Node* node, long long& k, std::vector<char>& pathToResult) const 
{
    if (node->beginInFirstString && node->beginInSecondString) 
    {
        int pathLen = node->end - node->st + 1;
        if (pathLen < k) 
        {
            k -= pathLen;
        }
        else 
        {
            return true;
        }
    }
    else 
    {
        return false;
    }
    for (auto& vertexEdge : node->edges) 
    {
        if (FindKSubstringHelper(vertexEdge.second.get(), k, pathToResult)) 
        {
            pathToResult.push_back(vertexEdge.first);
            return true;
        }
    }
    return false;
}
 
std::string SuffixTree::FindKSubstring(long long k) const
{
    std::vector<char> pathToResult;
    for (const auto& vertexEdge : root->edges) 
    {
        if (FindKSubstringHelper(vertexEdge.second.get(), k, pathToResult))
        {
            pathToResult.push_back(vertexEdge.first);
            break;
        }
    }
    std::string result;
    Node* currentNode = root.get();
    for (auto it = pathToResult.rbegin(); it != pathToResult.rend(); it++) 
    {
        currentNode = currentNode->GetNext(*it);
        long long edgeLen = currentNode->end - currentNode->st + 1;
        if (it == pathToResult.rend() - 1)
        {
            edgeLen = k;
            k = 0;
        }
        for (int i = 0; i < edgeLen; ++i) 
        {
            result.push_back(s[currentNode->st + i]);
        }
    }
    return (k > 0) ? "-1" : result;
}
 
std::string KCommonSubstring(const std::string& s, const std::string& t, long long k) 
{
    SuffixTree suffTree(s + "#" + t + "$");
    suffTree.DFS(suffTree.GetRoot(), s.size());
    return suffTree.FindKSubstring(k);
}
 
int main()
{
    std::string s, t;
    long long k;
    std::cin >> s >> t >> k;
    std::cout << KCommonSubstring(s, t, k) << "\n";
    return 0;
}
