#include <stdio.h>

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

    for (int i = 1; i < n; i++)
    {
        int x = A[i];
        int j = i - 1;
        while (A[j] > x && j != -1)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}