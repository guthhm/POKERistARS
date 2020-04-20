#include "quicklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int *castCtoI (char array[10][3]) {

    static int int_array[9];

    /*for (int i = 0; i < 10; i++)
        printf("Input: %s\n", array[i]);

    printf("\n");*/

    for (int i = 0; i < 10; i++)
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