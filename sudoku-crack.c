#include <stdio.h>
#include <stdlib.h>

int dimensions = 9;

// print the puzzle
void print_board(int board[dimensions][dimensions])
{
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            if (board[i][j] == 0)
            {
                printf("\033[0;30m"); // Set the text to the color black
            }
            else
            {
                printf("\033[0;32m"); // Set the text to the color green
            }
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\033[0m"); // Resets the text to default color
}

int is_valid(int board[][dimensions], int row, int col, int selection)
{
    // check row
    for (size_t i = 0; i < dimensions; i++)
    {
        if (board[row][i] == selection)
        {
            return 0;
        }
    }

    // check column
    for (size_t i = 0; i < dimensions; i++)
    {
        if (board[i][col] == selection)
        {
            return 0;
        }
    }

    // check the 3x3 square
    int starting_column = (col / 3) * 3;
    int starting_row = (row / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (board[starting_row + i][starting_column + j] == selection)
            {
                return 0;
            }
        }
    }
    return 1; // valid selection
}

int solveSudoku(int board[][dimensions], int row, int col)
{
    // Base case, reached the 10th row/ array[9][0]
    if (row == dimensions)
    {
        return 1;
    }

    // is not filled
    if (board[row][col] == 0)
    {

        // check all 1-9
        for (int selection = 1; selection <= dimensions; selection++)
        {
            // is selection valid?
            if (!is_valid(board, row, col, selection))
            {
                continue;
            }

            board[row][col] = selection; // fill the square

            // move on to the next square
            if (col >= 8)
            {
                col = -1;
                row++;
            }

            if (solveSudoku(board, row, col + 1))
            {
                return 1;
            }

            board[row][col] = 0; // backtrack / remove the queen
        }
    }

    // square is filled
    else
    {
        // move on to the next square
        if (col >= 8)
        {
            col = -1;
            row++;
        }

        if (solveSudoku(board, row, col + 1))
        {
            return 1;
        }
    }

    return 0; // end of the loop
}

int main()
{
    int board[][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    print_board(board);
    printf("\n");

    if (solveSudoku(board, 0, 0) == 1)
        print_board(board);

    else
        printf("No solution exists");

    return 0;
}