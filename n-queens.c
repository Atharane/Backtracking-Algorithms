#include <stdio.h>
int dimensions;

int is_valid(int board[][dimensions], int row, int col)
{
    // first row
    if (row == 0)
        return 1;

    int diagonal_row;
    int diagonal_col;

    for (size_t i = 0; i < row; i++)
    {
        if (board[i][col])
        {
            return 0; // queen already in the column
        }

        diagonal_row = row - i - 1;
        diagonal_col = col - i - 1;

        if (diagonal_col >= 0 && board[diagonal_row][diagonal_col])
        {
            return 0; // queen already in the 135° deg diagonal
        }

        diagonal_col = col + i + 1;

        if (col + i + 1 < dimensions && board[diagonal_row][diagonal_col])
        {
            return 0; // queen already in the 45° deg diagonal
        }
    }
    return 1; // queen not being attacked
}

int n_queens(int board[][dimensions], int row)
{
    // Base case, n queeens place
    if (row == dimensions)
    {
        return 1;
    }

    for (int col = 0; col < dimensions; col++)
    {
        // is queen being attacked
        if (!is_valid(board, row, col))
        {
            continue;
        }

        board[row][col] = 1; // place the queen

        // move on to the next row
        if (n_queens(board, row + 1))
        {
            return 1;
        }

        board[row][col] = 0; // backtrack / remove the queen
    }

    return 0;
}

int main()
{
    printf("Dimesions: ");
    scanf("%d", &dimensions);

    // create a 2-d array of size dimensions x dimensions representing the board
    int board[dimensions][dimensions];

    // initialize the board to 0
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            board[i][j] = 0;
        }
    }

    if (n_queens(board, 0))
    {
        for (int i = 0; i < dimensions; i++)
        {

            for (int j = 0; j < dimensions; j++)
            {
                if (board[i][j] == 1)
                {
                    printf("\033[0;32m"); // Set the text to the color green
                    printf("1 ");
                    printf("\033[0m"); // Resets the text to default color
                }
                else
                {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("\033[0;31m"); // Set the text to the color red
        printf("No solution found\n");
        printf("\033[0m"); // Resets the text to default color
    }

    return 0;
}