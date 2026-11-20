/*
 * CodeAlpha C Programming Internship - Task 3
 * Student Management System using structures and file handling.
 *
 * Student records are stored permanently in "students.dat".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define TEMP_FILE "students_temp.dat"
#define NAME_SIZE 50

struct Student {
    int rollNumber;
    char name[NAME_SIZE];
    float marks;
};

void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
int rollNumberExists(int rollNumber);
void clearInputBuffer(void);
void readName(char name[], int size);

int main(void)
{
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Thank you for using the Student Management System.\n");
                break;
            default:
                printf("Invalid choice. Please select 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard remaining characters. */
    }
}

void readName(char name[], int size)
{
    int length;

    clearInputBuffer();
    if (fgets(name, size, stdin) != NULL) {
        length = (int)strlen(name);
        if (length > 0 && name[length - 1] == '\n') {
            name[length - 1] = '\0';
        } else {
            clearInputBuffer();
        }
    } else {
        name[0] = '\0';
    }
}

int rollNumberExists(int rollNumber)
{
    FILE *fp;
    struct Student student;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        return 0;
    }

    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        if (student.rollNumber == rollNumber) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent(void)
{
    FILE *fp;
    struct Student student;

    printf("Enter roll number: ");
    if (scanf("%d", &student.rollNumber) != 1 || student.rollNumber <= 0) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    if (rollNumberExists(student.rollNumber)) {
        printf("A student with this roll number already exists.\n");
        return;
    }

    printf("Enter student name: ");
    readName(student.name, NAME_SIZE);

    printf("Enter marks (0 to 100): ");
    if (scanf("%f", &student.marks) != 1 ||
        student.marks < 0 || student.marks > 100) {
        printf("Invalid marks. Marks must be between 0 and 100.\n");
        clearInputBuffer();
        return;
    }

    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Unable to open the student file.\n");
        return;
    }

    if (fwrite(&student, sizeof(struct Student), 1, fp) == 1) {
        printf("Student record added successfully.\n");
    } else {
        printf("Error while saving student record.\n");
    }

    fclose(fp);
}

void displayStudents(void)
{
    FILE *fp;
    struct Student student;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found yet.\n");
        return;
    }

    printf("\n%-12s %-25s %-10s\n", "Roll Number", "Name", "Marks");
    printf("------------------------------------------------\n");

    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        printf("%-12d %-25s %-10.2f\n",
               student.rollNumber, student.name, student.marks);
        found = 1;
    }

    if (!found) {
        printf("No student records found.\n");
    }

    fclose(fp);
}

void searchStudent(void)
{
    FILE *fp;
    struct Student student;
    int rollNumber, found = 0;

    printf("Enter roll number to search: ");
    if (scanf("%d", &rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        if (student.rollNumber == rollNumber) {
            printf("\nStudent Found\n");
            printf("Roll Number: %d\n", student.rollNumber);
            printf("Name       : %s\n", student.name);
            printf("Marks      : %.2f\n", student.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with roll number %d was not found.\n", rollNumber);
    }

    fclose(fp);
}

void updateStudent(void)
{
    FILE *fp;
    struct Student student;
    int rollNumber, found = 0;

    printf("Enter roll number to update: ");
    if (scanf("%d", &rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        if (student.rollNumber == rollNumber) {
            printf("Enter new student name: ");
            readName(student.name, NAME_SIZE);

            printf("Enter new marks (0 to 100): ");
            if (scanf("%f", &student.marks) != 1 ||
                student.marks < 0 || student.marks > 100) {
                printf("Invalid marks. Update cancelled.\n");
                clearInputBuffer();
                fclose(fp);
                return;
            }

            fseek(fp, -(long)sizeof(struct Student), SEEK_CUR);
            if (fwrite(&student, sizeof(struct Student), 1, fp) == 1) {
                printf("Student record updated successfully.\n");
            } else {
                printf("Error while updating student record.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with roll number %d was not found.\n", rollNumber);
    }

    fclose(fp);
}

void deleteStudent(void)
{
    FILE *fp, *temp;
    struct Student student;
    int rollNumber, found = 0;

    printf("Enter roll number to delete: ");
    if (scanf("%d", &rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    temp = fopen(TEMP_FILE, "wb");
    if (temp == NULL) {
        printf("Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        if (student.rollNumber == rollNumber) {
            found = 1;
        } else {
            fwrite(&student, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove(FILE_NAME) != 0) {
        printf("Could not replace the original student file.\n");
        remove(TEMP_FILE);
        return;
    }

    if (rename(TEMP_FILE, FILE_NAME) != 0) {
        printf("Could not save the updated student file.\n");
        return;
    }

    if (found) {
        printf("Student record deleted successfully.\n");
    } else {
        printf("Student with roll number %d was not found.\n", rollNumber);
    }
}
