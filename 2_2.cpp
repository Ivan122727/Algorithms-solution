#include <iostream>
#include <queue>
#include <vector>

template<class T>
struct Node
{
    T value;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    explicit Node(const T& value) : value(value) {}
};

template <class T>
struct TreapNode
{
    T value;
    int priority;
    TreapNode<T>* left = nullptr;
    TreapNode<T>* right = nullptr;
    explicit TreapNode(const T& value, const T& priority) : value(value), priority(priority) {}
};

template <class S, class T>
class Tree
{
public:
    Tree() {}
    Tree(const Tree& other) = delete;
    Tree(Tree&& other) = delete;
    ~Tree()
    {
        if (root == nullptr)
        {
            return;
        }
        std::queue<S*> q;
        q.push(root);
        while (!q.empty())
        {
            root = q.front();
            q.pop();
            if (root->left != nullptr)
            {
                q.push(root->left);
            }
            if (root->right != nullptr)
            {
                q.push(root->right);
            }
            delete root;
        }
    }
    Tree& operator=(const Tree& other) = delete;
    Tree& operator=(Tree&& other) = delete;
    int CountTops(S* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        std::queue<S*> q;
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
    int TreeHeights(S* node)
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
    void DFS(S* node, int nodeHeight, std::vector<int>& countHeights)
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
protected:
    S* root = nullptr;
};

template<class S, class T>
class BinaryTree : public Tree<S, T>
{
public:
    void AddElem(const T& elem)
    {
        if (this->root == nullptr)
        {
            this->root = new S(elem);
            return;
        }
        S* tree = this->root;
        bool isDone = false;
        while (!isDone)
        {
            if (elem < tree->value)
            {
                if (tree->left == nullptr)
                {
                    tree->left = new S(elem);
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
                    tree->right = new S(elem);
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

template<class S, class T>
class TreapTree : public Tree<S, T>
{
public:
    std::pair<S*, S*> Split(S* root, const T& value)
    {
        if (root == nullptr)
        {
            return std::make_pair(nullptr, nullptr);
        }
        if (value < root->value)
        {
            std::pair<S*, S*> leftSplit = Split(root->left, value);
            root->left = leftSplit.second;
            return std::make_pair(leftSplit.first, root);
        }
        else
        {
            std::pair<S*, S*> rightSplit = Split(root->right, value);
            root->right = rightSplit.first;
            return std::make_pair(root, rightSplit.second);
        }
    }
    S* Merge(S* left, S* right)
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
    void AddElem(const T& elem, const T& priority)
    {
        S* node = new S(elem, priority);
        std::pair<S*, S*> split = Split(this->root, elem);
        this->root = Merge(Merge(split.first, node), split.second);
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
    BinaryTree<Node<int>, int> binTree;
    TreapTree<TreapNode<int>, int> treapTree;
    for (int i = 0; i < n; i++)
    {
        std::cin >> value >> priority;
        binTree.AddElem(value);
        treapTree.AddElem(value, priority);
    }
    std::cout << treapTree.MaxWidth() - binTree.MaxWidth() << "\n";
    return 0;
}
