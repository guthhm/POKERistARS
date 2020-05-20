#ifndef POKERLIB_H
#define POKERLIB_H

typedef struct hand
{
    char card_naipes[7];
    int card_values[7];
    int best_combination[5];
    short combination;
}HAND;

typedef struct player
{
    short check;
    short fold;
    short inactive;
    float score;
}PLAYER;

typedef struct card_node
{
    short card_value;
    char card_naipe;
    CARD_NODE *next_card;
}CARD_NODE;

char *divideHands (char cards[10][3], int player);

void errorCheck (char input[10][3], int input_size);

HAND handIdentifier (HAND player, int hand_size);

PLAYER doContest (HAND player_hand[8], PLAYER contestant[8]);

#endif