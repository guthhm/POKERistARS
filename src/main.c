#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define YES 1
#define NO 0 
#define hands[9] {1,2,3,4,5,6,7,8,9,10}

int handIdentifier (char hand[10][3]) {



}

int main(int argc, char **argv) {

    int loop = 0;
    char input[10][3];
    char args[8][3] ={"-c", "-d1", "-d2", "-d3", "-d4", "-dx", "-s1", "-o"};

    loop = YES;
    for (int i = 0; i < 9; i++)     // for para deteção do modo de execução do programa
    {
        if (strstr(args[i], argv[1]) != NULL)   // Compara a string recebida na linha de comando com as opções válidas
        {
            loop = NO;
            switch (i)
            {
                case 0:
                    printf("\n-c\n");
                    break;
                
                case 1:
                    printf("\n-d1\n");
                    break;

                case 2:
                    printf("\n-d2\n");
                    break;

                case 3:
                    printf("\n-d3\n");
                    break;

                case 4:
                    printf("\n-d4\n");
                    break;

                case 5:
                    printf("\n-dx\n");
                    break;

                case 6:
                    printf("\n-s1\n");
                    break;

                case 7:
                    printf("\n-o\n");
                    break;
                
                default:
                    printf("\nO modo de execucao escolhido nao e valido. Por favor tente novamente.\n");
                    exit(-1);
                    break;
            }
        }
        else if (loop != NO)
        {
            printf("\nO modo de execucao escolhido nao e valido. Por favor tente novamente.\n\n");
            exit(-1);
        } 
        
    }

    switch (argc)
    {
    case 7:
        for (int i = 0; i < argc-2; i++)
            strcpy(input[i], argv[i+2]);

        for (int i = 0; i < argc-2; i++)
            printf("Input: %s\n", input[i]);
        break;

    case 9:
        for (int i = 0; i < argc-2; i++)
            strcpy(input[i], argv[i+2]);

        for (int i = 0; i < argc-2; i++)
            printf("Input: %s\n", input[i]);
        break;

    case 11:
        for (int i = 0; i < argc-2; i++)
            strcpy(input[i], argv[i+2]);

        for (int i = 0; i < argc-2; i++)
            printf("Input: %s\n", input[i]);
        break;

    case 12:
        for (int i = 0; i < argc-2; i++)
            strcpy(input[i], argv[i+2]);

        for (int i = 0; i < argc-2; i++)
            printf("Input: %s\n", input[i]);
        break;
    
    default:
        break;
    }

    printf("\n");

    return 0;

}
