#include "pokerlib.h"

#ifndef QUICKLIB_H
#define QUICKLIB_H

#define YES 1
#define NO 0

typedef struct flag
{
    short loop;
    short turn;
    short count;
    short aux;
    short print_to_file;
}FLAG;

short handSort (char array[7][3], short arr_size);

short *castCtoI (char array[7][3]);

char *castItoC (short array[10]);

SHUFFLE_NODE *createShuffleNode (short value);

void insertAtTheEndOfShuffle (SHUFFLE_NODE *head, SHUFFLE_NODE *new_node);

void deleteLastNodeOfShuffle (SHUFFLE_NODE *head);

CARD_NODE *createCardNode (short value, char naipe);

void insertAtTheEndOfCard (CARD_NODE *head, CARD_NODE *new_node);

#endif