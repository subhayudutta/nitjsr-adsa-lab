#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3

typedef struct BTreeNode
{
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;
    bool leaf;
} BTreeNode;

BTreeNode *createTree()
{
    BTreeNode *node = malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = true;
    for (int i = 0; i < 2 * T; i++)
        node->children[i] = NULL;
    return node;
}

void traverse(BTreeNode *root)
{
    if (!root)
        return;
    int i;
    for (i = 0; i < root->n; i++)
    {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

bool searchItem(BTreeNode *root, int k, int *pos)
{
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && k == root->keys[i])
    {
        *pos = i;
        return true;
    }
    if (root->leaf)
        return false;
    return searchItem(root->children[i], k, pos);
}

void splitChild(BTreeNode *x, int i, BTreeNode *y)
{
    BTreeNode *z = malloc(sizeof(BTreeNode));
    z->leaf = y->leaf;
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];
    if (!y->leaf)
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];

    y->n = T - 1;

    for (int j = x->n; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n += 1;
}

void insertNonFull(BTreeNode *x, int k)
{
    int i = x->n - 1;

    if (x->leaf)
    {
        while (i >= 0 && k < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    }
    else
    {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->children[i]->n == 2 * T - 1)
        {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

BTreeNode *insertItem(BTreeNode *root, int k)
{
    if (root->n == 2 * T - 1)
    {
        BTreeNode *s = createTree();
        s->leaf = false;
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (k > s->keys[0])
            i++;
        insertNonFull(s->children[i], k);
        return s;
    }
    else
    {
        insertNonFull(root, k);
        return root;
    }
}

int findKey(BTreeNode *node, int k)
{
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        ++idx;
    return idx;
}

void removeFromLeaf(BTreeNode *node, int idx)
{
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];
    node->n--;
}

void removeFromNonLeaf(BTreeNode *node, int idx);

int getPred(BTreeNode *node, int idx)
{
    BTreeNode *cur = node->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int getSucc(BTreeNode *node, int idx)
{
    BTreeNode *cur = node->children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void borrowFromPrev(BTreeNode *node, int idx)
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[idx - 1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    node->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void borrowFromNext(BTreeNode *node, int idx)
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[(child->n)] = node->keys[idx];

    if (!(child->leaf))
        child->children[(child->n) + 1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void merge(BTreeNode *node, int idx)
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[T - 1] = node->keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + T] = sibling->keys[i];

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i + T] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    for (int i = idx + 2; i <= node->n; ++i)
        node->children[i - 1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}

void fill(BTreeNode *node, int idx)
{
    if (idx != 0 && node->children[idx - 1]->n >= T)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->children[idx + 1]->n >= T)
        borrowFromNext(node, idx);
    else
    {
        if (idx != node->n)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

void removeKey(BTreeNode *node, int k)
{
    int idx = findKey(node, k);

    if (idx < node->n && node->keys[idx] == k)
    {
        if (node->leaf)
            removeFromLeaf(node, idx);
        else
            removeFromNonLeaf(node, idx);
    }
    else
    {
        if (node->leaf)
        {
            return;
        }
        bool flag = (idx == node->n);
        if (node->children[idx]->n < T)
            fill(node, idx);
        if (flag && idx > node->n)
            removeKey(node->children[idx - 1], k);
        else
            removeKey(node->children[idx], k);
    }
}

void removeFromNonLeaf(BTreeNode *node, int idx)
{
    int k = node->keys[idx];

    if (node->children[idx]->n >= T)
    {
        int pred = getPred(node, idx);
        node->keys[idx] = pred;
        removeKey(node->children[idx], pred);
    }
    else if (node->children[idx + 1]->n >= T)
    {
        int succ = getSucc(node, idx);
        node->keys[idx] = succ;
        removeKey(node->children[idx + 1], succ);
    }
    else
    {
        merge(node, idx);
        removeKey(node->children[idx], k);
    }
}

BTreeNode *deleteItem(BTreeNode *root, int k)
{
    if (!root)
        return root;
    removeKey(root, k);
    if (root->n == 0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->children[0];
        free(tmp);
    }
    return root;
}

void deleteTree(BTreeNode *root)
{
    if (!root)
        return;
    if (!root->leaf)
    {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

int main()
{
    BTreeNode *root = createTree();

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++)
        root = insertItem(root, keys[i]);

    printf("B Tree (in order): ");
    traverse(root);
    printf("\n");

    int pos;
    if (searchItem(root, 12, &pos))
        printf("Key 12 found in leaf at pos %d\n", pos);
    else
        printf("Key 12 not found\n");

    root = deleteItem(root, 6);
    printf("After deleting 6: ");
    traverse(root);
    printf("\n");

    deleteTree(root);
    return 0;
}
