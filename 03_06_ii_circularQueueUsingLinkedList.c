#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

void enqueue(int val)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    if (!front)
        front = rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
}

void dequeue()
{
    if (!front)
        printf("Queue is Empty\n");
    else if (front == rear)
    {
        free(front);
        front = rear = NULL;
    }
    else
    {
        struct Node *temp = front;
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void display()
{
    if (!front)
        printf("Queue is Empty\n");
    else
    {
        struct Node *temp = front;
        do
        {
            printf("%d ", temp->data);
            temp = temp->next;
        } while (temp != front);
        printf("\n");
    }
}

int main()
{
    int choice, value;
    while (1)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit \nEnter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
