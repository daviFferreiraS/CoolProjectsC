#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    double *pilha = NULL;
    int contCharValido = 0;
    char entrada = ' ';
    double tmp = 0;
    while (entrada != EOF)
    {
        entrada = getchar();
        if(entrada != ' '){
            if(entrada > 47 && entrada < 58){
                contCharValido++;
                // push(pilha, entrada, &contCharValido);
                pilha = realloc(pilha, sizeof(double) * contCharValido);
                /* pilha[(*cont) - 1] = (double)ToDigit(entrada); */
                ungetc(entrada, stdin);
                scanf("%lf", &pilha[contCharValido- 1]);
            }
            else{
                switch (entrada)
                {
                    case '+':
                        tmp = pilha[contCharValido - 1] + pilha[contCharValido - 2];
                        contCharValido -= 1;
                        pilha = realloc(pilha, sizeof(double) * (contCharValido));
                        pilha[ contCharValido - 1] = tmp;
                        break;
                    case '-':
                        contCharValido -= 1;
                        tmp = pilha[ contCharValido - 1] -  pilha[ contCharValido];
                        pilha = realloc(pilha, sizeof(double) * (contCharValido));
                        pilha[ contCharValido - 1] = tmp;
                        break;
                    case '/':
                        tmp = pilha[ contCharValido - 2] / pilha[ contCharValido - 1];
                        contCharValido -= 1;
                        pilha = realloc(pilha, sizeof(double) * (contCharValido));
                        pilha[ contCharValido - 1] = tmp;
                        break;
                    case '*':
                        tmp = pilha[ contCharValido - 1] * pilha[ contCharValido - 2];
                        contCharValido -= 1;
                        pilha = realloc(pilha, sizeof(double) * (contCharValido));
                        pilha[ contCharValido - 1] = tmp;
                        break;
                    default: // *
                        break;
                }
            }
        }
        
    }
    printf("Resultado: %f\n", pilha[0]);
    free(pilha);
    return 0;
}
