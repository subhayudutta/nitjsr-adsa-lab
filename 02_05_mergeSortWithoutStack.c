#include <stdio.h>

void merge(int a[], int l, int m, int r)
{
    int i = l, j = m + 1, k = 0, temp[1000];
    while (i <= m && j <= r)
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
    while (i <= m)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++)
        a[i] = temp[k++];
}

void mergeSortBottomUp(int a[], int n)
{
    for (int w = 1; w < n; w *= 2)
        for (int i = 0; i < n; i += 2 * w)
        {
            int l = i, m = i + w - 1, r = i + 2 * w - 1;
            if (m < n)
                merge(a, l, m, (r < n ? r : n - 1));
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

    mergeSortBottomUp(A, n);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
}