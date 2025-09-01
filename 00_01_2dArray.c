#include <stdio.h>

int main()
{
    int r, c;
    printf("Enter total rows: ");
    scanf("%d", &r);
    printf("Enter total columns: ");
    scanf("%d", &c);

    int matrix[50][50];

    printf("\n--- Fill the matrix with values ---\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("Value at position (%d,%d): ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nThe 2D Matrix is:\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
