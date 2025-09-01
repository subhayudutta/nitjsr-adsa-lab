#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum value in the array
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Counting Sort function
void countingSort(int arr[], int n)
{
    int max = getMax(arr, n);

    int count[max + 1];
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    int index = 0;
    for (int i = 0; i <= max; i++)
    {
        while (count[i]-- > 0)
            arr[index++] = i;
    }
}

// Main function to test the sorting
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

    countingSort(A, n);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}
