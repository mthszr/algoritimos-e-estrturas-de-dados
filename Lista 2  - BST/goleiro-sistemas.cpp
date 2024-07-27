#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Node
{
    int id;
    int wei;
    int rnk;
    Node *left;
    Node *right;
    int height;
    int depth;

    Node(int id) : id(id), wei(0), rnk(0), left(nullptr), right(nullptr), height(1), depth(0) {}
};

class AVLTree
{
private:
    Node *root;
    int total_bytes;

    int height(Node *node)
    {
        return node ? node->height : 0;
    }

    int balanceFactor(Node *node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        y->rnk = calculateRnk(y);
        x->rnk = calculateRnk(x);

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        x->rnk = calculateRnk(x);
        y->rnk = calculateRnk(y);

        return y;
    }

    Node *insert(Node *node, int id, int wei)
    {
        if (!node)
        {
            Node *newNode = new Node(id);
            newNode->wei = wei;
            total_bytes += wei;
            return newNode;
        }

        if (id < node->id)
        {
            node->left = insert(node->left, id, wei);
        }
        else if (id > node->id)
        {
            node->right = insert(node->right, id, wei);
        }
        else
        {
            node->wei += wei;
            total_bytes += wei;
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && id < node->left->id)
        {
            return rightRotate(node);
        }

        if (balance < -1 && id > node->right->id)
        {
            return leftRotate(node);
        }

        if (balance > 1 && id > node->left->id)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && id < node->right->id)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        node->rnk = calculateRnk(node);

        return node;
    }

    int calculateRnk(Node *node)
    {
        if (!node)
            return 0;
        int leftRnk = node->left ? node->left->wei : 0;
        int rightRnk = node->right ? node->right->rnk : 0;
        return leftRnk + rightRnk;
    }

    Node *find(Node *node, int id)
    {
        if (!node || node->id == id)
            return node;
        if (id < node->id)
            return find(node->left, id);
        return find(node->right, id);
    }

    int queryRnk(Node *node, int id)
    {
        if (!node)
            return 0;
        if (id <= node->id)
            return queryRnk(node->left, id);
        return node->wei + queryRnk(node->left, id) + queryRnk(node->right, id);
    }

    void getWeiAndDepth(Node *node, int id, int depth, int &wei, int &d)
    {
        if (!node)
        {
            wei = 0;
            d = -1;
            return;
        }
        if (node->id == id)
        {
            wei = node->wei;
            d = depth;
            return;
        }
        else if (id < node->id)
        {
            getWeiAndDepth(node->left, id, depth + 1, wei, d);
        }
        else
        {
            getWeiAndDepth(node->right, id, depth + 1, wei, d);
        }
    }

public:
    AVLTree() : root(nullptr), total_bytes(0) {}

    void add(int id, int wei)
    {
        root = insert(root, id, wei);
        cout << total_bytes << endl;
    }

    void weiQuery(int id)
    {
        int wei, depth;
        getWeiAndDepth(root, id, 0, wei, depth);
        cout << wei << " " << depth << endl;
    }

    void rnkQuery(int id)
    {
        cout << queryRnk(root, id) << endl;
    }
};

int main()
{
    AVLTree tree;
    string command;

    while (getline(cin, command))
    {
        if (command == "END")
            break;

        istringstream iss(command);
        string op;
        int id, wei;

        iss >> op;
        if (op == "ADD")
        {
            iss >> id >> wei;
            tree.add(id, wei);
        }
        else if (op == "WEI")
        {
            iss >> id;
            tree.weiQuery(id);
        }
        else if (op == "RNK")
        {
            iss >> id;
            tree.rnkQuery(id);
        }
    }

    return 0;
}