#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random Sudoku puzzle
void generateRandomSudoku(int puzzle[9][9]) {
    // Clear the puzzle to all zeros initially
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            puzzle[i][j] = 0;
        }
    }

    srand(time(NULL)); // Seed for random number generation

    // Randomly decide the number of cells to pre-fill between 15 and 30
    int cellsToFill = 15 + rand() % 16; // Random number between 15 and 30

    for (int i = 0; i < cellsToFill; i++) {
        int row, col, num, isValid;

        do {
            row = rand() % 9;
            col = rand() % 9;
            num = rand() % 9 + 1;
            isValid = 1;

            // Check if the number can be placed in the cell
            for (int x = 0; x < 9; x++) {
                if (puzzle[row][x] == num || puzzle[x][col] == num) {
                    isValid = 0;
                    break;
                }
            }

            // Check the 3x3 subgrid
            int startRow = row / 3 * 3;
            int startCol = col / 3 * 3;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if (puzzle[startRow + x][startCol + y] == num) {
                        isValid = 0;
                        break;
                    }
                }
            }
        } while (!isValid || puzzle[row][col] != 0); // Ensure unique filling

        puzzle[row][col] = num;
    }
}

// Function to print the Sudoku puzzle
void printSudoku(int puzzle[9][9]) {
    printf("\n+-------+-------+-------+");
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("\n|-------+-------+-------|");
        }
        
        printf("\n");
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printf("| ");
            }
            if (puzzle[i][j] != 0) {
                printf("%d ", puzzle[i][j]);
            } else {
                printf("  ");
            }
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}

// Function to check if a move is valid
int valid_move(int puzzle[9][9], int row, int col, int val) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == val || puzzle[i][col] == val) {
            return 0;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[startRow + i][startCol + j] == val) {
                return 0;
            }
        }
    }
    return 1;
}

// Recursive function to solve the Sudoku puzzle
int solve_puzzle(int puzzle[9][9], int row, int col) {
    if (col == 9) {
        row++;
        col = 0;
    }

    if (row == 9) {
        return 1;
    }

    if (puzzle[row][col] > 0) {
        return solve_puzzle(puzzle, row, col + 1);
    }

    for (int i = 1; i <= 9; i++) { // Loop from 1 to 9 (valid Sudoku numbers)
        if (valid_move(puzzle, row, col, i)) {
            puzzle[row][col] = i;
            if (solve_puzzle(puzzle, row, col + 1)) {
                return 1;
            }
            puzzle[row][col] = 0;
        }
    }
    return 0;
}

int main() {
    int puzzle[9][9];
    generateRandomSudoku(puzzle);
    printf("Random Sudoku Puzzle (Unsolved):\n");
    printSudoku(puzzle);

    if (solve_puzzle(puzzle, 0, 0)) {
        printf("\nSolved Sudoku Puzzle:\n");
        printSudoku(puzzle);
    } else {
        printf("\nThe puzzle is not solvable. :(\n");
    }

    return 0;
}
