#include "pokerlib.h"
#include "quicklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *divideHands(char cards[10][3], int player)
{

    static char player_hands[6][3];

    //printf("\nPlayer: %d\n", player);

    if (player == 0)
        for (int i = 0; i < 10; i++)
        {                         // Copia elementos do input original para a mão do jogador
            if (i != 2 && i != 3) // Excepto elementos 2 e 3 por pertencerem ao 2º jogador.
                strcpy(player_hands[i], cards[i]);
            if (i > 3)
                strcpy(player_hands[i - 2], cards[i]); // Volta 2 elementos do array pois a mão do jogador é menor que o input
        }

    if (player == 1)
        for (int i = 2; i < 10; i++) // Copia elementos do input original a aprtir da 2ª posição do array
            strcpy(player_hands[i - 2], cards[i]);

    /*for (int i = 0; i < hand_size; i++)
        printf("%s  ", player_hands[i]);
    
    printf("\n"); */

    return player_hands;
}

void errorCheck(char input[10][3], int input_size)
{

    int valid = 0;
    const char valid_numbers[14] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char valid_naipes[4] = {'C', 'E', 'O', 'P'};

    for (int i = 0; i < input_size; i++) // Verifica Naipes ou Cartas ilegais
    {
        valid = NO;
        for (int j = 0; j < 14; j++)
            if (valid_numbers[j] == input[i][0])
                valid = YES;

        if (valid == NO)
        {
            printf("-1\n");
            exit(-1);
        }

        valid = NO;
        for (int j = 0; j < 4; j++)
            if (valid_naipes[j] == input[i][1])
                valid = YES;

        if (valid == NO)
        {
            printf("-1\n");
            exit(-1);
        }

        /*if (strlen >= 3)
        {
            printf("-1\n");
            exit(-1);
        }*/
    }

    /*for (int i = 0; i < input_size; i++)
    {
        valid == YES;
        for (int j = 0; j < input_size; j++)
        {
            if ((input[i][0] == input[j][0]) && (input[i][1] == input[j][1]))
                valid = NO;            
        }

        if (valid == NO)
        {
            printf("-1\n");
            exit(-1);
        }
    }*/

    //Cartas não podem repetir na mesma mão de 5, 7 e 9
    //Em 10 cartas, as 2 primeiras não podem repetir
}

