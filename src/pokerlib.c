#include "pokerlib.h"
#include "quicklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *divideHands (char cards[10][3], int player) {

    static char player_hands[6][3];

    //printf("\nPlayer: %d\n", player);

    if (player == 0)
        for (int i = 0; i < 10; i++) {// Copia elementos do input original para a mão do jogador
            if (i != 2 && i != 3)// Excepto elementos 2 e 3 por pertencerem ao 2º jogador.
                strcpy(player_hands[i], cards[i]);
            if (i > 3)
                strcpy(player_hands[i-2], cards[i]); // Volta 2 elementos do array pois a mão do jogador é menor que o input
        }

    if (player == 1)
        for (int i = 2; i < 10; i++) // Copia elementos do input original a aprtir da 2ª posição do array
            strcpy(player_hands[i-2], cards[i]);

    /*for (int i = 0; i < 7; i++)
        printf("%s  ", player_hands[i]);
    
    printf("\n"); */

    return player_hands;

}

HAND handIdentifier (HAND player) {

    HAND result;

    int naipes[4] = {0}, mask[3][7] = {0}, rank[10] = {0};
    int sequencia = 0, temp = 0, aux;

    for (int i = 0; i < 7; i++)
    {
        if (player.card_naipes[i] == 'C')
            naipes[0]++;
        if (player.card_naipes[i] == 'E')
            naipes[1]++;
        if (player.card_naipes[i] == 'O')
            naipes[2]++;
        if (player.card_naipes[i] == 'P')
            naipes[3]++;
    }

    for (int i = 3; i >= 0; i--)
        if (naipes[i] >= 5)
        {
            rank[4]++;
            for (int j = 0; j < 7; j++)
            {
                if ((player.card_naipes[j] == 'C')  && (i == 0))
                    mask[0][j]++;
                if ((player.card_naipes[j] == 'E') && (i == 1))
                    mask[0][j]++;
                if ((player.card_naipes[j] == 'O') && (i == 2))
                    mask[0][j]++;
                if ((player.card_naipes[j] == 'P') && (i == 3))
                    mask[0][j]++;
            }
        }
    

    for (int j = 6; j >= 0; j--) 
    {
        if ((j-1 >= 0) && (player.card_values[j-1] + 1 == player.card_values[j]))
        {
            mask[1][j] = 1;
            mask[1][j-1] = 1;
        }
        if ((j-1 >= 0) && (player.card_values[j-1] == player.card_values[j]))
        {
            mask[1][j] = 1;
            mask[1][j-1] = 1;
        }
    }

    for (int i = 0; i < 7; i++)
        if ((mask[0][i] == 1) && (mask[1][i] == 1))
        {
            mask[2][i]++;
            temp++;
            sequencia = i;
        }

    printf("\ntemp: %d\n", temp);
    printf("\nsequencia: %d\n", sequencia);
            
    if ((temp >= 5) && player.card_values[sequencia] == 14)
    {
        printf("\n\nROYAL FUCKING FLUSH\n\n");
    }

    if (temp >= 5)
    {
        printf("\n\nStraight Flush\n\n");
    }
    
    aux = 4;

    for (int i = 6; i >= 0; i--)
        if (mask[2][i] == 1)
        {
            player.best_combination[aux] = i;
            aux--;
        }

    printf("\nBest combination array: "); 
    for (int i = 0; i < 5; i++)
    {
        printf("%d  ", player.best_combination[i]);
         
    }
    printf("\n");
    
    for (int i = 0; i < 3; i++)
    {
        printf("\nMask %d: ", i+1);
        for (int j = 0; j < 7; j++)
        {
            printf("%d  ", mask[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < 4; i++)
    {
        if (i==0)
            printf("Copas: %d", naipes[i]);
        if (i==1)
            printf("Espadas: %d", naipes[i]);
        if (i==2)
            printf("Ouros: %d", naipes[i]);
        if (i==3)
            printf("Paus: %d", naipes[i]);

        printf("\n");
    }

    printf("\n");

    return result;

}

