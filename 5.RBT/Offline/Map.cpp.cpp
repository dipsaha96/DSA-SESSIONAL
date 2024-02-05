#include <bits/stdc++.h>
#include "color.hpp"
using namespace std;
using namespace dye;
enum color
{
    Red,
    Black
};
class Node
{
public:
    pair<int, string> data;
    Node *left;
    Node *right;
    Node *parent;
    int color;

    Node(pair<int, string> data = {int(), string()}, Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr, int color = Red)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->color = color;
    }
};

class RBT
{
    Node *root;
    Node *leaf;
    int size;

    void right_rotate(Node *node)
    {
        Node *pivot = node->left;
        node->left = pivot->right;
        if (pivot->right != leaf)
        {
            pivot->right->parent = node;
        }
        pivot->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = pivot;
        }

        else if (node == node->parent->right)
        {
            node->parent->right = pivot;
        }

        else
        {
            node->parent->left = pivot;
        }
        pivot->right = node;
        node->parent = pivot;
    }
    void left_rotate(Node *node)
    {
        Node *pivot = node->right;
        node->right = pivot->left;
        if (pivot->left != leaf)
        {
            pivot->left->parent = node;
        }
        pivot->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = pivot;
        }

        else if (node == node->parent->left)
        {
            node->parent->left = pivot;
        }

        else
        {
            node->parent->right = pivot;
        }
        pivot->left = node;
        node->parent = pivot;
    }

    
    void insertFix(Node* &root, Node *&node) {
    while (node->parent != nullptr && node->parent->color == Red) {
        Node *uncle = (node->parent == node->parent->parent->left) ? node->parent->parent->right : node->parent->parent->left;
        if (uncle != nullptr && uncle->color == Red) {
            node->parent->color = Black;
            uncle->color = Black;
            node->parent->parent->color = Red;
            node = node->parent->parent;
        } else {
            if (node->parent == node->parent->parent->left) {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = Black;
                node->parent->parent->color = Red;
                right_rotate(node->parent->parent);
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = Black;
                node->parent->parent->color = Red;
                left_rotate(node->parent->parent);
            }
        }
    }
    root->color = Black;
}

    void insert_help(pair<int, string> keys)
    {
        Node *tempnode = new Node(keys);
        tempnode->left = leaf;
        tempnode->right = leaf;
        Node *helperNode = nullptr;
        Node *rootHelper = this->root;

        while (rootHelper != leaf)
        {
            helperNode = rootHelper;
            if (tempnode->data.first == rootHelper->data.first)
            {
                rootHelper->data.second = keys.second;
                return;
            }

            else if (tempnode->data.first < rootHelper->data.first)
            {
                rootHelper = rootHelper->left;
            }

            else
            {
                rootHelper = rootHelper->right;
            }
        }

        tempnode->parent = helperNode;
        if (helperNode == nullptr)
        {
            root = tempnode;
        }

        else if (tempnode->data.first < helperNode->data.first)
        {
            helperNode->left = tempnode;
        }

        else
        {
            helperNode->right = tempnode;
        }

        if (tempnode->parent == nullptr)
        {
            tempnode->color = Black;
            return;
        }

        if (tempnode->parent->parent == nullptr)
        {
            return;
        }

        insertFix(root,tempnode);
    }

    


    Node *inorder_Succesor(Node *root)
    {
        Node *tempnode = root->right;
        while (tempnode->left != leaf)
        {
            tempnode = tempnode->left;
        }
        return tempnode;
    }
    //Node *&root,
    void RedBlackTransplant( Node *u, Node *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }

        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }

        else
        {
            u->parent->right = v;
        }

        v->parent = u->parent;
    }

    void Delete(Node *node)
    {
        Node *sibling;
        while (node != root && node->color == Black)
        {
            if (node == node->parent->left)
            {
                sibling = node->parent->right;
                if (sibling->color == Red)
                {
                    sibling->color = Black;
                    node->parent->color = Red;
                    left_rotate(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling->left->color == Black && sibling->right->color == Black)
                {
                    sibling->color = Red;
                    node = node->parent;
                }

                else
                {
                    if (sibling->right->color == Black)
                    {
                        sibling->left->color = Black;
                        sibling->color = Red;
                        right_rotate(sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = Black;
                    sibling->right->color = Black;
                    left_rotate(node->parent);
                    node = root;
                }
            }

            else
            {
                sibling = node->parent->left;
                if (sibling->color == Red)
                {
                    sibling->color = Black;
                    node->parent->color = Red;
                    right_rotate(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling->right->color == Black && sibling->left->color == Black)
                {
                    sibling->color = Red;
                    node = node->parent;
                }

                else
                {
                    if (sibling->left->color == Black)
                    {
                        sibling->right->color = Black;
                        sibling->color = Red;
                        left_rotate(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = Black;
                    sibling->left->color = Black;
                    right_rotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = Black;
    }

    // void Delete_help(Node *rootHelp, int key)
    // {
    //     Node *nodeToBedeleted = rootHelp;
    //     Node *succPrec, *succPrecChild;

    //     while (nodeToBedeleted != leaf && nodeToBedeleted->data.first != key)
    //     {
    //         if (key < nodeToBedeleted->data.first)
    //         {
    //             nodeToBedeleted = nodeToBedeleted->left;
    //         }
    //         else
    //         {
    //             nodeToBedeleted = nodeToBedeleted->right;
    //         }
    //     }

    //     if (nodeToBedeleted == leaf)
    //     {
    //         return;
    //     }

    //     int originalColorOfNodeToBedeleted = nodeToBedeleted->color;

    //     if (nodeToBedeleted->left == leaf)
    //     {
    //         succPrecChild = nodeToBedeleted->right;
    //         RedBlackTransplant(nodeToBedeleted, nodeToBedeleted->right);
    //     }
    //     else if (nodeToBedeleted->right == leaf)
    //     {
    //         succPrecChild = nodeToBedeleted->left;
    //         RedBlackTransplant(nodeToBedeleted, nodeToBedeleted->left);
    //     }
    //     else
    //     {
    //         succPrec = _(nodeToBedeleted);
    //         originalColorOfNodeToBedeleted = succPrec->color;
    //         succPrecChild = succPrec->right;

    //         if (succPrec->parent == nodeToBedeleted)
    //         {
    //             succPrecChild->parent = succPrec;
    //         }
    //         else
    //         {
    //             RedBlackTransplant(succPrec, succPrec->right);
    //             succPrec->right = nodeToBedeleted->right;
    //             succPrec->right->parent = succPrec;
    //         }

    //         RedBlackTransplant(nodeToBedeleted, succPrec);
    //         succPrec->left = nodeToBedeleted->left;
    //         succPrec->left->parent = succPrec;
    //         succPrec->color = nodeToBedeleted->color;
    //     }

    //     delete nodeToBedeleted;
    //     if (originalColorOfNodeToBedeleted == Black)
    //     {
    //         Delete(succPrecChild);
    //     }
    // }

//     void deleteFix(Node* &root, Node *&node) {
//     Node *sibling;
//     while (node != root && node->color == Black) {
//         if (node == node->parent->left) {
//             sibling = node->parent->right;
//             if (sibling->color == Red) {
//                 sibling->color = Black;
//                 node->parent->color = Red;
//                 left_rotate(node->parent);
//                 sibling = node->parent->right;
//             }
//             if (sibling->left->color == Black && sibling->right->color == Black) {
//                 sibling->color = Red;
//                 node = node->parent;
//             } else {
//                 if (sibling->right->color == Black) {
//                     sibling->left->color = Black;
//                     sibling->color = Red;
//                     right_rotate(sibling);
//                     sibling = node->parent->right;
//                 }
//                 sibling->color = node->parent->color;
//                 node->parent->color = Black;
//                 sibling->right->color = Black;
//                 left_rotate(node->parent);
//                 node = root;
//             }
//         } else {
//             sibling = node->parent->left;
//             if (sibling->color == Red) {
//                 sibling->color = Black;
//                 node->parent->color = Red;
//                 right_rotate(node->parent);
//                 sibling = node->parent->left;
//             }
//             if (sibling->right->color == Black && sibling->left->color == Black) {
//                 sibling->color = Red;
//                 node = node->parent;
//             } else {
//                 if (sibling->left->color == Black) {
//                     sibling->right->color = Black;
//                     sibling->color = Red;
//                     left_rotate(sibling);
//                     sibling = node->parent->left;
//                 }
//                 sibling->color = node->parent->color;
//                 node->parent->color = Black;
//                 sibling->left->color = Black;
//                 right_rotate(node->parent);
//                 node = root;
//             }
//         }
//     }
//     node->color = Black;
// }

void deleteHelp(Node* &root, int key) {
    Node *node = root;
    Node *succPrec, *succPrecChild;
    while (node != leaf && node->data.first != key) {
        if (key < node->data.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (node == leaf) {
        return;
    }

    int originalColor = node->color;
    Node *temp;
    if (node->left == leaf) {
        temp = node->right;
        RedBlackTransplant( node, node->right);
    } else if (node->right == leaf) {
        temp = node->left;
        RedBlackTransplant( node, node->left);
    } else {
        temp = node->right;
        while (temp->left != leaf) {
            temp = temp->left;
        }
        originalColor = temp->color;
        succPrecChild = temp->right;
        if (temp->parent == node) {
            succPrecChild->parent = temp;
        } else {
            RedBlackTransplant( temp, temp->right);
            temp->right = node->right;
            temp->right->parent = temp;
        }
        RedBlackTransplant( node, temp);
        temp->left = node->left;
        temp->left->parent = temp;
        temp->color = node->color;
    }

    if (originalColor == Black) {
        Delete(temp);
    }
    delete node;
}

    void clearHelp(Node *root)
    {
        if (root == leaf)
        {
            return;
        }
        clearHelp(root->left);
        clearHelp(root->right);
        delete root;
    }

    bool findHelp(Node *root, int key)
    {
        if (root == leaf)
        {
            return false;
        }

        if (key != root->data.first)
        {
            if (key < root->data.first)
            {
                return findHelp(root->left, key);
            }

            else if (key > root->data.first)
            {
                return findHelp(root->right, key);
            }
        }

        else if (key == root->data.first)
        {
            return true;
        }
        return false;
    }

    void inorderTraversalHelp(Node *root)
    {
        if (root == leaf)
        {
            return;
        }

        inorderTraversalHelp(root->left);
        if (root->color == Red)
        {
            cout << red(root->data.first) << " => " << red(root->data.second) << endl;
        }

        else
        {
            cout << black(root->data.first) << " => " << black(root->data.second) << endl;
        }
        inorderTraversalHelp(root->right);
    }
    
    void printRedBlackTreeHelp(Node *root)
{
    if (root == leaf)
        return;

    cout << (root->color == Red ? red(root->data.first) : black(root->data.first)) << "_" << (root->color == Red ? red(root->data.second) : black(root->data.second));

    if (root->left != leaf || root->right != leaf)
    {
        cout << "(";
        printRedBlackTreeHelp(root->left);
        cout << ",";
        printRedBlackTreeHelp(root->right);
        cout << ")";
    }
}


    Node *copyTree(const Node *srcNode, Node *parentOfCopy)
    {
        if (srcNode == leaf)
        {
            return leaf;
        }

        Node *copyNode = new Node({srcNode->data.first, srcNode->data.second});
        copyNode->color = srcNode->color;
        copyNode->parent = parentOfCopy;
        copyNode->left = copyTree(srcNode->left, copyNode);
        copyNode->right = copyTree(srcNode->right, copyNode);

        return copyNode;
    }

public:
    RBT()
    {
        leaf = new Node();
        leaf->color = Black;
        leaf->left = nullptr;
        leaf->right = nullptr;
        this->root = leaf;
        this->size = 0;
    }
    void insert(int key, string value) {
    pair<int, string> keys = {key, value};
     insert_help(keys);
     // Ensure the root node is black after insertion
    size++;
}
    void erase(int key)
    {
        deleteHelp(this->root, key);
        size--;
    }
    bool clear()
    {
        if (size == 0)
        {
            return false;
        }
        clearHelp(root);
        root = leaf;
        size = 0;
        return true;
    }

    bool find(int key)
    {
        return findHelp(root, key);
    }

    bool empty()
    {
        return size == 0;
    }
    int Size()
    {
        return size;
    }

    void inorderTraversal()
    {
        if (root == leaf)
        {
            return;
        }
        inorderTraversalHelp(root);
    }

    void printRedBlackTree()
    {
        printRedBlackTreeHelp(root);
        cout << endl;
    }
};

class Map
{

    RBT rbt;

public:
    Map()
    {
    }
    void Insert(pair<int, string> &p)
    {
        int key = p.first;
        string value = p.second;
        rbt.insert(key, value);
    }

    void Erase(int key)
    {
        rbt.erase(key);
    }

    bool Clear()
    {
        return rbt.clear();
    }

    bool Find(int key)
    {
        return rbt.find(key);
    }

    bool Empty()
    {
        return rbt.empty();
    }

    int SIZE()
    {
        return rbt.Size();
    }
    void Iteration()
    {
        rbt.inorderTraversal();
    }

    void print()
    {
        rbt.printRedBlackTree();
    }
};
int main()
{
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    Map map;
    string line, value;
    int key;

    while (cin >> line)
    {
        if (line == "I")
        {
            cin >> key >> value;
            pair<int, string> p = {key, value};
            map.Insert(p);
            map.print();
        }

        else if (line == "E")
        {
            cin >> key;
            if (!map.Find(key))
            {
                cout << key << " not found" << endl;
            }

            else
            {
                map.Erase(key);
                map.print();
            }
        }

        else if (line == "Clr")
        {
            if (map.Clear())
            {
                cout << "successful" << endl;
            }

            else
            {
                cout << "unsuccessful" << endl;
            }
        }

        else if (line == "F")
        {
            cin >> key;
            if (map.Find(key))
            {
                cout << key << " found" << endl;
            }

            else
            {
                cout << key << " not found" << endl;
            }
        }

        else if (line == "Em")
        {
            if (map.Empty())
            {
                cout << "yes" << endl;
            }

            else
            {
                cout << "no" << endl;
            }
        }

        else if (line == "S")
        {
            cout << map.SIZE() << endl;
        }

        else if (line == "Itr")
        {
            map.Iteration();
        }
    }

    fclose(stdin);
    // fclose(stdout);
    return 0;
}

