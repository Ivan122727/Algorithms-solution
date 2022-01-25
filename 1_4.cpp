/*
ID: 62797166
Условие:
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).
Асиптотика: T(n) = O(n log n)
Память: M(n) = O(n)
*/
#include <iostream>
#include <queue>
#include <string>

template<class T>
struct Node
{
	T value;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	explicit Node(const T& value) : value(value) {};
};

template<class T>
class Tree
{
public:
    Tree() {};
    ~Tree() { CleanTree(root); };
    std::string BFS()
    {
        std::string answer = "";
        std::queue<Node<T>*> q;
        if (root == nullptr)
        {
            return answer;
        }
        Node<T>* node = root;
        q.push(node);
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            answer += std::to_string(node->value) + " ";
            if (node->left != nullptr)
            {
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }
        return answer;
    }
    void AddElem(T elem)
    {
        if (root == nullptr)
        {
            root = new Node<T>(elem);
            return;
        }
        Node<T>* tree = root;
        bool isDone = false;
        while (!isDone)
        {
            if (elem < tree->value)
            {
                if (tree->left == nullptr)
                {
                    tree->left = new Node<T>(elem);
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
                    tree->right = new Node<T>(elem);
                    isDone = true;
                }
                else
                {
                    tree = tree->right;
                }
            }
        }
    }
    void CleanTree(Node<T>* node)
    {
        if (node == nullptr)
        {
            return;
        }
        std::queue<Node<T>*> q;
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
private:
    Node<T>* root = nullptr;
};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    Tree<int> tree;
    int n, elem;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> elem;
        tree.AddElem(elem);
    }
    std::cout << tree.BFS() << "\n";
    return 0;
}
