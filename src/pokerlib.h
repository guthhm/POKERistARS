#ifndef POKERLIB_H
#define POKERLIB_H

typedef struct hand
{
    char card_naipes[7];
    short card_values[7];
    short best_combination[5];
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
    char card_value;
    char card_naipe;
    struct card_node *next_card;
}CARD_NODE;

typedef struct shuffle_node
{
    short type;
    struct shuffle_node *next;
}SHUFFLE_NODE;


char *divideHands (char cards[10][3], int player);

void errorCheck (char input[10][3], int input_size);

HAND handIdentifier (HAND player, int hand_size);

PLAYER doContest (HAND player_hand[8], PLAYER contestant[8]);

void shakeIt (SHUFFLE_NODE *shuffle_head, CARD_NODE *deck_head, CARD_NODE *half_deck, short print_to_file);

#endif