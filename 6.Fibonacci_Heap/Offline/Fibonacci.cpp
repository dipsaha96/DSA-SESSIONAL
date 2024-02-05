#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    node *parent;
    node *child;
    node *left;
    node *right;
    int key;
    int value;
    int degree;
    bool mark;
    char found;

    node(int key = 0, int value = 0, node *parent = NULL, node *child = NULL, node *left = NULL, node *right = NULL, int degree = 0, bool mark = false)
    {
        this->parent = parent;
        this->child = child;
        this->left = left;
        this->right = right;
        this->degree = degree;
        this->mark = mark;
        this->key = key;
        this->value = value;
    }
};

class fibonacci
{
private:
    node *root;
    int size;

public:
    fibonacci()
    {
        root = make_heap();
        size = 0;
    }

    node *make_heap(int key = 0, int value = 0)
    {
        node *new_node = new node(key, value);
        return new_node;
    }

    bool is_empty()
    {
        return size == 0;
    }

    void insert(int key, int value)
    {
        node *new_node = new node(key, value);
        new_node->left = new_node->right = new_node;
        if (size == 0)
        {
            root = new_node;
        }
        else
        {
            root->left->right = new_node;
            new_node->left = root->left;
            new_node->right = root;
            root->left = new_node;
        }

        if (root->key < key)
        {
            root = new_node;
        }

        size++;
    }

    void link(node *y, node *x)
    {
        y->left->right = y->right;
        y->right->left = y->left;
        if (x->right == x)
        {
            root == x;
        }
        y->left = y->right = y;
        y->right = x->child;
        y->parent = x;
        if (x->child == NULL)
        {
            x->child = y;
        }
        y->right = x->child;
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;
        if (y->key > x->child->key)
        {
            x->child = y;
        }
        x->degree++;
        y->mark = false;
    }

    void consolidate()
    {
        int temp1;
        double temp2 = log(size) / log(2);
        int temp3 = temp2;
        node *ara[temp3 + 1];
        for (int i = 0; i <= temp3; i++)
        {
            ara[i] = NULL;
        }
        node *new_node = root;
        node *ptr2;
        node *ptr3;
        node *ptr4 = new_node;
        do
        {
            ptr4 = ptr4->right;
            temp1 = new_node->degree;
            while (ara[temp1] != NULL)
            {
                ptr2 = ara[temp1];
                if (new_node->key < ptr2->key)
                {
                    ptr3 = new_node;
                    new_node = ptr2;
                    ptr2 = ptr3;
                }
                if (ptr2 == root)
                {
                    root = new_node;
                }
                link(ptr2, new_node);
                if (new_node->right == new_node)
                {
                    root = new_node;
                }
                ara[temp1] = NULL;
                temp1++;
            }
            ara[temp1] = new_node;
            new_node = new_node->right;
        } while (new_node != root);
        root = NULL;
        for (int i = 0; i <= temp3; i++)
        {
            if (ara[i] != NULL)
            {
                ara[i]->left = ara[i];
                ara[i]->right = ara[i];
                if (root != NULL)
                {
                    root->left->right = ara[i];
                    ara[i]->right = root;
                    ara[i]->left = root->left;
                    root->left = ara[i];
                    if (ara[i]->key > root->key)
                    {
                        root = ara[i];
                    }
                }
                else
                {
                    root = ara[i];
                }
                if (root == NULL)
                {
                    root = ara[i];
                }
                else if (ara[i]->key > root->key)
                {
                    root = ara[i];
                }
            }
        }
    }

    
    pair<int,int> extract_max()
    {
        if(root==NULL)
        {
            cout<<"Heap is empty!"<<endl;
            return {INT_MIN,INT_MIN};
        }
        if (root != NULL)
        {
            node *max = root;
            node *temp = max;
            node *x = NULL;
            if (max->child != NULL)
            {
                x = max->child;
                do
                {
                    temp = x->right;
                    root->left->right = x;
                    x->right = root;
                    x->left = root->left;
                    root->left = x;
                    if (x->key > root->key)
                    {
                        root = x;
                    }
                    x->parent = NULL;
                    x = temp;
                } while (temp != max->child);
            }
            max->left->right = max->right;
            max->right->left = max->left;
            root = max->right;
            if (max == max->right && max->child == NULL)
            {
                root = NULL;
            }
            else
            {
                root = temp->right;
                consolidate();
            }

            size--;
            if(size == 0)
            {
                root=NULL;
            }
            return {max->key, max->value};
        } 
    }
    // void printTree(node *rot, int depth)
    // {
    //     // Print the current node
    //     cout << "(" << rot->key << ", " << rot->value << ")";

    //     // Print children recursively
    //     if (rot->child)
    //     {
    //         cout << " -> ";
    //         node *child = rot->child;
    //         do
    //         {
    //             printTree(child, depth + 1);
    //             child = child->right;
    //             if (child != rot->child)
    //                 cout << ", ";
    //         } while (child != rot->child);
    //     }
    // }

