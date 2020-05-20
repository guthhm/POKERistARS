#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "quicklib.h"
#include "pokerlib.h"

#define YES 1
#define NO 0

int main(int argc, char **argv)
{

    short loop = 0, count = 0, turn = 0, aux = 0, contestant_num = 0;
    int *input_int;
    long int cursor = 0;
    char *player_hands, *char_res, *deck_path;
    char input[10][3], splited_hands[1][7][3], temp_hand[7][3] = {0}, ch;
    char args[7][4] = {"-c", "-d1", "-d2", "-d3", "-d4", "-dx", "-s1"};
    FILE *deck_file;
    HAND hand_input[2] = {0}, hand_result[2], contestant_hand[8];
    PLAYER contestant[8] = {};

    loop = YES;
    for (int mode = 0; mode < 8; mode++) // for para deteção do modo de execução do programa
    {
        if (strstr(args[mode], argv[1]) != NULL) // Compara a string recebida na linha de comando com as opções válidas
        {
            loop = NO;
            switch (mode)
            {
            case 0: // Modo linha de comando

                if (argc != 7 && argc != 9 && argc != 11 && argc != 12) // Confere a quantidade de cartas
                {
                    printf("-1");
                    printf("\n");
                    exit(-1);
                }

                for (int i = 0; i < argc - 2; i++)
                { // Copia cartas recebidas na linha de comando para input
                    strcpy(input[i], argv[i + 2]);
                }

                errorCheck(input, argc - 2);

                switch (argc)
                {
                case 7:

                    handSort(input, 5);

                    input_int = castCtoI(input);
                    for (int i = 0; i < 5; i++)
                    {
                        hand_input[0].card_values[i] = *(input_int + i);
                        hand_input[0].card_naipes[i] = input[i][1];
                    }

                    hand_result[0] = handIdentifier(hand_input[0], 5);

                    printf("%d", (hand_result[0].combination) + 1);
                    printf("\n");

                    break;

                case 9:

                    handSort(input, 7);

                    input_int = castCtoI(input);
                    for (int i = 0; i < 7; i++)
                    {
                        hand_input[0].card_values[i] = *(input_int + i);
                        hand_input[0].card_naipes[i] = input[i][1];
                    }

                    hand_result[0] = handIdentifier(hand_input[0], 7);

                    char_res = castItoC(hand_result[0].card_values);
                    for (int i = 0; i < 5; i++)
                    {
                        temp_hand[i][0] = *(char_res + (hand_result[0].best_combination[i]));
                        temp_hand[i][1] = hand_result[0].card_naipes[hand_result[0].best_combination[i]];
                        temp_hand[i][2] = '\0';
                    }

                    handSort(temp_hand, 5);

                    for (int i = 4; i >= 0; i--)
                        printf("%s ", temp_hand[i]);

                    printf("%d", (hand_result[0].combination) + 1);
                    printf("\n");

                    break;

                case 11:

                    for (int i = 0; i < 2; i++)
                    { // i = 0 é jogador 1 ; i = 1 é jogador 2

                        player_hands = divideHands(input, i); // Cria 2 arrays com 7 elementos para os dois jogadores
                        int l = 0;

                        for (int j = 0; j < 7; j++) // Copia as mão divididas em splited_hands
                            for (int k = 0; k < 3; k++)
                                if (*player_hands != '\0')
                                {
                                    splited_hands[i][j][k] = *(player_hands + l);
                                    l++;
                                }
                    }

                    handSort(splited_hands[0], 7); // Ordena ambas as mãos
                    handSort(splited_hands[1], 7);

                    for (int i = 0; i < 2; i++) // Separa a parte intera dascartas do naipe, designando o valor de 2 a 14 para 2 e Ás, respectivamente
                    {
                        input_int = castCtoI(splited_hands[i]);
                        for (int j = 0; j < 7; j++)
                        {
                            hand_input[i].card_values[j] = *(input_int + j);
                            hand_input[i].card_naipes[j] = splited_hands[i][j][1];
                        }
                    }

                    for (int i = 0; i < 2; i++) // Classifica ambas as mãos e retorna a melhor combinação
                        hand_result[i] = handIdentifier(hand_input[i], 7);

                    for (int i = 0; i < 2; i++)
                    {

                        char_res = castItoC(hand_result[i].card_values);
                        for (int j = 0; j < 5; j++)
                        {
                            temp_hand[j][0] = *(char_res + (hand_result[i].best_combination[j]));
                            temp_hand[j][1] = hand_result[i].card_naipes[hand_result[i].best_combination[j]];
                            temp_hand[j][2] = '\0';
                        }

                        handSort(temp_hand, 5);

                        for (int i = 4; i >= 0; i--)
                            printf("%s ", temp_hand[i]);

                        printf("%d ", (hand_result[i].combination) + 1);
                        char_res = NULL;
                    }

                    if (hand_result[0].combination > hand_result[1].combination)
                        printf("1");
                    else if (hand_result[0].combination < hand_result[1].combination)
                        printf("2");
                    else if (hand_result[0].combination == hand_result[1].combination)
                    {
                        if (hand_result[0].card_values[6] > hand_result[0].card_values[6])
                            printf("1");
                        if (hand_result[0].card_values[6] < hand_result[0].card_values[6])
                            printf("2");
                        else
                            printf("0");
                    }
                    printf("\n");

                    break;

                case 12:

                    for (int j = 0; j < 5; j++)
                    {
                        strcpy(splited_hands[0][j], input[j]);
                        strcpy(splited_hands[1][j], input[j + 5]);
                    }

                    handSort(splited_hands[0], 5); // Ordena ambas as mãos
                    handSort(splited_hands[1], 5);

                    for (int i = 0; i < 2; i++) // Separa a parte intera dascartas do naipe, designando o valor de 2 a 14 para 2 e Ás, respectivamente
                    {
                        input_int = castCtoI(splited_hands[i]);
                        for (int j = 0; j < 5; j++)
                        {
                            hand_input[i].card_values[j] = *(input_int + j);
                            hand_input[i].card_naipes[j] = splited_hands[i][j][1];
                        }
                    }

                    for (int i = 0; i < 2; i++) // Classifica ambas as mãos e retorna a melhor combinação
                        hand_result[i] = handIdentifier(hand_input[i], 5);

                    for (int i = 0; i < 2; i++)
                    {

                        char_res = castItoC(hand_result[i].card_values);
                        for (int j = 0; j < 5; j++)
                        {
                            temp_hand[j][0] = *(char_res + (hand_result[i].best_combination[j]));
                            temp_hand[j][1] = hand_result[i].card_naipes[hand_result[i].best_combination[j]];
                            temp_hand[j][2] = '\0';
                        }

                        handSort(temp_hand, 5);

                        for (int i = 4; i >= 0; i--)
                            printf("%s ", temp_hand[i]);

                        printf("%d ", (hand_result[i].combination) + 1);
                        char_res = NULL;
                    }

                    if (hand_result[0].combination > hand_result[1].combination)
                        printf("1");
                    else if (hand_result[0].combination < hand_result[1].combination)
                        printf("2");
                    else if (hand_result[0].combination == hand_result[1].combination)
                    {
                        if (hand_result[0].card_values[6] > hand_result[0].card_values[6])
                            printf("1");
                        if (hand_result[0].card_values[6] < hand_result[0].card_values[6])
                            printf("2");
                        else
                            printf("0");
                    }

                    printf("\n");

                    break;

                default: // Savaguarda de eventual erro desconhecido
                    printf("-1");
                    printf("\n");
                    exit(-1);
                    break;
                }

                /*Impressão de dados*/ /*
                    
                    for (int i = 0; i < 2; i++) {
                        printf("\nPlayer %d:", i+1);
                        for (int j = 0; j < 7; j++)
                            printf("%s  ", splited_hands[i][j]);
                        printf("\n");
                    }

                    printf("\nMão ordenada:\n");

                    for (int i = 0; i < 2; i++) {
                        printf("\nPlayer %d:", i+1);
                        for (int j = 0; j < 7; j++)
                            printf("%s  ", splited_hands[i][j]);
                        printf("\n");
                    }

                    for (int i = 0; i < 2; i++) {
                        printf("\nI: %d\n", i);
                        for (int j = 0; j < 21; j++)
                            printf("%c..", *(player_hands+j));

                    printf("\n");
                    }
                    

                    printf("\n");   

                    // Imprime valores para conferir

                    //printf("\n\n");
                    printf("\tMãos: \n");

                    for (int i = 0; i < 2; i++) {
                        printf("\nJogador %d: ", i+1);
                        for (int j = 0; j < 7; j++)
                            printf("%d%c   ", hand_input[i].card_values[j], hand_input[i].card_naipes[j]);
                    }

                    printf("\n\n");
                    */

                break;

            case 1:

                /*---------- -d1 ----------*/

                deck_path = (char *)malloc(strlen(argv[2] + 1));

                strcpy(deck_path, argv[2]);

                if (strstr(deck_path, ".deck") != NULL)
                    deck_file = fopen(deck_path, "r");
                else
                {
                    printf("-1\n");
                    exit(-1);
                }

                if (deck_file == NULL)
                {
                    printf("-1\n");
                    exit(-1);
                }
                else
                {
                    while ((ch = fgetc(deck_file)) != EOF)
                    {
                        //printf("%c    ", ch);

                        if (((ch > '1') && (ch <= '9')) || (ch == 'T') || (ch == 'J') || (ch == 'Q') || (ch == 'K') || (ch == 'A'))
                        {
                            input[count][0] = ch;
                        }
                        else if ((ch == 'C') || (ch == 'E') || (ch == 'O') || (ch == 'P'))
                        {
                            input[count][1] = ch;
                            input[count][2] = '\0';
                            count++;
                            aux++;
                            //printf("%s ", input[count-1]);
                        }

                        if ((count % 5 == 0) && (count != 0))
                        {
                            /*printf("\nCount: %d\n", count);
                                for (int i = 0; i < 6; i++)
                                {
                                    printf("%s ", input[i]);
                                }
                                printf("\n");*/

                            handSort(input, 5);

                            input_int = castCtoI(input);
                            for (int i = 0; i < 5; i++)
                            {
                                hand_input[0].card_values[i] = *(input_int + i);
                                hand_input[0].card_naipes[i] = input[i][1];
                            }

                            hand_result[0] = handIdentifier(hand_input[0], 5);

                            printf("%d", (hand_result[0].combination) + 1);
                            printf("\n");

                            count = 0;
                        }

                        if (aux == 52)
                        {
                            aux = 0;
                            count = 0;
                            turn++;
                            printf("\n");
                        }
                    }
                }

                free(deck_path);
                fclose(deck_file);

                break;

            case 2:

                /*---------- -d2 ----------*/

                deck_path = (char *)malloc(strlen(argv[2] + 1));

                strcpy(deck_path, argv[2]);

                if (strstr(deck_path, ".deck") != NULL)
                    deck_file = fopen(deck_path, "r");
                else
                {
                    printf("-1\n");
                    exit(-1);
                }

                if (deck_file == NULL)
                {
                    printf("-1\n");
                    exit(-1);
                }
                else
                {
                    while ((ch = fgetc(deck_file)) != EOF)
                    {
                        //printf("%c    ", ch);

                        if (((ch > '1') && (ch <= '9')) || (ch == 'T') || (ch == 'J') || (ch == 'Q') || (ch == 'K') || (ch == 'A'))
                        {
                            input[count][0] = ch;
                        }
                        else if ((ch == 'C') || (ch == 'E') || (ch == 'O') || (ch == 'P'))
                        {
                            input[count][1] = ch;
                            input[count][2] = '\0';
                            count++;
                            aux++;
                            //printf("%s ", input[count-1]);
                        }

                        if ((count % 7 == 0) && (count != 0))
                        {
                            /*printf("\nCount: %d\n", count);
                                for (int i = 0; i < 6; i++)
                                {
                                    printf("%s ", input[i]);
                                }
                                printf("\n");*/

                            handSort(input, 7);

                            input_int = castCtoI(input);
                            for (int i = 0; i < 8; i++)
                            {
                                hand_input[0].card_values[i] = *(input_int + i);
                                hand_input[0].card_naipes[i] = input[i][1];
                            }

                            hand_result[0] = handIdentifier(hand_input[0], 7);

                            char_res = castItoC(hand_result[0].card_values);
                            for (int i = 0; i < 5; i++)
                            {
                                temp_hand[i][0] = *(char_res + (hand_result[0].best_combination[i]));
                                temp_hand[i][1] = hand_result[0].card_naipes[hand_result[0].best_combination[i]];
                                temp_hand[i][2] = '\0';
                            }

                            handSort(temp_hand, 5);

                            for (int i = 4; i >= 0; i--)
                                printf("%s ", temp_hand[i]);

                            printf("%d", (hand_result[0].combination) + 1);
                            printf("\n");

                            count = 0;
                        }

                        if (aux == 52)
                        {
                            aux = 0;
                            count = 0;
                            turn++;
                            printf("\n");
                        }
                    }
                }

                free(deck_path);
                fclose(deck_file);

                break;

            case 3:

                /*---------- -d3 ----------*/

                deck_path = (char *)malloc(strlen(argv[2] + 1));

                strcpy(deck_path, argv[2]);

                if (strstr(deck_path, ".deck") != NULL)
                    deck_file = fopen(deck_path, "r");
                else
                {
                    printf("-1\n");
                    exit(-1);
                }

                if (deck_file == NULL)
                {
                    printf("-1\n");
                    exit(-1);
                }
                else
                {
                    while ((ch = fgetc(deck_file)) != EOF)
                    {
                        //printf("%c    ", ch);

                        if (((ch > '1') && (ch <= '9')) || (ch == 'T') || (ch == 'J') || (ch == 'Q') || (ch == 'K') || (ch == 'A'))
                        {
                            input[count][0] = ch;
                        }
                        else if ((ch == 'C') || (ch == 'E') || (ch == 'O') || (ch == 'P'))
                        {
                            input[count][1] = ch;
                            input[count][2] = '\0';
                            count++;
                            aux++;
                            //printf("%s ", input[count-1]);
                        }

                        if ((count % 9 == 0) && (count != 0))
                        {
                            /*printf("\nCount: %d\n", count);
                                for (int i = 0; i < 6; i++)
                                {
                                    printf("%s ", input[i]);
                                }
                                printf("\n");*/

                            for (int i = 0; i < 2; i++)
                            { // i = 0 é jogador 1 ; i = 1 é jogador 2

                                player_hands = divideHands(input, i); // Cria 2 arrays com 7 elementos para os dois jogadores
                                int l = 0;

                                for (int j = 0; j < 7; j++) // Copia as mão divididas em splited_hands
                                    for (int k = 0; k < 3; k++)
                                        if (*player_hands != '\0')
                                        {
                                            splited_hands[i][j][k] = *(player_hands + l);
                                            l++;
                                        }
                            }

                            handSort(splited_hands[0], 7); // Ordena ambas as mãos
                            handSort(splited_hands[1], 7);

                            for (int i = 0; i < 2; i++) // Separa a parte intera dascartas do naipe, designando o valor de 2 a 14 para 2 e Ás, respectivamente
                            {
                                input_int = castCtoI(splited_hands[i]);
                                for (int j = 0; j < 7; j++)
                                {
                                    hand_input[i].card_values[j] = *(input_int + j);
                                    hand_input[i].card_naipes[j] = splited_hands[i][j][1];
                                }
                            }

                            for (int i = 0; i < 2; i++) // Classifica ambas as mãos e retorna a melhor combinação
                                hand_result[i] = handIdentifier(hand_input[i], 7);

                            for (int i = 0; i < 2; i++)
                            {

                                char_res = castItoC(hand_result[i].card_values);
                                for (int j = 0; j < 5; j++)
                                {
                                    temp_hand[j][0] = *(char_res + (hand_result[i].best_combination[j]));
                                    temp_hand[j][1] = hand_result[i].card_naipes[hand_result[i].best_combination[j]];
                                    temp_hand[j][2] = '\0';
                                }

                                handSort(temp_hand, 5);

                                for (int i = 4; i >= 0; i--)
                                    printf("%s ", temp_hand[i]);

                                printf("%d ", (hand_result[i].combination) + 1);
                                char_res = NULL;
                            }

                            if (hand_result[0].combination > hand_result[1].combination)
                                printf("1");
                            else if (hand_result[0].combination < hand_result[1].combination)
                                printf("2");
                            else if (hand_result[0].combination == hand_result[1].combination)
                            {
                                if (hand_result[0].card_values[6] > hand_result[0].card_values[6])
                                    printf("1");
                                if (hand_result[0].card_values[6] < hand_result[0].card_values[6])
                                    printf("2");
                                else
                                    printf("0");
                            }
                            printf("\n");

                            count = 0;
                        }

                        if (aux == 52)
                        {
                            aux = 0;
                            count = 0;
                            turn++;
                            printf("\n");
                        }
                    }
                }

                free(deck_path);
                fclose(deck_file);

                break;

            case 4:

                /*---------- -d4 ----------*/

                deck_path = (char *)malloc(strlen(argv[2] + 1));

                strcpy(deck_path, argv[2]);

                if (strstr(deck_path, ".deck") != NULL)
                    deck_file = fopen(deck_path, "r");
                else
                {
                    printf("-1\n");
                    exit(-1);
                }

                if (deck_file == NULL)
                {
                    printf("-1\n");
                    exit(-1);
                }
                else
                {
                    while ((ch = fgetc(deck_file)) != EOF)
                    {
                        //printf("%c    ", ch);

                        if (((ch > '1') && (ch <= '9')) || (ch == 'T') || (ch == 'J') || (ch == 'Q') || (ch == 'K') || (ch == 'A'))
                        {
                            input[count][0] = ch;
                        }
                        else if ((ch == 'C') || (ch == 'E') || (ch == 'O') || (ch == 'P'))
                        {
                            input[count][1] = ch;
                            input[count][2] = '\0';
                            count++;
                            aux++;
                            //printf("%s ", input[count-1]);
                        }

                        if ((count % 10 == 0) && (count != 0))
                        {
                            /*printf("\nCount: %d\n", count);
                                for (int i = 0; i < 6; i++)
                                {
                                    printf("%s ", input[i]);
                                }
                                printf("\n");*/

                            for (int j = 0; j < 5; j++)
                            {
                                strcpy(splited_hands[0][j], input[j]);
                                strcpy(splited_hands[1][j], input[j + 5]);
                            }

                            handSort(splited_hands[0], 5); // Ordena ambas as mãos
                            handSort(splited_hands[1], 5);

                            for (int i = 0; i < 2; i++) // Separa a parte intera dascartas do naipe, designando o valor de 2 a 14 para 2 e Ás, respectivamente
                            {
                                input_int = castCtoI(splited_hands[i]);
                                for (int j = 0; j < 5; j++)
                                {
                                    hand_input[i].card_values[j] = *(input_int + j);
                                    hand_input[i].card_naipes[j] = splited_hands[i][j][1];
                                }
                            }

                            for (int i = 0; i < 2; i++) // Classifica ambas as mãos e retorna a melhor combinação
                                hand_result[i] = handIdentifier(hand_input[i], 5);

                            for (int i = 0; i < 2; i++)
                            {

                                char_res = castItoC(hand_result[i].card_values);
                                for (int j = 0; j < 5; j++)
                                {
                                    temp_hand[j][0] = *(char_res + (hand_result[i].best_combination[j]));
                                    temp_hand[j][1] = hand_result[i].card_naipes[hand_result[i].best_combination[j]];
                                    temp_hand[j][2] = '\0';
                                }

                                handSort(temp_hand, 5);

                                for (int i = 4; i >= 0; i--)
                                    printf("%s ", temp_hand[i]);

                                printf("%d ", (hand_result[i].combination) + 1);
                                char_res = NULL;
                            }

                            if (hand_result[0].combination > hand_result[1].combination)
                                printf("1");
                            else if (hand_result[0].combination < hand_result[1].combination)
                                printf("2");
                            else if (hand_result[0].combination == hand_result[1].combination)
                            {
                                if (hand_result[0].card_values[6] > hand_result[0].card_values[6])
                                    printf("1");
                                if (hand_result[0].card_values[6] < hand_result[0].card_values[6])
                                    printf("2");
                                else
                                    printf("0");
                            }

                            printf("\n");

                            count = 0;
                        }

                        if (aux == 52)
                        {
                            aux = 0;
                            count = 0;
                            turn++;
                            printf("\n");
                        }
                    }
                }

                free(deck_path);
                fclose(deck_file);

                break;

            case 5:

                /*---------- -dx ----------*/
                aux = 0;

                deck_path = (char *)malloc(strlen(argv[2] + 1));

                strcpy(deck_path, argv[2]);

                if (strstr(deck_path, ".deck") != NULL)
                    deck_file = fopen(deck_path, "r");
                else
                {
                    printf("-1\n");
                    exit(-1);
                }

                if (deck_file == NULL)
                {
                    printf("-1\n");
                    exit(-1);
                }
                else
                {

                    for (int i = 0; i < 8; i++)
                        if (contestant[i].check == 2)
                        {
                            contestant[i].inactive = YES;
                            contestant[i].check = 0;
                        }

                    while ((ch = fgetc(deck_file)) != EOF)
                    {
                        //printf("%c  ", ch);

                        if (((ch > '1') && (ch <= '9')) || (ch == 'T') || (ch == 'J') || (ch == 'Q') || (ch == 'K') || (ch == 'A'))
                            input[count][0] = ch;
                        else if ((ch == 'C') || (ch == 'E') || (ch == 'O') || (ch == 'P'))
                        {
                            input[count][1] = ch;
                            input[count][2] = '\0';
                            count++;
                            aux++;
                            //printf("%s ", input[count-1]);
                        }

                        if (contestant_num != 99)
                        {
                            if ((count % 2 == 0) && (count != 0) && (contestant_num < 8))
                            {

                                while (contestant[contestant_num].inactive == YES)
                                    contestant_num++;

                                if (contestant[contestant_num].inactive == NO)
                                {
                                    input_int = castCtoI(input);
                                    for (int i = 0; i < 2; i++)
                                    {
                                        contestant_hand[contestant_num].card_values[i] = *(input_int + i);
                                        contestant_hand[contestant_num].card_naipes[i] = input[i][1];
                                    }
                                    contestant_num++;
                                }

                                count = 0;
                            }

                            if ((count % 5 == 0) && (count != 0) && (contestant_num == 8))
                            {
                                /*printf("\nCartas mesa: ");
                                for (int i = 0; i < 5; i++)
                                    printf("%s ", input[i]);
                                printf("\n");*/

                                input_int = castCtoI(input);

                                for (int i = 0; i < 8; i++)
                                    if (contestant[i].inactive == NO)
                                        for (int j = 0; j < 5; j++)
                                        {
                                            contestant_hand[i].card_values[j + 2] = *(input_int + j);
                                            contestant_hand[i].card_naipes[j + 2] = input[j][1];
                                        }

                                count = 0;
                                contestant_num = 99;
                            }
                        }

                        if (aux == 52)
                        {
                            aux = 0;
                            contestant_num = 0;
                            turn++;

                            for (int i = 0; i < 8; i++)
                            {
                                char_res = castItoC(contestant_hand[i].card_values);
                                for (int j = 0; j < 7; j++)
                                {
                                    temp_hand[j][0] = *(char_res + j);
                                    temp_hand[j][1] = contestant_hand[i].card_naipes[j];
                                    temp_hand[j][2] = '\0';
                                }

                                handSort(temp_hand, 7);

                                input_int = castCtoI(temp_hand);
                                for (int j = 0; j < 7; j++)
                                {
                                    contestant_hand[i].card_values[j] = *(input_int + j);
                                    contestant_hand[i].card_naipes[j] = temp_hand[j][1];
                                }

                                contestant_hand[i] = handIdentifier(contestant_hand[i], 7);
                            }

                            for (int i = 0; i < 8; i++)
                            {
                                if ((contestant_hand[i].combination >= i) || (contestant[i].fold == 4))
                                    contestant[i].inactive = NO;
                                else
                                    contestant[i].inactive = YES;

                                if (contestant[i].inactive == NO)
                                {
                                    contestant[i].check++;
                                    contestant[i].fold = 0;
                                } 
                                else
                                {
                                    contestant[i].fold++;
                                    contestant[i].check = 0;
                                }
                            }

                            doContest(contestant_hand, contestant);
                            printf("\n");

                            /*
                            printf("\n"); 
                            for (int i = 0; i < 8; i++)
                                if (contestant[i].inactive == NO || contestant[i].inactive == YES)
                                {
                                    printf("Jogador %d: ", i + 1);
                                    for (int j = 0; j < 7; j++)
                                        printf("%d%c  ", contestant_hand[i].card_values[j], contestant_hand[i].card_naipes[j]);
                                    printf("  %d\n", contestant_hand[i].combination + 1);
                                }
                                */
                        }
                    }
                }

                break;

            case 6:
                printf("\n-s1\n");

                printf("-1");
                printf("\n");
                exit(-1);
                break;

            default:
                printf("-1");
                printf("\n");
                exit(-1);
                break;
            }
        }
        else if ((loop != NO) && (mode == 8))
        {
            printf("-1");
            printf("\n");
            exit(-1);
        }
    }

    return 0;
}
