/*
━━━━━━━━┛ ✠ ┗━━━━━━━━━━━━━━━━┛ ✠ ┗━━━━━━━━
Davi Fagundes, nUSP: 12544013, ICMC USP
━━━━━━━━┓ ✠ ┏━━━━━━━━━━━━━━━━┓ ✠ ┏━━━━━━━━
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

char *readline();
int tipo_palindromo();

int main(int argc, char const *argv[])
{
    char *frase;
    frase = readline();
    int *contador = malloc(sizeof(int));
    *contador = 0;

    int tamanho_frase = strlen(frase);

    // Checando se é ou não um palíndromo
    if(frase[tamanho_frase-1] == frase[0]){ 
        if(tipo_palindromo(frase, contador)){
            printf("Palindromo direto\n");
        }
        else{
            printf("Palindromo indireto\n");
        }
    }
    else{
        printf("Nao eh um palindromo\n");
    }

    // Desalocando memória
    free(contador);
    free(frase);
    return 0;
}

char *readline() // vai retornar um ponteiro de char
{ 
    char c = 'a';
    char *endereco = NULL; 
    int cont_char = 0;
    // aqui faz a leitura e concatenacao da string
    while ( c != '\n' && c != EOF)
    {
        c = getchar();
        if(isalnum(c) || c == ' ' || c == '/'){
            cont_char++;
            endereco = realloc(endereco, cont_char*(sizeof(char)));
            *(endereco + cont_char - 1) = toupper(c);  
        }
    }
    cont_char++;
    endereco = realloc(endereco, cont_char*(sizeof(char)));
    *(endereco + cont_char -1) = '\0';
    
    return endereco;
}

int tipo_palindromo(char *frase, int *contador){ // Retorna 1 (TRUE) ou 0 (FALSE)
    if(strlen(frase) <= 1)
        return TRUE; // Caso houver apenas um caractere ou nenhum na frase

    int tamanho_frase = strlen(frase);

    if(*contador == (tamanho_frase)){ // Definindo palindromo direto, condição de parada
        return TRUE;
    }
        

    if(frase[*contador] == frase[tamanho_frase - (*contador + 1)]){
        *contador += 1;
        return tipo_palindromo(frase, contador); // Passagem do contador para condição de parada
    }
    else
        return FALSE; // Definindo palindromo indireto
} 