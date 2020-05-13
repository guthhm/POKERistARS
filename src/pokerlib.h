#ifndef POKERLIB_H
#define POKERLIB_H

typedef struct hand
{
    char card_naipes[7];
    int card_values[7];
    int best_combination[5];
    int combination;
}HAND;

char *divideHands (char cards[10][3], int player);

void errorCheck (char input[10][3], int input_size);

HAND handIdentifier (HAND player, int hand_size);

#endif