/*
ID: 62883537
Условие:
Дано число N < 10^6 и последовательность пар целых чисел из [-231, 231] длиной N. 
Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi). 
Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции: При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). 
Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi. Равные ключи добавляйте в правое поддерево.
Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. 
Вывести их разницу. 
Разница может быть отрицательна.
Асимптотика: T(n) = O(n log n)
Память: M(n) = O(n)
*/
#include <iostream>
#include <queue>
#include <vector>

template<class T>
struct Node
{
    T value;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    explicit Node(const T& value) : value(value) {};
};

template <class T>
struct TreapNode
{
    T value;
    int priority;
    TreapNode<T>* left = nullptr;
    TreapNode<T>* right = nullptr;
    explicit TreapNode(const T& value, const T& priority = rand()) : value(value), priority(priority) {};
};

template<class T>
class Tree
{
public:
    Tree() {};
    ~Tree() { CleanTree(root); };
    int CountTops(T* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        std::queue<T*> q;
        q.push(node);
        int count = 1;
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (node->left != nullptr)
            {
                count++;
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                count++;
                q.push(node->right);
            }
        }
        return count;
    }
    int TreeHeights(T* node)
    {
        int height = 0;
        int left = 0;
        int right = 0;
        if (node != nullptr)
        {
            left = TreeHeights(node->left);
            right = TreeHeights(node->right);
            height = (left > right ? left : right) + 1;
        }
        return height;
    }
    void DFS(T* node, int nodeHeight, std::vector<int>& countHeights)
    {
        if (node == nullptr)
        {
            return;
        }
        ++countHeights[nodeHeight];
        DFS(node->left, nodeHeight + 1, countHeights);
        DFS(node->right, nodeHeight + 1, countHeights);
    }
    int MaxWidth()
    {
        int height = TreeHeights(root);
        std::vector<int> countHeights(height);
        DFS(root, 0, countHeights);
        int ans = 0;
        for (int i = 0; i < height; ++i)
        {
            ans = std::max(countHeights[i], ans);
        }
        return ans;
    }
    void CleanTree(T* node)
    {
        if (node == nullptr)
        {
            return;
        }
        std::queue<T*> q;
        q.push(node);
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (node->left != nullptr)
            {
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                q.push(node->right);
            }
            delete node;
        }
    }
    T* root = nullptr;
};

template<class T>
class BinnaryTree : public Tree<T>
{
public:
    void AddElem(T* elem)
    {
        if (this->root == nullptr)
        {
            this->root = elem;
            return;
        }
        T* tree = this->root;
        bool isDone = false;
        while (!isDone)
        {
            if (elem->value < tree->value)
            {
                if (tree->left == nullptr)
                {
                    tree->left = elem;
                    isDone = true;
                }
                else
                {
                    tree = tree->left;
                }
            }
            else
            {
                if (tree->right == nullptr)
                {
                    tree->right = elem;
                    isDone = true;
                }
                else
                {
                    tree = tree->right;
                }
            }
        }
    }
};

template<class T>
class TreapTree : public Tree<T>
{
public:
    std::pair<T*, T*> Split(T* root, T* elem)
    {
        if (root == nullptr)
        {
            return std::make_pair(nullptr, nullptr);
        }
        if (elem->value < root->value)
        {
            std::pair<T*, T*> leftSplit = Split(root->left, elem);
            root->left = leftSplit.second;
            return std::make_pair(leftSplit.first, root);
        }
        else
        {
            std::pair<T*, T*> rightSplit = Split(root->right, elem);
            root->right = rightSplit.first;
            return std::make_pair(root, rightSplit.second);
        }
    }
    T* Merge(T* left, T* right)
    {
        if (left == nullptr || right == nullptr)
        {
            return left == nullptr ? right : left;
        }
        if (right->priority < left->priority)
        {
            left->right = Merge(left->right, right);
            return left;
        }
        else
        {
            right->left = Merge(left, right->left);
            return right;
        }
    }
    void AddElem(T* elem)
    {
        std::pair<T*, T*> split = Split(this->root, elem);
        this->root = Merge(Merge(split.first, elem), split.second);
        return;
    }
};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, value, priority;
    std::cin >> n;
    BinnaryTree<Node<int>> binTree;
    TreapTree<TreapNode<int>> treapTree;
    for (int i = 0; i < n; i++)
    {
        std::cin >> value >> priority;
        binTree.AddElem(new Node<int>(value));
        treapTree.AddElem(new TreapNode<int>(value, priority));
    }
    std::cout << treapTree.MaxWidth() - binTree.MaxWidth() << "\n";
    return 0;
}
