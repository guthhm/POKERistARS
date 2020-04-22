#include "quicklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int *castCtoI (char array[7][3]) {

    static int int_array[7];
    
    /*
    printf("\nAntes de fazer cast:\n");

    for (int i = 0; i < 7; i++)
        printf("%s  ", array[i]);

    printf("\n");
    */

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
    /*

    printf("\nDepois do cast:\n");

    for (int i = 0; i < 7; i++)
        printf("%d  ", int_array[i]);

    printf("\n\n");

    */
    
    return int_array;
}

char *castItoC (int array[10]) {

    // Corpo da função

    return 0;

}