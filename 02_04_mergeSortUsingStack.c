#include <stdio.h>

struct Frame
{
    int l, r, stage;
};

void merge(int a[], int l, int m, int r)
{
    int temp[1000], i = l, j = m + 1, k = 0;
    while (i <= m && j <= r)
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
    while (i <= m)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++)
        a[i] = temp[k++];
}

void mergeSortStack(int a[], int n)
{
    struct Frame stack[1000];
    int top = 0;

    stack[top++] = (struct Frame){0, n - 1, 0};

    while (top)
    {
        struct Frame f = stack[--top];
        int l = f.l, r = f.r, m = (l + r) / 2;

        if (l >= r)
            continue;

        if (f.stage == 0)
        {
            stack[top++] = (struct Frame){l, r, 1};
            stack[top++] = (struct Frame){m + 1, r, 0};
            stack[top++] = (struct Frame){l, m, 0};
        }
        else
        {
            merge(a, l, m, r);
        }
    }
}

int main()
{
    int A[50], n;
    printf("Enter no. of terms: ");
    scanf("%d", &n);

    printf("\nEnter array elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    mergeSortStack(A, n);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
}