HAND handIdentifier(HAND player, int hand_size)
{

    HAND result;

    int naipes[4] = {0}, mask[7] = {0}, rank[10] = {0};
    int last_high = 0, first_high = 0, streak = 0, aux = 0;

    for (int i = 0; i < hand_size; i++) // Conta qual naipe tem maior ocorrência
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
                if ((player.card_naipes[j] == 'C') && (i == 0))
                    mask[j]++;
                if ((player.card_naipes[j] == 'E') && (i == 1))
                    mask[j]++;
                if ((player.card_naipes[j] == 'O') && (i == 2))
                    mask[j]++;
                if ((player.card_naipes[j] == 'P') && (i == 3))
                    mask[j]++;
            }
        }

    aux = 0;
    for (int i = hand_size - 1; i >= 0; i--)
    {

        int j = 1;

        if (player.card_values[i] == player.card_values[i - 1] + 1)
            streak++;

        if (mask[i] == 1)
        {
            while (mask[i - j] == 0)
                j++;

            if (player.card_values[i] == player.card_values[i - j] + 1)
                aux++;

            if (i == (hand_size - 1))
                last_high = i;
        }

        if ((player.card_values[0] == 2) && (player.card_values[hand_size - 1] == 14) && (streak >= 3) && (i < 2))
            streak++;

        /*if (player.card_values[i] == player.card_values[i-1])  // Se i = i-1 streak não altera
           streak = streak;
       */
        if (player.card_values[i] > player.card_values[i - 1] + 1)
            streak = 0;

        if ((streak > 0) && !(((player.card_values[0] == 2) && (player.card_values[hand_size - 1] == 14)) || (player.card_values[i] == player.card_values[i - 1])))
        {
            result.best_combination[streak - 1] = i;
            if (streak == 4)
                result.best_combination[4] = i - 1;
        }
        else if ((streak > 0) && ((player.card_values[0] == 2) && (player.card_values[hand_size - 1] == 14)))
        {
            result.best_combination[streak] = i;
            result.best_combination[0] = hand_size - 1;
        }
        else if (streak == 0)
            for (int k = 0; k < 5; k++)
                result.best_combination[k] = 0;

        if (streak == 4)
        {
            if (aux == 4)
            {
                if (player.card_values[last_high] == 14)
                {
                    rank[9]++;
                    break;
                }
                else
                {
                    rank[8]++;
                    break;
                }
            }

            rank[4]++; //Straight
            break;
        }
    }

    for (int i = hand_size - 1; i >= 0; i--)
    {
        if ((i >= 3) && (player.card_values[i] == player.card_values[i - 3])) // Verifica 4 of a Kind
        {
            rank[7]++;
            last_high = i;
            break;
        }
        if ((i >= 2) && (player.card_values[i] == player.card_values[i - 2]) && (rank[7] == NO)) // Verifica 3 of a Kind
        {
            rank[3]++;
            first_high = i;
        }
        if ((i >= 1) && (player.card_values[i] == player.card_values[i - 1]) && !(player.card_values[i] == player.card_values[i - 2]) && !(player.card_values[i + 1] == player.card_values[i - 1])) // Verifica Pair ou 2-Pair
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
        if (((rank[3] == 1) && (rank[1] >= 1)) || (rank[3] == 2)) // Verifica Full House
        {
            rank[6]++;
            break;
        }
    }

    for (int i = 0; i < hand_size; i++)
    {
        result.card_values[i] = player.card_values[i]; // Copia cartas para result
        result.card_naipes[i] = player.card_naipes[i];
    }

    aux = 0;
    for (int i = 9; i >= 0; i--)
    {
        if (rank[i] != 1 && rank[i] != 2)
            aux++;
        if (aux == 8)
            rank[0]++;
    }

    for (int i = 9; i >= 0; i--)
    {
        if ((rank[i] == 1) || (rank[i] == 2))
        {
            switch (i)
            {
            case 9: // Royal Flush

                for (int k = 4; k >= 0; k--)
                    for (int j = 6; j >= 0; j--)
                        if (mask[j] == 1)
                        {
                            result.best_combination[k] = i; // Copia para result a posição das melhores cartas (no caso as últimas)
                            break;
                        }
                break;

            case 8: // Straight Flush

                for (int k = 4; k >= 0; k--)
                    for (int j = 6; j >= 0; j--)
                        if ((mask[j]) == 1)
                        {
                            result.best_combination[k] = i; // Copia para result a posição das melhores cartas (no caso as últimas)
                            break;
                        }
                break;

            case 7: // 4 of a Kind

                for (int j = 0; j < 4; j++)
                    result.best_combination[j] = last_high - (3 - j); // Copia para result a posição das melhores cartas (no caso as últimas)
                if (last_high == hand_size - 1)
                    result.best_combination[4] = 2; // Guarda a posição da maior carta fora da combinação
                if (last_high < hand_size - 1)
                    result.best_combination[4] = hand_size - 1;

                break;

            case 6: // Full House

                for (int j = 2; j >= 0; j--)
                    result.best_combination[j + 2] = first_high - (2 - j);
                for (int j = 1; j >= 0; j--)
                    result.best_combination[j] = last_high - (1 - j);
                break;

            case 5: // Flush

                aux = 4;
                for (int j = hand_size - 1; j >= 0; j--)
                    if (mask[j] == 1)
                    {
                        result.best_combination[aux] = j;
                        aux--;
                    }
                break;

            case 4: // Straight

                break;

            case 3: // 3 of a Kind

                for (int j = 2; j >= 0; j--)
                    result.best_combination[j] = first_high - (2 - j);

                if (first_high == hand_size - 1)
                {
                    result.best_combination[4] = 3;
                    result.best_combination[3] = 2;
                }
                else if (first_high == hand_size - 2)
                {
                    result.best_combination[4] = hand_size - 1;
                    result.best_combination[3] = first_high - 3;
                }
                else if (first_high <= hand_size - 3)
                {
                    result.best_combination[4] = hand_size - 1;
                    result.best_combination[3] = hand_size - 2;
                }

                break;

            case 2: // 2 Pairs

                for (int j = 1; j >= 0; j--)
                {
                    result.best_combination[j] = last_high - (1 - j);
                    result.best_combination[j + 2] = first_high - (1 - j);
                }
                if ((last_high == hand_size - 1) && (first_high == hand_size - 3))
                    result.best_combination[4] = hand_size - 5;
                if ((last_high == hand_size - 1) && (first_high != hand_size - 3))
                    result.best_combination[4] = hand_size - 3;
                if (last_high != hand_size - 1)
                    result.best_combination[4] = hand_size - 1;

                break;

            case 1: // Pair

                for (int j = 1; j >= 0; j--)
                    result.best_combination[j] = last_high - (1 - j);

                if (last_high == hand_size - 1)
                    for (int j = 4; j >= 2; j--)
                        result.best_combination[j] = (hand_size - 3) - (4 - j);
                else if (last_high == (hand_size - 2))
                {
                    result.best_combination[2] = last_high - 3;
                    result.best_combination[3] = last_high - 2;
                    result.best_combination[4] = hand_size - 1;
                }
                else if (last_high == (hand_size - 3))
                {
                    for (int j = 4; j >= 3; j--)
                        result.best_combination[j] = (hand_size - 1) - (4 - j);
                    result.best_combination[2] = last_high - 2;
                }
                else if (last_high <= hand_size - 4)
                    for (int j = 4; j >= 2; j--)
                        result.best_combination[j] = (hand_size - 1) - (4 - j);

                break;

            case 0: // High Card

                if (hand_size == 5)
                    for (int j = hand_size - 1; j >= 0; j--)
                        result.best_combination[j] = j;

                if (hand_size == 7)
                    for (int j = hand_size - 1; j >= 2; j--)
                        result.best_combination[j - 2] = j;

                break;

            default:
                exit(-1);
                break;
            }

            result.combination = i; // Guarda a posição do rank
            break;
        }
    }

    /* Impressão dos dados na tela */ /*

    printf("\nMão:\n");
    for (int i = 0; i < hand_size; i++)
    {
        printf("%d%c  ", player.card_values[i], player.card_naipes[i]);
    }
    printf("\n");
    
    printf("\n\nFirst high: %d\nLast high: %d\n", first_high, last_high);

    printf("\nBest combination array: \n"); 
    for (int i = 0; i < 5; i++)
        printf("%d  ", result.best_combination[i]);
    printf("\n");
    for (int i = 0; i < 5; i++)
        printf("%d%c  ", result.card_values[result.best_combination[i]], result.card_naipes[result.best_combination[i]]);

    printf("\n");
    printf("\nMask: ");
    for (int j = 0; j < hand_size; j++)
        printf("%d  ", mask[j]);
    printf("\n");

    printf("\nHand Size: %d\n\n", hand_size);

    printf("Copas: %d\n", naipes[0]);
    printf("Espadas: %d\n", naipes[1]);
    printf("Ouros: %d\n", naipes[2]);
    printf("Paus: %d\n\n", naipes[3]);

    printf("Rank:\n");
    for (int i = 0; i < 10; i++)
        printf("(%d) %d  ",i, rank[i]);
        
    printf("\n\n");*/

    return result;
}

