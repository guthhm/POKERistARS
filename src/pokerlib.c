#include "pokerlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **divideHands (char cards[10][3], int player) {

    static char player_hands[6][3];

    if (player == 0)
        for (int i = 0; i < 10; i++) {// Copia elementos do input original para a mão do jogador
            if (i != 2 && i != 3)// Excepto elementos 2 e 3 por pertencerem ao 2º jogador.
                strcpy(player_hands[i], cards[i]);
            if (i > 3)
                strcpy(player_hands[i-2], cards[i]); // Volta 2 elementos do array pois a mão do jogador é menor que o input
        }

    if (player == 1)
        for (int i = 2; i < 10; i++) // Copia elementos do input original a aprtir da 2ª posição do array
            strcpy(player_hands[i], cards[i]);

    return player_hands;

}