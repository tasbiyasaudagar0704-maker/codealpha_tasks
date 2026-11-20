/*
 * CodeAlpha C Programming Internship - Task 2
 * Matrix addition, multiplication and transpose using functions.
 */

#include <stdio.h>

#define MAX 10

void readMatrix(int matrix[MAX][MAX], int rows, int cols);
void displayMatrix(int matrix[MAX][MAX], int rows, int cols);
void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols);
void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX], int rowsA,
                      int colsA, int colsB);
void transposeMatrix(int a[MAX][MAX], int result[MAX][MAX],
                     int rows, int cols);

int main(void)
{
    int choice;
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];
    int rowsA, colsA, rowsB, colsB;

    do {
        printf("\n===== MATRIX OPERATIONS =====\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Matrix Transpose\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter rows and columns of both matrices: ");
                if (scanf("%d %d", &rowsA, &colsA) != 2 ||
                    rowsA < 1 || rowsA > MAX ||
                    colsA < 1 || colsA > MAX) {
                    printf("Invalid matrix size. Maximum size is 10 x 10.\n");
                    break;
                }

                printf("Enter elements of first matrix:\n");
                readMatrix(a, rowsA, colsA);

                printf("Enter elements of second matrix:\n");
                readMatrix(b, rowsA, colsA);

                addMatrices(a, b, result, rowsA, colsA);
                printf("Addition result:\n");
                displayMatrix(result, rowsA, colsA);
                break;

            case 2:
                printf("Enter rows and columns of first matrix: ");
                if (scanf("%d %d", &rowsA, &colsA) != 2 ||
                    rowsA < 1 || rowsA > MAX ||
                    colsA < 1 || colsA > MAX) {
                    printf("Invalid matrix size. Maximum size is 10 x 10.\n");
                    break;
                }

                printf("Enter rows and columns of second matrix: ");
                if (scanf("%d %d", &rowsB, &colsB) != 2 ||
                    rowsB < 1 || rowsB > MAX ||
                    colsB < 1 || colsB > MAX) {
                    printf("Invalid matrix size. Maximum size is 10 x 10.\n");
                    break;
                }

                if (colsA != rowsB) {
                    printf("Multiplication not possible: columns of first "
                           "matrix must equal rows of second matrix.\n");
                    break;
                }

                printf("Enter elements of first matrix:\n");
                readMatrix(a, rowsA, colsA);

                printf("Enter elements of second matrix:\n");
                readMatrix(b, rowsB, colsB);

                multiplyMatrices(a, b, result, rowsA, colsA, colsB);
                printf("Multiplication result:\n");
                displayMatrix(result, rowsA, colsB);
                break;

            case 3:
                printf("Enter rows and columns of matrix: ");
                if (scanf("%d %d", &rowsA, &colsA) != 2 ||
                    rowsA < 1 || rowsA > MAX ||
                    colsA < 1 || colsA > MAX) {
                    printf("Invalid matrix size. Maximum size is 10 x 10.\n");
                    break;
                }

                printf("Enter elements of matrix:\n");
                readMatrix(a, rowsA, colsA);

                transposeMatrix(a, result, rowsA, colsA);
                printf("Transpose of matrix:\n");
                displayMatrix(result, colsA, rowsA);
                break;

            case 4:
                printf("Exiting Matrix Operations.\n");
                break;

            default:
                printf("Invalid choice. Please select 1 to 4.\n");
        }
    } while (choice != 4);

    return 0;
}

void readMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX], int rowsA,
                      int colsA, int colsB)
{
    int i, j, k;

    for (i = 0; i < rowsA; i++) {
        for (j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (k = 0; k < colsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transposeMatrix(int a[MAX][MAX], int result[MAX][MAX],
                     int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[j][i] = a[i][j];
        }
    }
}
