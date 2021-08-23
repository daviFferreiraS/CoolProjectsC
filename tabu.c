/*
━━━━━━━━┛ ✠ ┗━━━━━━━━━━━━━━━━┛ ✠ ┗━━━━━━━━
Davi Fagundes, nUSP: 12544013, ICMC USP
━━━━━━━━┓ ✠ ┏━━━━━━━━━━━━━━━━┓ ✠ ┏━━━━━━━━
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline() // vai retornar um ponteiro de char
{ 
    char c = ' ';
    char *endereco = NULL; 
    int cont_char = 0;
    // aqui faz a leitura e concatenacao da string
    while ( c != '\n' && c != EOF && c != '$')
    {
        c = getchar();
        cont_char++;
        endereco = realloc(endereco, cont_char*(sizeof(char)));
        *(endereco + cont_char - 1) = c;
    }
    *(endereco + cont_char -1) = '\0';
    
    return endereco;
}

char *RemoverSubString(char *frase, const char *palavraTabu, int *repeticoes ){
    int size = strlen(palavraTabu);
    if(size > 0){
        char *auxiliar = frase;
        while ((auxiliar = strstr(auxiliar,palavraTabu)) != NULL){
            memmove(auxiliar, auxiliar + size, strlen(auxiliar + size) + 1);
            *repeticoes += 1;
        }  
    }
    return frase;
}

int main(int argc, char const *argv[])
{
    int repeticoes_tabu = 0;
    char palavraTabu[20];
    scanf("%s\n", palavraTabu);

    char *frase = NULL;
    frase = readline();

    RemoverSubString(frase, palavraTabu, &repeticoes_tabu);
     
    
    printf("A palavra tabu foi encontrada %d vezes\n", repeticoes_tabu);
    printf("Frase: %s\n",frase);
    free(frase);
    return 0;
}
