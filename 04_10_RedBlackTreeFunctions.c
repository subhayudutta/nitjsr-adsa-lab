#include <stdio.h>
#include <stdlib.h>

enum Color
{
    RED,
    BLACK
};

typedef struct Node
{
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;

Node *newNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->color = RED;
    n->left = n->right = n->parent = NULL;
    return n;
}

void rotateLeft(Node **root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node **root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(Node **root, Node *z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        }
        else
        {
            Node *y = z->parent->parent->left;
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertItem(int data)
{
    Node *z = newNode(data);
    Node *y = NULL;
    Node *x = root;

    while (x)
    {
        y = x;
        if (data < x->data)
            x = x->left;
        else if (data > x->data)
            x = x->right;
        else
        {
            free(z);
            return;
        }
    }

    z->parent = y;
    if (!y)
        root = z;
    else if (data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(&root, z);
}

Node *searchItem(Node *root, int key)
{
    if (!root || root->data == key)
        return root;
    if (key < root->data)
        return searchItem(root->left, key);
    return searchItem(root->right, key);
}

Node *minimum(Node *node)
{
    while (node->left)
        node = node->left;
    return node;
}

void fixDelete(Node **root, Node *x)
{
    while (x != *root && (!x || x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w && w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK))
            {
                if (w)
                    w->color = RED;
                x = x->parent;
            }
            else
            {
                if (!w->right || w->right->color == BLACK)
                {
                    if (w->left)
                        w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right)
                    w->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = *root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w && w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if ((!w->right || w->right->color == BLACK) &&
                (!w->left || w->left->color == BLACK))
            {
                if (w)
                    w->color = RED;
                x = x->parent;
            }
            else
            {
                if (!w->left || w->left->color == BLACK)
                {
                    if (w->right)
                        w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left)
                    w->left->color = BLACK;
                rotateRight(root, x->parent);
                x = *root;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

void rbTransplant(Node **root, Node *u, Node *v)
{
    if (!u->parent)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

void deleteItem(int data)
{
    Node *z = searchItem(root, data);
    if (!z)
        return;

    Node *y = z;
    Node *x;
    enum Color y_original_color = y->color;

    if (!z->left)
    {
        x = z->right;
        rbTransplant(&root, z, z->right);
    }
    else if (!z->right)
    {
        x = z->left;
        rbTransplant(&root, z, z->left);
    }
    else
    {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            if (x)
                x->parent = y;
        }
        else
        {
            rbTransplant(&root, y, y->right);
            y->right = z->right;
            if (y->right)
                y->right->parent = y;
        }
        rbTransplant(&root, z, y);
        y->left = z->left;
        if (y->left)
            y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK && x)
        fixDelete(&root, x);
}

void deleteTree(Node *node)
{
    if (!node)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

void inorder(Node *node)
{
    if (!node)
        return;
    inorder(node->left);
    printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
    inorder(node->right);
}

void createTree()
{
    deleteTree(root);
    root = NULL;
    printf("Tree created.\n");
}

int main()
{
    insertItem(10);
    insertItem(5);
    insertItem(15);
    insertItem(3);
    insertItem(7);

    deleteItem(3);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    deleteTree(root);
    root = NULL;

    return 0;
}