    // void print()
    // {
    //     if (size != 0)
    //     {
    //         node *rootList = root;
    //         int treeNum = 1;
    //         do
    //         {
    //             cout << "Tree " << treeNum << ": ";
    //             printTree(rootList, 0);
    //             cout << endl;
    //             rootList = rootList->right;
    //             treeNum++;
    //         } while (rootList != root);
    //     }
    //     else
    //     {
    //         cout << "The heap is empty." << endl;
    //     }
    // }

    void print_tree(node* x){ 
            if(x == NULL || x->child == NULL){ 
                cout<<endl;
                return; 
            }   
            node* temp = x;
            node* temp2 = temp->child; 
            do{
                cout<<"("<<temp2->key<<", "<<temp2->value<<")";
                if(temp2->right != temp->child){
                    cout<<",";
                }
                temp2 = temp2->right;
            }while(temp2 != temp->child);

            cout<<endl;

            temp2 = temp->child;
            do{
                if(temp2->child != NULL){
                   cout<<"        ("<<temp2->key<<", "<<temp2->value<<")"<<"->";
                   print_tree(temp2);
                }
                temp2 = temp2->right;
            }while(temp2 != temp->child);

            //cout<<endl;
         }


         void print(){ 
            int treeNum = 1; 
            node* temp = root;
            if(temp == NULL){
                cout<<"The heap is empty"<<endl;
                return;
            }

            do{
                cout<<"Tree "<<treeNum<<": ";
                cout<<"("<<temp->key<<", "<<temp->value<<")";
                if(temp->child != NULL){
                    cout<<"->";
                }
                print_tree(temp);
                temp = temp->right; 
                //cout<<endl;
                treeNum++;
            }while(temp != root);
         }

    int Size()
    {
        return size;
    }
    
    node *findNode(node *rot, int value)
    {
        if (rot == NULL)
            return NULL;

        node *temp = rot;
        temp->found = 'Y';

        node *ptr = NULL;
        if (temp->value == value)
        {
            ptr = temp;
            temp->found = 'N';
            return ptr;
        }
        if (ptr == NULL)
        {
            if (temp->child != NULL)
            {
                ptr = findNode(temp->child, value);
            }

            if (ptr == NULL && temp->right->found != 'Y')
            {
                ptr = findNode(temp->right, value);
            }
        }
        temp->found = 'N';

        return ptr;
    }
    void cut(node *x, node *y)
    {
        if (x == x->right)
        {
            y->child = NULL;
        }
        x->right->left = x->left;
        x->left->right = x->right;
        if (x == y->child)
        {
            y->child = x->right;
        }
        x->right = x->left = x;
        y->degree--;
        root->left->right = x;
        x->right = root;
        x->left = root->left;
        root->left = x;
        x->parent = NULL;
        x->mark = false;
    }

    void cascade_cut(node *z)
    {
        node *temp = z->parent;
        if (temp != NULL)
        {
            if (z->mark == false)
            {
                z->mark = true;
            }
            else
            {
                cut(z, temp);
                cascade_cut(temp);
            }
        }
    }
    void increase_key(int value, int key)
    {
        if (root == NULL)
        {
            cout << "The heap is empty" << endl;
            return;
        }
        node *test = findNode(root, value);
        if (test == NULL)
        {
            cout << "The node is not found" << endl;
        }
        else
        {
            if (test->key >= key)
            {
                cout << "The key is not greater than node's key" << endl;
            }
            else
            {
                test->key = key;
                node *temp = test->parent;
                if (temp != NULL && temp->key < test->key)
                {
                    cut(test, temp);
                    cascade_cut(temp);
                }
                if (test->key > root->key)
                {
                    root = test;
                }

                // cout<<"The key is increased succesfully"<<endl;
            }
        }
    }

    void Delete(int value)
    {
        if (root == NULL)
        {
            cout << "the root is empty" << endl;
            return;
        }
        node *temp = findNode(root, value);
        if (temp == NULL)
        {
            cout << "the node is not found" << endl;
            return;
        }
        else
        {
            increase_key(temp->value, 100001);
            extract_max();
            cout << "Key deleted successfully" << endl;
        }
    }

    fibonacci meld(fibonacci &heap1)
    {
        if(root == NULL)
        {
            return heap1;
        }
        if(heap1.root == NULL)
        {
            return *this;
        }
        fibonacci heap;
        heap.root=root;

        node *temp1 = heap.root->left;
        node *temp2 = heap1.root->left;

        heap.root->left->right = heap1.root;
        heap1.root->left->right = heap.root;
        heap.root->left = temp2;
        heap1.root->left = temp1;

        if(heap.root->key >= heap1.root->key) {
            root=heap.root;
            //heap1.root = NULL;
        }
        else
        {
            root=heap1.root;
            //heap.root = NULL;
        }
        size+=heap1.size;
        heap1.size=0;
        return *this;
    }
    pair<int,int> find_max()
    {
        if(root == NULL)
        {
             cout << "root is empty" << endl;
        return{INT_MIN,INT_MIN};
        }
        return {root->key, root->value};
    }
   
};

