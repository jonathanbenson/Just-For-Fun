#include <stdio.h>
#include <stdlib.h>

struct Box
{
    int value;
    int is_revealed;

    int row;
    int col;
    int cell;
};

struct Sudoku
{
    struct Box boxes[9][9];
};

void init(struct Sudoku *sudokup)
{
    int cell = 0;

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            sudokup->boxes[row][col].row = row;
            sudokup->boxes[row][col].col = col;
            sudokup->boxes[row][col].cell = cell;

            sudokup->boxes[row][col].value = 0;
            sudokup->boxes[row][col].is_revealed = 1;

            if (col == 2 || col == 5)
            {
                cell++;
            }
            else if (col == 8)
            {
                cell -= 2;
            }
        }

        if (row == 2 || row == 5)
        {
            cell += 3;
        }
    }
}

void gen(struct Sudoku *sudokup)
{
    void init(struct Box *row)
    {
        for (int i = 0; i < 9; i++)
        {
            row[i].value = i + 1;
        }
    }

    void shuffle(struct Box *row)
    {
        int current_value;
        int exchange_value;
        int random_index;

        for (int i = 0; i < 9; i++)
        {
            random_index = rand() % 9;

            current_value = row[i].value;
            exchange_value = row[random_index].value;

            row[i].value = exchange_value;
            row[random_index].value = current_value;
        }
    }

    int check(struct Sudoku *sudokup , int cri)
    {
        //pri stands for previous row index
        //cri stands for current row index
        //prbi stands for previous row boxes index
        //crbi stands for current row boxes index
        for (int pri = 0; pri < cri; pri++)
        {
            for (int prbi = 0; prbi < 9; prbi++)
            {
                for (int crbi = 0; crbi < 9; crbi++)
                {

                    if (sudokup->boxes[pri][prbi].value == sudokup->boxes[cri][crbi].value)
                    {
                        if (sudokup->boxes[pri][prbi].cell == sudokup->boxes[cri][crbi].cell)
                        {
                            return 0;
                        }
                        else if (sudokup->boxes[pri][prbi].row == sudokup->boxes[cri][crbi].row)
                        {
                            return 0;
                        }
                        else if (sudokup->boxes[pri][prbi].col == sudokup->boxes[cri][crbi].col)
                        {
                            return 0;
                        }
                    }
                }
            }
        }

        return 1;
    }


    int row_i = 0;

    while (row_i < 9)
    {
        if (row_i == 0)
        {
            init(&sudokup->boxes[row_i]);
            shuffle(&sudokup->boxes[row_i]);
            row_i++;
        }
        else
        {
            init(&sudokup->boxes[row_i]);

            while (1)
            {
                shuffle(&sudokup->boxes[row_i]);

                if (check(sudokup , row_i))
                {
                    row_i++;
                    break;
                }
            }
        }
    }
}

void display(struct Sudoku *sudokup)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudokup->boxes[row][col].is_revealed == 1)
            {
                printf("%d  " , sudokup->boxes[row][col].value);
            }
            else
            {
                printf("   ");
            }

            if (col == 2 || col == 5)
            {
                printf("|  ");
            }

        }

        printf("\n");

        if (row == 2 || row == 5)
        {
            printf("-------------------------------\n");
        }
    }
}

void test(struct Sudoku *sudokup)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            printf("row: %d col: %d cell: %d" , row , col , sudokup->boxes[row][col].cell);
            printf("\n");
        }
    }
}


int main()
{
    printf("Loading...\r");

    struct Sudoku sudoku;
    struct Sudoku *sudokup;

    sudokup = &sudoku;

    srand(time(NULL));

    init(sudokup);
    gen(sudokup);
    display(sudokup);

    return 0;
}
