#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define N 10
#define M 10
#define BUCKET_SIZE 10

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n)
{
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Insertion Sort
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bubble Sort
void bubbleSort(int A[], int n)
{
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
}

// Selection Sort
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
            swap(&arr[i], &arr[minIndex]);
    }
}

// Shell Sort
void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// Quick Sort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
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

// Heap Sort
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

// Radix Sort
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
void countingSortRadix(int arr[], int n, int exp)
{
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortRadix(arr, n, exp);
}

// Counting Sort
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

// Bucket Sort
void bucketSort(int arr[], int n)
{
    int i, j, k;

    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int *buckets[BUCKET_SIZE];
    int count[BUCKET_SIZE] = {0};

    for (i = 0; i < BUCKET_SIZE; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        int index = (BUCKET_SIZE * arr[i]) / (max + 1);
        buckets[index][count[index]++] = arr[i];
    }

    for (i = 0; i < BUCKET_SIZE; i++)
        insertionSort(buckets[i], count[i]);

    k = 0;
    for (i = 0; i < BUCKET_SIZE; i++)
    {
        for (j = 0; j < count[i]; j++)
        {
            arr[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }
}

// Radix Exchange Sort
int getBit(int num, int bitPos)
{
    return (num >> bitPos) & 1;
}
void radixExchangeSort(int arr[], int left, int right, int bitPos)
{
    if (left >= right || bitPos < 0)
        return;

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (i <= j && getBit(arr[i], bitPos) == 0)
            i++;
        while (i <= j && getBit(arr[j], bitPos) == 1)
            j--;

        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    radixExchangeSort(arr, left, j, bitPos - 1);
    radixExchangeSort(arr, i, right, bitPos - 1);
}
int getMaxBitPos(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bitPos = 0;
    while (max >> bitPos)
        bitPos++;
    return bitPos - 1;
}

// Address Calculation Sort
void addressCalculationSort(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int *buckets[M];
    int count[M] = {0};

    for (int i = 0; i < M; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        int index = (arr[i] * M) / (max + 1);
        buckets[index][count[index]++] = arr[i];
    }

    for (int i = 0; i < M; i++)
        insertionSort(buckets[i], count[i]);

    int idx = 0;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            arr[idx++] = buckets[i][j];
        }
        free(buckets[i]);
    }
}

// Main Function
int main()
{
    int A[MAX], n, choice, maxBit;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    while (1)
    {
        printf("\nChoose Sorting Algorithm:\n");
        printf("1. Insertion Sort\n");
        printf("2. Bubble Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Shell Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Merge Sort\n");
        printf("7. Heap Sort\n");
        printf("8. Radix Sort\n");
        printf("9. Counting Sort\n");
        printf("10. Bucket Sort\n");
        printf("11. Radix Exchange Sort\n");
        printf("12. Address Calculation Sort\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("\nExited!\n");
            break;
        }

        switch (choice)
        {
        case 1:
            insertionSort(A, n);
            break;
        case 2:
            bubbleSort(A, n);
            break;
        case 3:
            selectionSort(A, n);
            break;
        case 4:
            shellSort(A, n);
            break;
        case 5:
            quickSort(A, 0, n - 1);
            break;
        case 6:
            mergeSort(A, 0, n - 1);
            break;
        case 7:
            heapSort(A, n);
            break;
        case 8:
            radixSort(A, n);
            break;
        case 9:
            countingSort(A, n);
            break;
        case 10:
            bucketSort(A, n);
            break;
        case 11:
            maxBit = getMaxBitPos(A, n);
            radixExchangeSort(A, 0, n - 1, maxBit);
            break;
        case 12:
            addressCalculationSort(A, n);
            break;
        default:
            printf("Invalid choice.\n");
            continue;
        }

        printArray(A, n);
    }

    return 0;
}