#include <iostream>
using namespace std;

class BTreeNode
{
    int *key;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;

public:
    BTreeNode(int _t, bool _leaf);

    void insertNonFull(int k);

    void splitChild(int i, BTreeNode *y);

    void traverse();

    BTreeNode *search(int k);
    int findKey(int k);

    void farewell(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);

    int findpredecessor(int idx);
    int findsuccesor(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);

    void merge(int idx);

    friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;

public:
    BTree(int tt)
    {
        root = NULL;
        t = tt;
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    BTreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k);

    void farewell(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;

    key = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];

    n = 0;
}

void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << key[i];
    }

    if (leaf == false)
        C[i]->traverse();
}

BTreeNode *BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > key[i])
        i++;

    if (key[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(k);
}

void BTree::insert(int k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->key[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode *s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->key[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && key[i] > k)
        {
            key[i + 1] = key[i];
            i--;
        }

        key[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && key[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);

            if (key[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->key[j] = y->key[j + t];

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        key[j + 1] = key[j];

    key[i] = y->key[t - 1];

    n = n + 1;
}

void BTree::farewell(int k)
{
    if (!root)
    {
        cout << "The database is empty please insert entries to use this operation\n";
        return;
    }

    root->farewell(k);

    if (root->n == 0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
        delete tmp;
    }
    return;
}

int BTreeNode::findKey(int k)
{
    int idx = 0;
    while (idx < n && key[idx] < k)
        ++idx;
    return idx;
}

void BTreeNode::removeFromLeaf(int idx)
{

    for (int i = idx + 1; i < n; ++i)
        key[i - 1] = key[i];

    n--;

    return;
}

void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = key[idx];

    if (C[idx]->n >= t)
    {
        int pred = findpredecessor(idx);
        key[idx] = pred;
        C[idx]->farewell(pred);
    }

    else if (C[idx + 1]->n >= t)
    {
        int succ = findsuccesor(idx);
        key[idx] = succ;
        C[idx + 1]->farewell(succ);
    }

    else
    {
        merge(idx);
        C[idx]->farewell(k);
    }
    return;
}

int BTreeNode::findpredecessor(int idx)
{
    BTreeNode *cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->key[cur->n - 1];
}

int BTreeNode::findsuccesor(int idx)
{

    BTreeNode *cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->key[0];
}

void BTreeNode::fill(int idx)
{

    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);

    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);

    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx)
{

    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->key[i + 1] = child->key[i];

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->key[0] = key[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    key[idx - 1] = sibling->key[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->key[(child->n)] = key[idx];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    key[idx] = sibling->key[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->key[i - 1] = sibling->key[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->key[t - 1] = key[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->key[i + t] = sibling->key[i];

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i)
        key[i - 1] = key[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}

void BTreeNode::farewell(int k)
{
    int idx = findKey(k);

    if (idx < n && key[idx] == k)
    {

        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        if (leaf)
        {
            cout << "" << k << " not found in the database\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->farewell(k);
        else
            C[idx]->farewell(k);
    }
    return;
}

int main()
{
    int k, Age, i = 0;
    int choice;
    int default_in;
    char O;
    BTree t(3);

    cout << "\n do you want to multiple entries at first (enter 1) or proceed to main menu and make entries as you go ? \n ";
    cin >> default_in;

    switch (default_in)
    {
    case 1:
    {
        int x, prof_age;
        int j = 0;

        cout << "how many entries do you want to make ? ";
        cin >> x;

        while (j < x)
        {
            cout << "Enter professor age : ";
            cin >> prof_age;
            t.insert(prof_age);
            cout << endl;
            j++;

            cout << "these are current entries in the database ";
            t.traverse();
            cout << endl;

           /* if (j == x-1 )
            {
                cout << "\nall entries were made succesfully xD \n"; 
            } */
        }
    }

    default:
    {

        while (choice != 4)
        {

            cout << "\n case 1 : make an entry\n case 2: delete an entry \n case 3: search \n case 4: exit ";
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                cout << "Enter professor age : ";
                cin >> Age;
                t.insert(Age);
                cout << endl;
                i++;

                cout << "these are current entries in the database ";
                t.traverse();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "enter farewell entry :\n";
                cin >> k;
                t.farewell(k);
                cout << "we are sorry to see you go :(\n";
                cout << "the current entries in database are :";
                t.traverse();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "Enter Professor age to search :";
                cin >> k;
                (t.search(k) != NULL) ? cout << "\n found : " << k : cout << "\n not found";
                break;
            }
            case 4:
            {
                break;
            }

            default:
            {
                printf("\nplease select case 1 2 3 or 4\n");
            }
            }
        }
    }

  }
    return 0;
}
