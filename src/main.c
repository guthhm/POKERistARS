#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "quicklib.h"

#define YES 1
#define NO 0 

typedef struct hand
{
    char card_naipes[10];
    int card_values[6];
}HAND;

int handSort (char array[10][3], int arr_size) {

    int i, j; 
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
            
            if ((array[j]))
            {
                
            }
        }   

        if (swapped == NO) 
            break; 
    } 

}

int main(int argc, char **argv) {

    int loop = 0;
    int *input_int;
    char input[10][3];
    char args[8][3] ={"-c", "-d1", "-d2", "-d3", "-d4", "-dx", "-s1", "-o"};
    HAND hand_input;

    loop = YES;
    for (int i = 0; i < 9; i++)     // for para deteção do modo de execução do programa
    {
        if (strstr(args[i], argv[1]) != NULL)   // Compara a string recebida na linha de comando com as opções válidas
        {
            loop = NO;
            switch (i)
            {
                case 0:
                    //printf("\n-c\n");
                    break;
                
                case 1:
                    //printf("\n-d1\n");
                    break;

                case 2:
                    //printf("\n-d2\n");
                    break;

                case 3:
                    //printf("\n-d3\n");
                    break;

                case 4:
                    //printf("\n-d4\n");
                    break;

                case 5:
                    //printf("\n-dx\n");
                    break;

                case 6:
                    //printf("\n-s1\n");
                    break;

                case 7:
                    //printf("\n-o\n");
                    break;
                
                default:
                    printf("\nO modo de execucao escolhido nao e valido. Por favor tente novamente.\n");
                    exit(-1);
                    break;
            }
        }
        else if (loop != NO)
        {
            printf("\nO modo de execucao escolhido nao e valido. Por favor tente novamente.\n\n");
            exit(-1);
        } 
        
    }

    for (int i = 0; i < argc-2; i++)  // Copia cartas recebidas na linha de comando para input
            strcpy(input[i], argv[i+2]);

    for (int i = 0; i < argc-2; i++) {
        hand_input.card_naipes[i] = input[i][1];
        hand_input.card_values[i] = *(input_int + i);
    }

    input_int = castCtoI(input);

    /* // Imprime valores para conferir

    for (int i = 0; i < argc-2; i++)
        printf("Input: %d\n", *(input_int + i));

    printf("\n\n");
    printf("Mão: ");

    for (int i = 0; i < argc-2; i++)
        printf("%d%c   ", hand_input.card_values[i], hand_input.card_naipes[i]);

    */

    handSort(input, argc-2);

    /*for (int i = 0; i < argc-2; i++)
        printf("Input: %s\n", input[i]);*/
    
    return 0;

}
