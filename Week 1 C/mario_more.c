#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //get the height from user
    int height;
    do
    {
        height = get_int("Height:");
    }
    //limit the input
    while
    (
        (height < 1) || (height > 8)
    );
    int row;
    int i;
    //loop for each row
    for (row = 1; row <= height; row++)
    {
        //the front space
        for (i = 1; i <= (height - row); i++)
        {
            printf(" ");
        }
        //the blcok
        for (i = 1; i <= row; i++)
        {
            printf("#");
        }
        //the middle space
        printf("  ");
        //the end block
        for (i = 1; i <= row; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}