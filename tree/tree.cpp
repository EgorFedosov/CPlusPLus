#include <iostream>
#include <string>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *createNode(int value)
{
    return new TreeNode{value, nullptr, nullptr};
}

void add(TreeNode *&root, int value)
{
    TreeNode *current = root;
    TreeNode *prev = nullptr;
    bool find = false;

    while (current && !find)
    {
        prev = current;
        if (value == current->data)
        {
            find = true;
            cout << "Error: Duplicate key " << value << endl;
        }
        else if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (find)
        return;

    TreeNode *newNode = createNode(value);
    if (!prev)
    {
        root = newNode;
    }
    else if (value < prev->data)
    {
        prev->left = newNode;
    }
    else
    {
        prev->right = newNode;
    }
}

void View_Tree(const TreeNode *p, int level = 0)
{
    if (!p)
        return;

    View_Tree(p->right, level + 1);

    for (int i = 0; i < level * 4; ++i)
    {
        cout << " ";
    }
    cout << p->data << endl;

    View_Tree(p->left, level + 1);
}

TreeNode *Del_Info(TreeNode *root, int key)
{
    TreeNode *Del = root, *Prev_Del = nullptr, *R = nullptr, *Prev_R = nullptr; //  R - на что заменяем

    while (Del && Del->data != key)
    {
        Prev_Del = Del;
        if (Del->data > key)
            Del = Del->left;
        else
            Del = Del->right;
    }

    if (!Del)
    {
        cerr << "NOT Key!" << endl;
        return root;
    }

    if (!Del->right)
        R = Del->left;
    else if (!Del->left)
        R = Del->right;
    else
    {
        Prev_R = Del;
        R = Del->left;
        while (R->right)
        {
            Prev_R = R;
            R = R->right;
        }

        if (Prev_R == Del)
            R->right = Del->right;
        else
        {
            R->right = Del->right;
            Prev_R->right = R->left;
            R->left = Prev_R;
        }
    }

    if (Del == root)
        root = R;
    else
    {
        if (Del->data < Prev_Del->data)
            Prev_Del->left = R;
        else
            Prev_Del->right = R;
    }

    delete Del;
    return root;
}

void Del_Tree(TreeNode *t)
{
    if (t)
    {
        Del_Tree(t->left);
        Del_Tree(t->right);
        delete t;
    }
}

int main()
{

    /*Разработать

– внести информацию из массива в дерево поиска;
– сбалансировать дерево поиска;
– добавить в дерево поиска новую запись;
– по заданному ключу найти информацию и отобразить ее;
– удалить из дерева поиска информацию с заданным ключом;
– распечатать информацию прямым, обратным обходом и в порядке возрастания ключа;
- Определить количество записей в правой ветви дерева



защита
создаем дерево, лада добавляет узлы, делает  обратный обход, я должен изобразить это дерево
ИЛИ числа разыне и нужно представить их в виде дерева по алгоритму

*/

    return 0;
}