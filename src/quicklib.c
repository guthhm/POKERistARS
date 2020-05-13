#include "quicklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int *castCtoI (char array[7][3]) {

    static int int_array[7];
    
    for (int i = 0; i < 7; i++)
    {
        if (array[i][0] <= '9')
            int_array[i] = array[i][0] - '0';
        if (array[i][0] == 'T')
            int_array[i] = 10;
        if (array[i][0] == 'J')
            int_array[i] = 11;
        if (array[i][0] == 'Q')
            int_array[i] = 12;
        if (array[i][0] == 'K')
            int_array[i] = 13;
        if (array[i][0] == 'A')
            int_array[i] = 14;
    }

    return int_array;

}

char *castItoC (int array[10]) {

    static char string_array[10];
    
    for (int i = 0; i < 7; i++)
    {
        if (array[i]<= 9)
            string_array[i] = array[i] + '0';
        if (array[i]== 10)
            string_array[i] = 'T';
        if (array[i]== 11)
            string_array[i] = 'J';
        if (array[i]== 12)
            string_array[i] = 'Q';
        if (array[i] == 13)
            string_array[i] = 'K';
        if (array[i] == 14)
            string_array[i] = 'A';
    }

    return string_array;

}