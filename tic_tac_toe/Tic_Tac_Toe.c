#include <stdio.h>
#include <stdlib.h>

void reset(char **playground)
{
    int k = 1;
    for (int i = 0; i < 3; i++)
    {
        playground[i] = (char *)malloc(3 * sizeof(char));
        for (int j = 0; j < 3; j++)
        {
            playground[i][j] = k + '0';
            k++;
        }
    }
}

void print(char **playground)
{
    fflush(stdout);
    system("clear");
    printf("\n\t\033[1;34m\033[1m* Tic-Tac-Toe *\033[0m \033[0m\n\n");
    printf("\t-------------\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\t");
        for (int j = 0; j < 3; j++)
        {
            if(playground[i][j]== 'X' || playground[i][j]== 'O'){
                char color = '2';
                if(playground[i][j]== 'X')  color = '1';
                printf("|\033[3%cm \033[1m%c\033[0m \033[0m",color, playground[i][j]);
            }
            else{
                printf("| %c ", playground[i][j]);
            }
            
        }
        printf("|\n\t-------------\n");
    }
}

int result(char **playground, char player)
{

    // checking rows
    for (int i = 0; i < 3; i++)
    {
        int flag = 1;
        for (int j = 0; j < 3; j++)
        {
            if (playground[i][j] != player)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            return 1;
        }
    }

    // checking columns
    for (int i = 0; i < 3; i++)
    {
        int flag = 1;
        for (int j = 0; j < 3; j++)
        {
            if (playground[j][i] != player)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            return 1;
        }
    }

    // checking diagonals
    if (playground[1][1] != player)
    {
        return 0;
    }

    int i = 0, j = 0, flag = 1; /* \ */
    while (i < 3 && j < 3)
    {
        if (playground[i][j] != player)
        {
            flag = 0;
        }
        i++;
        j++;
    }
    if (flag)
        return 1;

    i = 2, j = 0, flag = 1; /* / */
    while (i >= 0 && j < 3)
    {
        if (playground[i][j] != player)
        {
            flag = 0;
        }
        i--;
        j++;
    }
    if (flag)
        return 1;

    return 0; // continue playing or draw
}


void play_game(char** playground)
{
    reset(playground);
    print(playground);
    int play = 9;
    while (play--)
    {
        char player = 'X';
        if (play % 2 == 0)
        {
            player = 'O';
        }

        int choosen = 1;

        while (choosen)
        {
            int choice, i, j;
            printf("%d) Player %c Choose your block : ", 9 - play, player);
            // scanf(" %d",&choice);
            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input. Please enter an integer.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
                continue;
            }
            if (choice < 1 || choice > 9)
            {
                printf("Choose only between 1 and 9 \n");
            }
            else
            {
                int occupied = 1;
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (playground[i][j] == (choice + '0'))
                        {
                            occupied = 0;
                            playground[i][j] = player;
                            choosen = 0;
                            break;
                        }
                    }
                    if (!occupied)
                    {
                        print(playground);
                        break;
                    }
                }
                if (occupied)
                {
                    printf("Already Occupied Choose Another !!\n");
                }
            }
        }
        if (play <= 5)
        {
            int res = result(playground, player);
            if (res)
            {
                char color = '2';
                if(player == 'X')   color = '1';
                printf("\033[3%cm \033[1m Winner is %c ! \033[0m \033[0m\n",color, player);
                break;
            }
            else if (play == 0)
            {
                printf("Match Draw ! \n");
            }
        }
    }
}


int main()
{

    char **playground = (char **)malloc(3 * sizeof(char *));

    int exit = 1;

    while (exit)
    {
        play_game(playground);
        char ng;
        printf("New Game (Y/n) : ");
        scanf(" %c", &ng);
        if (ng == 'Y' || ng == 'y')
        {
            // system("clear");
        }
        else
        {
            exit = 0;
        }
    }
}