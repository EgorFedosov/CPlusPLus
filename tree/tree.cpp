#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

struct TreeNode
{
    int data;
    char info[100];
    TreeNode *left;
    TreeNode *right;
};

TreeNode *createNode(int value, const char *info)
{
    TreeNode *node = new TreeNode;
    node->data = value;
    strncpy(node->info, info, 99);
    node->info[99] = '\0';
    node->left = node->right = nullptr;
    return node;
}
void add(TreeNode *&root, int value, const char *info)
{
    if (info == nullptr || strlen(info) == 0 || strlen(info) >= 100)
    {
        cout << "Error: Invalid info for key " << value << endl;
        return;
    }

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

    TreeNode *newNode = createNode(value, info);
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
    TreeNode *Del = root, *Prev_Del = nullptr, *R = nullptr, *Prev_R = nullptr;

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

void TreeFromArray(TreeNode *&root, const int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        char info[100] = "def";
        add(root, arr[i], info);
    }
}

int Search_Info(TreeNode *root, int key)
{
    TreeNode *Find = root, *Prev_Find = nullptr;

    while (Find && Find->data != key)
    {
        Prev_Find = Find;
        if (Find->data > key)
            Find = Find->left;
        else
            Find = Find->right;
    }

    if (!Find)
    {
        cout << "NOT find key!" << endl;
        return 0;
    }
    else
    {
        cout << "Find key: " << Find->data << ", info: " << Find->info << endl;
        return Find->data;
    }
}

void DirectPrint(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    stack<TreeNode *> s;
    s.push(root);

    while (s.empty() == false)
    {
        TreeNode *temp = s.top();
        s.pop();
        cout << temp->data << " ";

        if (temp->right)
            s.push(temp->right);
        if (temp->left)
            s.push(temp->left);
    }
}

void ReversePrint(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    ReversePrint(root->left);
    ReversePrint(root->right);
    cout << root->data << " ";
}

void SymmetricalPrint(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    SymmetricalPrint(root->left);
    cout << root->data << " ";
    SymmetricalPrint(root->right);
}

int countRightBranch(TreeNode *root)
{
    int count = 0;

    while (root && root->right)
    {
        count++;
        root = root->right;
    }

    return count;
}

int countNodes(TreeNode *root)
{
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void fillArray(TreeNode *root, int *arr, int &index)
{
    if (!root)
        return;
    fillArray(root->left, arr, index);
    arr[index++] = root->data;
    fillArray(root->right, arr, index);
}

TreeNode *buildBalancedTree(int *arr, int start, int end)
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    char info[100];
    snprintf(info, sizeof(info), "info%d", arr[mid]);
    TreeNode *node = createNode(arr[mid], info);

    node->left = buildBalancedTree(arr, start, mid - 1);
    node->right = buildBalancedTree(arr, mid + 1, end);

    return node;
}

void balanceTree(TreeNode *&root)
{
    int n = countNodes(root);
    if (n == 0)
        return;

    int *arr = new int[n];
    int index = 0;

    fillArray(root, arr, index);
    Del_Tree(root);

    root = buildBalancedTree(arr, 0, n - 1);

    delete[] arr;
}

void sumAndCount(TreeNode *root, int &sum, int &count)
{
    if (!root)
        return;
    sum += root->data;
    count++;
    sumAndCount(root->left, sum, count);
    sumAndCount(root->right, sum, count);
}

void find(TreeNode *root, double average, TreeNode *&temp)
{
    if (!root)
        return;

    if (!temp || abs(root->data - average) < abs(temp->data - average))
        temp = root;

    if (average < root->data)
        find(root->left, average, temp);

    else if (average > root->data)
        find(root->right, average, temp);
}

int main()
{
    TreeNode *root = nullptr;
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add node\n";
        cout << "2. Delete node\n";
        cout << "3. Search for a key\n";
        cout << "4. Display tree\n";
        cout << "5. Direct traversal (pre-order)\n";
        cout << "6. Reverse traversal (post-order)\n";
        cout << "7. Symmetrical traversal (in-order)\n";
        cout << "8. Count nodes in right branch\n";
        cout << "9. Balance the tree\n";
        cout << "10. Delete the  tree\n";
        cout << "11. Create tree from array\n";
        cout << "12. Find average key and temp info\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int val;
            char info[100];
            cout << "Enter value to add: ";
            cin >> val;
            cout << "Enter info for the node: ";
            cin.ignore();
            cin.getline(info, 100);
            add(root, val, info);
            break;
        }
        case 2:
        {
            int key;
            cout << "Enter key to delete: ";
            cin >> key;
            root = Del_Info(root, key);
            break;
        }
        case 3:
        {
            int key;
            cout << "Enter key to search: ";
            cin >> key;
            Search_Info(root, key);
            break;
        }
        case 4:
        {
            if (root == nullptr)
            {
                cout << "Tree is empty." << endl;
            }
            else
            {
                View_Tree(root);
            }
            break;
        }
        case 5:
        {
            cout << "Direct traversal: ";
            DirectPrint(root);
            cout << endl;
            break;
        }
        case 6:
        {
            cout << "Reverse traversal: ";
            ReversePrint(root);
            cout << endl;
            break;
        }
        case 7:
        {
            cout << "Symmetrical traversal: ";
            SymmetricalPrint(root);
            cout << endl;
            break;
        }
        case 8:
        {
            cout << "Number of nodes in right branch: " << countRightBranch(root) << endl;
            break;
        }
        case 9:
        {
            balanceTree(root);
            cout << "Tree balanced." << endl;
            break;
        }
        case 10:
        {
            Del_Tree(root);
            root = nullptr;
            cout << "Tree deleted." << endl;
            break;
        }
        case 11:
        {
            cout << "Enter size array: ";
            int size;
            cin >> size;

            if (size <= 0)
            {
                cout << "Invalid size!" << endl;
                break;
            }

            int arr[size];
            for (int i = 0; i < size; i++)
            {
                cout << "Enter element" << i << ":";
                int el;
                cin >> el;
                arr[i] = el;
            }

            TreeFromArray(root, arr, size);
            cout << "Tree created from array." << endl;
            break;
        }

        case 12:
        {
            int sum = 0, count = 0;
            sumAndCount(root, sum, count);

            if (count == 0)
            {
                cout << "Tree is empty.\n";
                break;
            }

            double average = sum / count;
            TreeNode *temp = nullptr;
            find(root, average, temp);

            cout << "Average key value: " << average << endl;
            cout << "temp key: " << temp->data << ", Info: " << temp->info << endl;
            break;
        }

        case 0:
        {
            cout << "Exiting..." << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Try again." << endl;
            break;
        }
        }
    } while (choice != 0);

    Del_Tree(root);

    return 0;
}
