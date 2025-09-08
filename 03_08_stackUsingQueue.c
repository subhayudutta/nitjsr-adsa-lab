#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int arr[MAX];
    int front;
    int rear;
} Queue;

typedef struct
{
    Queue q1;
    Queue q2;
} Stack;

void initQueue(Queue *q)
{
    q->front = q->rear = -1;
}

int isEmptyQueue(Queue *q)
{
    return q->front == -1;
}

int isFullQueue(Queue *q)
{
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int data)
{
    if (isFullQueue(q))
    {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmptyQueue(q))
    {
        q->front = 0;
    }
    q->arr[++(q->rear)] = data;
}

int dequeue(Queue *q)
{
    if (isEmptyQueue(q))
    {
        printf("Queue Underflow\n");
        return -1;
    }
    int data = q->arr[q->front++];
    if (q->front > q->rear)
    {
        q->front = q->rear = -1;
    }
    return data;
}

int front(Queue *q)
{
    if (isEmptyQueue(q))
        return -1;
    return q->arr[q->front];
}

//  Method 1: Costly Enqueue (Push)
void push_costlyEnqueue(Stack *s, int data)
{
    enqueue(&s->q2, data);

    while (!isEmptyQueue(&s->q1))
    {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

int pop_costlyEnqueue(Stack *s)
{
    if (isEmptyQueue(&s->q1))
    {
        printf("Stack is Empty\n");
        return -1;
    }
    return dequeue(&s->q1);
}

// Method 2: Costly Dequeue (Pop)
void push_costlyDequeue(Stack *s, int data)
{
    enqueue(&s->q1, data);
}

int pop_costlyDequeue(Stack *s)
{
    if (isEmptyQueue(&s->q1))
    {
        printf("Stack is Empty\n");
        return -1;
    }

    while (s->q1.front != s->q1.rear)
    {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    int popped = dequeue(&s->q1);

    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return popped;
}

int main()
{
    Stack s1, s2;
    initQueue(&s1.q1);
    initQueue(&s1.q2);
    initQueue(&s2.q1);
    initQueue(&s2.q2);

    printf("Method 1: Costly Enqueue\n");
    push_costlyEnqueue(&s1, 10);
    push_costlyEnqueue(&s1, 20);
    push_costlyEnqueue(&s1, 30);
    printf("Popped: %d\n", pop_costlyEnqueue(&s1));
    printf("Popped: %d\n", pop_costlyEnqueue(&s1));

    printf("\nMethod 2: Costly Dequeue\n");
    push_costlyDequeue(&s2, 100);
    push_costlyDequeue(&s2, 200);
    push_costlyDequeue(&s2, 300);
    printf("Popped: %d\n", pop_costlyDequeue(&s2));
    printf("Popped: %d\n", pop_costlyDequeue(&s2));

    return 0;
}
