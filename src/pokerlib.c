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

    /*for (int i = 0; i < hand_size; i++)
        printf("%s  ", player_hands[i]);
    
    printf("\n"); */

    return player_hands;

}

HAND handIdentifier (HAND player, int hand_size) {

    HAND result;

    int naipes[4] = {0}, mask[3][7] = {0}, rank[10] = {0};
    int last_high = 0, first_high, count = 0, streak = 0, aux;

    for (int i = 0; i < hand_size; i++)  // Conta qual naipe tem maior ocorrência
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


    for (int i = 3; i >= 0; i--) // Verifica se algum naipe possui 5 ocorrências, o que configura um Flush
        if (naipes[i] >= 5)
        {
            rank[5]++;
            for (int j = 0; j < hand_size; j++)
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


    for (int j = hand_size-1; j >= 0; j--)  // Verifica, de 2 em 2 as condições de Straight
    {
        if ((j-1 >= 0) && (player.card_values[j-1] + 1 == player.card_values[j]))
            mask[1][j] = 1;
        /*if ((j-1 >= 0) && (player.card_values[j-1] == player.card_values[j]) && (mask[1][j+1] == 1))
        {
            mask[1][j] = 1;
            mask[1][j-1] = 1;
        }*/
        if ((j-1 >= 0) && (player.card_values[j-1] < player.card_values[j] - 1))
        {
            mask[1][j] = 0;
            mask[1][j-1] = 0;
        }
        if ((j-1 == 0) && (player.card_values[j] + 1 == player.card_values[j+1]))
            mask[1][j] = 1;
        if ((j-1 == 0) && (player.card_values[j-1] + 1 == player.card_values[j]))
            mask[1][j-1] = 1;
        
        if ((player.card_values[j-2] == player.card_values[j]))
        {
            mask[1][j-2] = 0;
            mask[1][j-1] = 0;
            mask[1][j] = 0;
            j--;
        }
        if ((player.card_values[0] == 2) && (player.card_values[hand_size-1] == 14))
        {
            mask[1][hand_size-1] = 1;
            mask[1][0] = 1;
        }
    }


    for (int i = 0; i < hand_size; i++)  // Compara as 2 máscaras em busca de um Straight Flush ou apenas Straight
    {
        if (rank[5] == 1)
        {
            if ((mask[0][i] == 1) && (mask[1][i] == 1))
            {
                mask[2][i]++;
                last_high = i;
            }            
        } 
        if ((mask[1][i] == 1))
            last_high = i;
    }

    for (int i = hand_size-1; i >= 0; i--)
    {
        if (mask[1][i] == 1)
        {
            if (player.card_values[i] == player.card_values[i-1] + 1)
            {
                printf("\nI: %d", i);
                streak++;
            } else if ((player.card_values[i] == player.card_values[i+1] - 1) )
            {
                printf("\nI: %d", i);
                streak = 0;
            }
            if (streak == 5)
            {
                break;
            }
            
            
        }
                 
    }
        

    if (streak >= 5)
        rank[4]++;
        //Straight
    
    if ((rank[5] == 1) && (rank[4] == 1) && (player.card_values[last_high] == 14))
        rank[9]++; 
        // ROYAL FLUSH

    if ((rank[5] == 1) && (rank[4] == 1))
        rank[8]++;
        // Straight Flush


    for (int i = hand_size-1; i >= 0; i--)
    {
        if ((i >= 3) && (player.card_values[i] == player.card_values[i-3]))  // Verifica 4 of a Kind
        {
                rank[7]++;
                last_high = i;
                break;
        }
        if ((i >= 2)  && (player.card_values[i] == player.card_values[i-2]) && (rank[7] == NO))  // Verifica 3 of a Kind
        {
                rank[3]++;
                first_high = i;
        }
        if ((i >= 1) && (player.card_values[i] == player.card_values[i-1]) && !(player.card_values[i] == player.card_values[i-2]) && !(player.card_values[i+1] == player.card_values[i-1]))  // Verifica Pair ou 2-Pair
        {
            rank[1]++;
            if (rank[1] == 1)
                last_high = i;
            if (rank[1] == 2 && rank[3] == NO)
                first_high = i;
                
            if (rank[1] == 2)
            {
                rank[2]++;
                break;
            }
        }
        if ((rank[3] == YES) && (rank[1] == YES))  // Verifica Full House
        {
            rank[6]++;
            break;
        }
    }


    for (int i = 0; i < hand_size; i++)
    {
        result.card_values[i] = player.card_values[i];  // Copia cartas para result
        result.card_naipes[i] = player.card_naipes[i];
    }

    for (int i = 9; i >=0; i--)
    {
        if ((rank[i] == 1) || (rank[i] == 2))
        {
            switch (i)
            {
            case 9:  // Royal Flush

                for (int j = 0; j < hand_size; j++)
                    if (i >= 2)
                        result.best_combination[j-2] = j;  // Copia para result a posição das melhores cartas (no caso as últimas)
                
                break;

            case 8:  // Straight Flush

                for (int j = 0; j < hand_size; j++)
                    if (i >= 2)
                        result.best_combination[j-2] = j;  // Copia para result a posição das melhores cartas (no caso as últimas)

                break;

            case 7:  // 4 of a Kind

                for (int j = 0; j < 4; j++)
                    result.best_combination[j] = last_high-(3-j);  // Copia para result a posição das melhores cartas (no caso as últimas)
                if (last_high == hand_size-1)
                    result.best_combination[4] = 2;  // Guarda a posição da maior carta fora da combinação
                if (last_high < hand_size-1)
                    result.best_combination[4] = hand_size-1;

                break;

            case 6:  // Full House

                for (int j = 2; j >= 0; j--)
                    result.best_combination[j+2] = first_high - (2 - j);
                for (int j = 1; j >= 0; j--)
                    result.best_combination[j] = last_high - (1 - j);
                break;

            case 5:  // Flush

                aux = 4;
                for (int j = hand_size-1; j >= 0; j--)
                    if (mask[0][j] == 1)
                    {
                        result.best_combination[aux] = j;
                        aux--;
                    }
                break;

            case 4:  // Straight

                aux = 4;
                for (int j = hand_size-1; j >= 0; j--)
                    if (mask[1][j] == 1)
                    {
                        if (result.card_values[j] == 14)
                            result.best_combination[0] = j;
                        else
                        {
                            result.best_combination[aux] = j;
                            if (result.best_combination[0] != 14)
                                aux--;
                        }
                    }
                break;

            case 3:  // 3 of a Kind

                for (int j = 2; j >= 0; j--)
                    result.best_combination[j] = first_high - (2 - j);
                if (first_high == hand_size-1){
                    result.best_combination[4] = 3;
                    result.best_combination[3] = 2;
                }
                if (first_high == hand_size-2){
                    result.best_combination[4] = hand_size-1;
                    result.best_combination[3] = hand_size-4;
                }
                if (first_high < 4){
                    result.best_combination[4] = hand_size-1;
                    result.best_combination[3] = hand_size-2;
                }
                break;


            case 2:  // 2 Pairs

                for (int j = 1; j >= 0; j--)
                {
                    result.best_combination[j] = last_high - (1 - j);
                    result.best_combination[j+2] = first_high - (1 - j);
                }
                if ((last_high == hand_size-1) && (first_high == hand_size-3))
                    result.best_combination[4] = hand_size-5;
                if ((last_high == hand_size-1) && (first_high != hand_size-3))
                    result.best_combination[4] = hand_size-3;
                if (last_high != hand_size-1)
                    result.best_combination[4] = hand_size-1;
                
                break;

            case 1:  // Pair

                for (int j = 1; j >= 0; j--)
                    result.best_combination[j] = last_high - (1 - j);
                if (last_high ==hand_size-1)
                    for (int j = 4; j >= 2; j--)
                        result.best_combination[j] = (hand_size-3)-(4-j);
                if (last_high == (hand_size-2))
                    for (int j = 4; j >= 2; j--)
                        result.best_combination[j] = (hand_size-2)-(4-j);
                if (last_high <=(hand_size-3))
                    for (int j = 4; j >= 2; j--)
                        result.best_combination[j] = (hand_size-1)-(4-j);
                break;

            case 0:  // High Card

                for (int j = hand_size-1; j >= 2; j--)
                    result.best_combination[j-2] = j;
                break;
            
            default:
                exit(-1);
                break;
            }

            result.combination = i;  // Guarda a posição do rank
            break;
        }
    }

    /* Impressão dos dados na tela *//*

    printf("\n\nFirst high: %d\nLast high: %d\n", first_high, last_high);

    printf("\nBest combination array: "); 
    for (int i = 0; i < 5; i++)
        printf("%d  ", result.best_combination[i]);
    printf("\n");*/
    
    for (int i = 0; i < 3; i++)
    {
        printf("\nMask %d: ", i+1);
        for (int j = 0; j < hand_size; j++)
            printf("%d  ", mask[i][j]);
        printf("\n");
    }
    /*
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
    }*/

    printf("\n");
    printf("Rank:\n");

    for (int i = 0; i < 10; i++)
        printf("(%d) %d  ",i, rank[i]);

    printf("\n\n");

    

    return result;

}

