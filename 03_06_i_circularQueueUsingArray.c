#include <stdio.h>
#define SIZE 5

int queue[SIZE], front = -1, rear = -1;

void enqueue(int val)
{
    if ((rear + 1) % SIZE == front)
        printf("Queue is Full\n");
    else
    {
        if (front == -1)
            front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = val;
    }
}

void dequeue()
{
    if (front == -1)
        printf("Queue is Empty\n");
    else
    {
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % SIZE;
    }
}

void display()
{
    if (front == -1)
        printf("Queue is Empty\n");
    else
    {
        int i = front;
        while (1)
        {
            printf("%d ", queue[i]);
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}

int main()
{
    int choice, value;
    while (1)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nEnter choice: ");
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