PLAYER doContest(HAND player_hand[8], PLAYER contestant[8])
{
    char *stream;
    char temp_hand[5][3], winner[5][3];
    short position = 0, max = 4, winner_num;
    int rank[8] = {0};
    PLAYER res;

    for (int i = 0; i < 8; i++)
        for (int j = i+1; j < 8; j++)
            if ((contestant[i].inactive == NO) && (contestant[j].inactive == NO))
            {
                if (player_hand[i].combination == player_hand[j].combination)
                {
                    while ((player_hand[i].card_values[player_hand[i].best_combination[max]] == player_hand[j].card_values[player_hand[i].best_combination[max]]) && (max >= 0))
                        max--;

                    if (max == 0)
                    {
                        if (player_hand[i].card_naipes[player_hand[i].best_combination[4]] == player_hand[j].card_naipes[player_hand[j].best_combination[4]])
                        {
                            rank[j]++;
                            rank[i]++;
                        }
                        else if (player_hand[i].card_naipes[player_hand[i].best_combination[4]] > player_hand[j].card_naipes[player_hand[j].best_combination[4]])
                            rank[i]++;
                        else if (player_hand[i].card_naipes[player_hand[i].best_combination[4]] < player_hand[j].card_naipes[player_hand[j].best_combination[4]])
                            rank[j]++;
                    }
                    else if (player_hand[i].card_values[player_hand[i].best_combination[4]] > player_hand[j].card_values[player_hand[j].best_combination[4]])
                        rank[i]++;
                    else if (player_hand[i].card_values[player_hand[i].best_combination[4]] < player_hand[j].card_values[player_hand[j].best_combination[4]])
                        rank[j]++;
                }
                else if (player_hand[i].combination > player_hand[j].combination)
                {
                    rank[i]++;
                }
                else if (player_hand[i].combination < player_hand[j].combination)
                {
                    rank[j]++;
                }
            }

    /*
    printf("\nRank: ");
    for (int i = 0; i < 8; i++)
        printf("(%d) %d  ", i + 1, rank[i]);
    printf("\n");
    */

    max = 0;

    for (int i = 0; i < 8; i++)
    {
        if (rank[i] > max)
        {
            max = rank[i];
            position = i;
        }
        for (int j = 1 + i; j < 8; j++)
        {
            if (rank[j] > max)
            {
                max = rank[i];
                position = i;
            }
        }
    }

    for (int i = 0; i < 8; i++)
        if (contestant[i].inactive == NO)
        {
            printf("%d ", i + 1);
            stream = castItoC(player_hand[i].card_values);
            for (int j = 0; j < 5; j++)
            {
                temp_hand[j][0] = *(stream + (player_hand[i].best_combination[j]));
                temp_hand[j][1] = player_hand[i].card_naipes[player_hand[i].best_combination[j]];
                temp_hand[j][2] = '\0';
            }

            handSort(temp_hand, 5);

            for (int j = 4; j >= 0; j--)
            {
                printf("%s ", temp_hand[j]);
                if (i == position)
                {
                    strcpy(winner[j], temp_hand[j]);
                    winner_num = i;
                }
            }

            printf("%d", (player_hand[i].combination) + 1);
            printf("\n");
        }

    printf("W ");

    for (int i = 4; i >= 0; i--)
        printf("%s ", winner[i]);

    printf("%d ", (player_hand[position].combination) + 1);
    printf("%d", winner_num + 1);
    printf("\n");

    return res;
}