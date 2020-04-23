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
    int last_high = 0, first_high, count = 0, streak = 0, aux;

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
            rank[5]++;
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
        }
        if ((j-1 >= 0) && (player.card_values[j-1] == player.card_values[j]) && (mask[1][j+1] == 1))
        {
            mask[1][j] = 1;
            mask[1][j-1] = 1;
        }
        if ((j-1 >= 0) && (player.card_values[j-1] < player.card_values[j] - 1))
            for (int i = 6; i >= j; i--)
                mask[1][i] = 0;
        if ((player.card_values[j-2] == player.card_values[j]))
        {
            mask[1][j-2] = 0;
            mask[1][j-1] = 0;
            j--;
        }
        if ((player.card_values[0] == 2) && (player.card_values[6] == 14))
        {
            mask[1][6] = 1;
            mask[1][0] = 1;
        }
        
    }

    for (int i = 0; i < 7; i++)
    {
        if (rank[5] == 1)
        {
            if ((mask[0][i] == 1) && (mask[1][i] == 1))
            {
                mask[2][i]++;
                last_high = i;
            }            
        } else if ((rank[5] == 0) &&  (mask[1][i] == 1))
        {
            streak++;
            last_high = i;
        }
    }

    if (streak >= 5)
    {
        rank[4]++;
    }
    
    if ((rank[5] == 1) && (rank[4] == 1) && (player.card_values[last_high] == 14))
    {
        //printf("\n\nROYAL FLUSH\n\n");
        rank[9]++;
    }

    if ((rank[5] == 1) && (rank[4] == 1))
    {
        //printf("\n\nStraight Flush\n\n");
        rank[8]++;
    }

    aux = 4;

    for (int i = 6; i >= 0; i--)
        if (mask[2][i] == 1)
        {
            player.best_combination[aux] = i;
            aux--;
        }

    for (int i = 6; i >= 0; i--)
    {
        if ((i >= 3) && (player.card_values[i] == player.card_values[i-3]))
        {
                rank[7]++;
                last_high = i;
                break;
        }
        if ((i >= 2)  && (player.card_values[i] == player.card_values[i-2]) && (rank[7] == NO))
        {
                rank[3]++;
                first_high = i;
        }
        if ((i >= 1) && (player.card_values[i] == player.card_values[i-1]) && !(player.card_values[i] == player.card_values[i-2]))
        {
                rank[1]++;
                if (rank[1] == 1)
                    last_high = i;
                if (rank[1] == 2)
                    first_high = i;
                
                if (rank[1] == 2)
                {
                    rank[2]++;
                    break;
                }
        }
        if ((rank[3] == YES) && (rank[1] == YES))
        {
            for (int j = 2; j >= 0; j--)
                player.best_combination[j+2] = first_high - (2 - j);
            for (int j = 1; j >= 0; j--)
                player.best_combination[j] = last_high - (1 - j);
            rank[6]++;
            break;
        }
        
    }

    printf("\n\nFirst high: %d\nLast high: %d\n", first_high, last_high);
            

    /* Impressão dos dados na tela */

    printf("\nBest combination array: "); 
    for (int i = 0; i < 5; i++)
        printf("%d  ", player.best_combination[i]);
    printf("\n");
    
    for (int i = 0; i < 3; i++)
    {
        printf("\nMask %d: ", i+1);
        for (int j = 0; j < 7; j++)
            printf("%d  ", mask[i][j]);
        printf("\n");
    }

    printf("\n");

    /*

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
    */

    printf("\n");
    printf("Rank:\n");

    for (int i = 0; i < 10; i++)
        printf("(%d) %d  ",i, rank[i]);

    printf("\n\n");

    

    return result;

}

