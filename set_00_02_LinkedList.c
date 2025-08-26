#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *link;
};

struct Node *start = NULL;

void insertNode(int num)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = num;
    newNode->link = NULL;

    if (start == NULL)
    {
        start = newNode;
        return;
    }
    struct Node *ptr = start;
    while (ptr->link != NULL)
        ptr = ptr->link;
    ptr->link = newNode;
}

void deleteNode(int num)
{
    if (start == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    if (start->value == num)
    {
        struct Node *temp = start;
        start = start->link;
        free(temp);
        printf("Deleted node with value %d\n", num);
        return;
    }
    struct Node *ptr = start;
    while (ptr->link != NULL && ptr->link->value != num)
    {
        ptr = ptr->link;
    }
    if (ptr->link != NULL)
    {
        struct Node *del = ptr->link;
        ptr->link = del->link;
        free(del);
        printf("Deleted node with value %d\n", num);
    }
    else
    {
        printf("Value not found in the list.\n");
    }
}

void searchNode(int num)
{
    struct Node *ptr = start;
    int index = 0;
    while (ptr != NULL)
    {
        if (ptr->value == num)
        {
            printf("Node with value %d found at position %d\n", num, index);
            return;
        }
        ptr = ptr->link;
        index++;
    }
    printf("Value not present in the list.\n");
}

void traverseList()
{
    if (start == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    struct Node *ptr = start;
    printf("List elements: ");
    while (ptr != NULL)
    {
        printf("%d -> ", ptr->value);
        ptr = ptr->link;
    }
    printf("NULL\n");
}

int main()
{
    int option, num;

    do
    {
        printf("\n=== Singly Linked List Menu ===\n");
        printf("1. Insert Node\n2. Delete Node\n3. Search Node\n4. Traverse List\n5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Enter number to insert: ");
            scanf("%d", &num);
            insertNode(num);
            break;
        case 2:
            printf("Enter number to delete: ");
            scanf("%d", &num);
            deleteNode(num);
            break;
        case 3:
            printf("Enter number to search: ");
            scanf("%d", &num);
            searchNode(num);
            break;
        case 4:
            traverseList();
            break;
        case 5:
            printf("Program terminated.\n");
            break;
        default:
            printf("Invalid option! Try again.\n");
        }
    } while (option != 5);

    return 0;
}
