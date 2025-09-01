#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int arr[MAX];
    int top;
} Stack;

// Queue using two stacks
typedef struct
{
    Stack s1;
    Stack s2;
} Queue;

void initStack(Stack *s)
{
    s->top = -1;
}

// Stack functions
int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX - 1;
}

void push(Stack *s, int data)
{
    if (isFull(s))
    {
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++(s->top)] = data;
}

int pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

int peek(Stack *s)
{
    if (isEmpty(s))
        return -1;
    return s->arr[s->top];
}

// METHOD 1: Push is Costly
void enqueue_costlyPush(Queue *q, int data)
{
    while (!isEmpty(&q->s1))
    {
        push(&q->s2, pop(&q->s1));
    }

    push(&q->s1, data);

    while (!isEmpty(&q->s2))
    {
        push(&q->s1, pop(&q->s2));
    }
}

int dequeue_costlyPush(Queue *q)
{
    if (isEmpty(&q->s1))
    {
        printf("Queue is Empty\n");
        return -1;
    }
    return pop(&q->s1);
}

// METHOD 2: Pop is Costly
void enqueue_costlyPop(Queue *q, int data)
{
    push(&q->s1, data);
}

int dequeue_costlyPop(Queue *q)
{
    int val;

    if (isEmpty(&q->s1) && isEmpty(&q->s2))
    {
        printf("Queue is Empty\n");
        return -1;
    }

    if (isEmpty(&q->s2))
    {
        while (!isEmpty(&q->s1))
        {
            push(&q->s2, pop(&q->s1));
        }
    }

    val = pop(&q->s2);
    return val;
}

// MAIN FUNCTION
int main()
{
    Queue q1, q2;
    initStack(&q1.s1);
    initStack(&q1.s2);
    initStack(&q2.s1);
    initStack(&q2.s2);

    printf("Method 1: Push is Costly\n");
    enqueue_costlyPush(&q1, 10);
    enqueue_costlyPush(&q1, 20);
    enqueue_costlyPush(&q1, 30);
    printf("Dequeued: %d\n", dequeue_costlyPush(&q1));
    printf("Dequeued: %d\n", dequeue_costlyPush(&q1));

    printf("\nMethod 2: Pop is Costly\n");
    enqueue_costlyPop(&q2, 100);
    enqueue_costlyPop(&q2, 200);
    enqueue_costlyPop(&q2, 300);
    printf("Dequeued: %d\n", dequeue_costlyPop(&q2));
    printf("Dequeued: %d\n", dequeue_costlyPop(&q2));

    return 0;
}
