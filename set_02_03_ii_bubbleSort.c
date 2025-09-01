#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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

    for (int i = 0; i < n; i++)
    {
        int flag = 1;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j + 1], &A[j]);
                flag = 0;
            }
        }
        if (flag)
            break;
    }

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}