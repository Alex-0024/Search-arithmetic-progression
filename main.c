#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
* In the console window, the user enters integers separated by spaces.
* The program creates a text file 001.txt, that reflects all possible arithmetic progressions of the entered numbers.
*/

int main()
{
    FILE *f;
    int mas[200];
    char str[200];
    int count_mas = 0; // counter read numbers
    int size_progres;
    int tmp;
    int pos_mas = 0; // position for array elements
    int flag_progres; // flag for the presence of a progression, if more than two then there is a progression
    int count_progres = 1; // counter for the number of progressions, how many have been determined
    bool progression = false; // variable for a progression yes or not

    puts("Please enter integer numbers,length string don't more 200 symbol:");
    fgets(str, 200, stdin); // entering a line from the console, the total length of the line is no more than 199 characters, including spaces!!!

    f = fopen("001.txt", "w");

    fprintf(f, "You enter:\n");
    fprintf(f, "%s\n", str);

    fclose(f);

    f = fopen("001.txt", "r");

    fgets(str, strlen("You enter:\n"), f);
    while( fscanf(f, "%d ", mas+count_mas) == 1) // reading numbers into an array
    {
        printf("mas[%d]=%d ", count_mas, mas[count_mas]);
        count_mas++;
    }

    fclose(f);

    f = fopen("001.txt", "a");

    fprintf(f, "Output arithmetic progression:\n");

    fclose(f);

    printf("\ncount_mas=%d\n", count_mas);

    /* bubble sort */

    for (int j = 0; j < count_mas-1; j++)
        for (int k = 0; k < count_mas-j-1; k++)
            if (mas[k] > mas[k+1])
            {
                tmp = mas[k];
                mas[k] = mas[k+1];
                mas[k+1] = tmp;
            }

    for (int j = 0; j < count_mas; j++)
        printf("%d ", mas[j]);
    printf("\n");

    /* sorting an array of numbers for algebraic progression */

    for(int j = 0; j < count_mas-2; j++) // loop with maximum number of iterations to determine all progressions = number of numbers in the array minus two
    {
        size_progres = abs (mas[pos_mas] - mas[pos_mas+1]);
        pos_mas++;
        flag_progres = 1;

        for (int k = pos_mas; k < count_mas-1; k++) // looping through numbers in an array
        {
            if ( abs(mas[k] - mas[k+1]) == size_progres) // if there is a progression between two subsequent numbers
            {
                pos_mas++;
                flag_progres++;
            }
            else
                break;
        }

        if (flag_progres >= 2) // if there is progression
        {
            progression = true;
            for (int s = (pos_mas-flag_progres); s <= pos_mas; s++) // output on display
                printf("num[%d]= %d ", s, mas[s]);
            printf("\n");

            f = fopen("001.txt", "a"); // output in file

            fprintf(f, "%d)", count_progres);
            for (int s = (pos_mas-flag_progres); s <= pos_mas; s++)
                fprintf(f, "%5d", mas[s]);
            fprintf(f, "\n");

            fclose(f);

            count_progres++;
        }
        printf("pos_mas=%d\n", pos_mas);

        if (pos_mas >= count_mas-1) // if all elements of the original array are traversed, then exit the loop
            break;

    }

    if (!progression) // if there are no progressions
        {
            printf("No progression\n");

            f = fopen("001.txt", "a");

            fputs("No progression", f);

            fclose(f);
        }

    return 0;
}

