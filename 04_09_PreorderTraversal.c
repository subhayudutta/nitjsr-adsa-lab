#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
void preorderTraversal(struct Node *root)
{
    if (root == NULL)
        return;
    struct Node *stack[100];
    int top = -1;

    stack[++top] = root;

    while (top >= 0)
    {
        struct Node *node = stack[top--];
        printf("%d ", node->data);
        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
}

int main()
{

    struct Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Preorder Traversal: ");
    preorderTraversal(root);

    return 0;
}