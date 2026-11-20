
 * CodeAlpha C Programming Internship - Task 1
 * Basic Calculator using switch-case.

#include <stdio.h>

int main(void)
{
    double num1, num2;
    char operation;

    printf("===== BASIC CALCULATOR =====\n");
    printf("Enter an operator (+, -, *, /): ");
    if (scanf(" %c", &operation) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter two numbers: ");
    if (scanf("%lf %lf", &num1, &num2) != 2) {
        printf("Invalid number input.\n");
        return 1;
    }

    switch (operation) {
        case '+':
            printf("Result = %.2lf\n", num1 + num2);
            break;

        case '-':
            printf("Result = %.2lf\n", num1 - num2);
            break;

        case '*':
            printf("Result = %.2lf\n", num1 * num2);
            break;

        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
            } else {
                printf("Result = %.2lf\n", num1 / num2);
            }
            break;

        default:
            printf("Invalid operator. Please use +, -, * or /.\n");
    }

    return 0;
}
