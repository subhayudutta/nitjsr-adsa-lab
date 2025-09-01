#include <stdio.h>

void merge(int arr[], int left, int mid, int right)
{
    int temp[100];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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

    mergeSort(A, 0, n - 1);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}