# CodeAlpha C Programming Internship Projects

This repository contains three C programming projects selected from the CodeAlpha internship task list.

## Projects

1. **Task 1 – Basic Calculator**
   - Addition, subtraction, multiplication and division
   - Uses `switch-case`
   - Checks division by zero

2. **Task 2 – Matrix Operations**
   - Matrix addition
   - Matrix multiplication
   - Matrix transpose
   - Uses functions and 2D arrays
   - Supports matrix dimensions up to 10 x 10

3. **Task 3 – Student Management System**
   - Add, display, search, update and delete student records
   - Uses structures and file handling
   - Stores records permanently in `students.dat`

## Requirements

- A C compiler such as GCC
- A terminal or IDE (Code::Blocks, VS Code, etc.)

## Compile and run

Open a terminal in the relevant project folder.

### Task 1
```bash
gcc calculator.c -o calculator
./calculator
```

### Task 2
```bash
gcc matrix_operations.c -o matrix_operations
./matrix_operations
```

### Task 3
```bash
gcc student_management.c -o student_management
./student_management
```

On Windows, run the generated program as `calculator.exe`, `matrix_operations.exe`, or `student_management.exe`.

## Notes

- Run Task 3 from a folder where the program can create and update files. Its data file, `students.dat`, is created automatically when the first student is added.
- Keep `students.dat` in the same folder as the Task 3 executable so saved records remain available.
- Test each menu option before submitting.
