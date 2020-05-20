#include "quicklib.h"
#include "pokerlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int handSort (char array[7][3], int arr_size) {

    char temp[3];
    bool swapped; 

    for (int i = 0; i < arr_size-1; i++) 
    { 

        swapped = false; 
        for (int j = 0; j < arr_size-i-1; j++) 
        { 
            if (array[j][0] > array[j+1][0]) 
            { 
                strcpy(temp, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], temp);
                swapped = YES; 
            } 

            if (((array[j][0] == 'J') && (array[j+1][0] == 'T')) || ((array[j][0] == 'Q') && (array[j+1][0] == 'T')))
            {
                strcpy(temp, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], temp);
                swapped = YES;
            }
            
            if (((array[j][0] == 'K') && (array[j+1][0] == 'Q')) || ((array[j][0] == 'K') && (array[j+1][0] == 'T')))
            {
                strcpy(temp, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], temp);
                swapped = YES;
            }

            if (((array[j][0] == 'A') && (array[j+1][0] == 'T')) || ((array[j][0] == 'A') && (array[j+1][0] == 'J')) || ((array[j][0] == 'A') && (array[j+1][0] == 'Q')) || ((array[j][0] == 'A') && (array[j+1][0] == 'K')))
            {
                strcpy(temp, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], temp);
                swapped = YES;
            }
            
        }   

        if (swapped == NO) 
            break; 
    } 

    return 0;

}

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