#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "quicklib.h"
#include "pokerlib.h"

#define YES 1
#define NO 0 

int handSort (char array[6][3], int arr_size) {

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

            if ((array[j][0] == 'J') && (array[j+1][0] == 'T') || (array[j][0] == 'Q') && (array[j+1][0] == 'T'))
            {
                strcpy(temp, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], temp);
                swapped = YES;
            }
            
            if ((array[j][0] == 'K') && (array[j+1][0] == 'Q') || (array[j][0] == 'K') && (array[j+1][0] == 'T'))
            {
                strcpy(temp, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], temp);
                swapped = YES;
            }

            if ((array[j][0] == 'A') && (array[j+1][0] == 'T') || (array[j][0] == 'A') && (array[j+1][0] == 'J') || (array[j][0] == 'A') && (array[j+1][0] == 'Q') || (array[j][0] == 'A') && (array[j+1][0] == 'K'))
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

int main(int argc, char **argv) {

    int loop = 0;
    int *input_int;
    char *player_hands;
    char input[10][3], players[1][7][3];
    char args[8][3] = {"-c", "-d1", "-d2", "-d3", "-d4", "-dx", "-s1", "-o"};
    HAND hand_input[2];

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

    //printf("\n%d\n", argc);

    /*if ((argc != 7 || argc != 9 || argc != 11 || argc != 12) && (strstr("-c", argv[1]) != NULL))
    {
        printf("\nO numero de cartas inserido não é válido. Por favor tente com um numero dentro dos parametros.\n\n");
        exit(-1);
    } */

    for (int i = 0; i < argc-2; i++)  // Copia cartas recebidas na linha de comando para input
            strcpy(input[i], argv[i+2]);

    if (argc == 11) {   // Separa as mãos dos jogadores 

        for (int i = 0; i < 2; i++) { // i = 0 é jogador 1 ; i = 1 é jogador 2 

            player_hands = divideHands(input, i);
            int l=0;
        
            for (int j = 0; j < 7; j++)
                for (int k = 0; k < 3; k++)
                    if (*player_hands != '\0'){
                    players[i][j][k] = *(player_hands+l);
                    l++;
                    //printf("\nL: %d\n", l);
                    }
            
            /*for (int j = 0; j < 7; j++)
                printf("%s ", players[i][j]);

            printf("\n");*/
            
        }
    }

    /*for (int i = 0; i < 2; i++) {
        printf("\nPlayer %d:", i+1);
        for (int j = 0; j < 7; j++)
            printf("%s  ", players[i][j]);
        printf("\n");
    }*/

    handSort(players[0], 7);
    handSort(players[1], 7);

    /*printf("\nMão ordenada:\n");

    for (int i = 0; i < 2; i++) {
        printf("\nPlayer %d:", i+1);
        for (int j = 0; j < 7; j++)
            printf("%s  ", players[i][j]);
        printf("\n");
    }

    for (int i = 0; i < 2; i++) {
        printf("\nI: %d\n", i);
        for (int j = 0; j < 21; j++)
            printf("%c..", *(player_hands+j));

    printf("\n");
    }
    */

    printf("\n");

    for (int i = 0; i < 2; i++) {
        input_int = castCtoI(players[i]);
        for (int j = 0; j < 7; j++) {
            hand_input[i].card_values[j] = *(input_int + j);
            hand_input[i].card_naipes[j] = players[i][j][1];
        }
    }
    

    // Imprime valores para conferir

    //printf("\n\n");
    printf("\tMãos: \n");

    for (int i = 0; i < 2; i++) {
        printf("\nJogador %d: ", i+1);
        for (int j = 0; j < 7; j++)
            printf("%d%c   ", hand_input[i].card_values[j], hand_input[i].card_naipes[j]);
    }

    printf("\n\n");

    handIdentifier(hand_input[1]);
    
    return 0;

}
