#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct { // Eu to ligado que tá mta coisa na struct, mas achei pertinente guardar tudo isso.
    char **matriz;
    char *nomeArquivo;
    int qtdLinhas;
    int qtdColunas;
    int nPessoas;
    int caminhos;
    int visitados;
    double exploracao;
} desenho_t;

typedef struct 
{
   int coordX;
   int coordY;
} ponto_t;

char *readline();
void receberDesenho( desenho_t *desenho, ponto_t *ponto);
void printarDesenho( desenho_t desenho);
void fugirDosParentes( desenho_t *desenho, int coordX, int coordY, int *finalizou);

int main(){
    desenho_t labirinto;
    ponto_t ponto_inicial; 
    labirinto.nomeArquivo = readline();
    labirinto.matriz = NULL;
    labirinto.nPessoas = 0; labirinto.caminhos = 0; labirinto.visitados = 0; labirinto.exploracao =0.0;
    int final = FALSE;
    receberDesenho(&labirinto, &ponto_inicial);
    fugirDosParentes(&labirinto, ponto_inicial.coordX, ponto_inicial.coordY, &final);
    printarDesenho(labirinto);
    
    for (int i = 0; i < labirinto.qtdLinhas; i++)
    {
        free(labirinto.matriz[i]);
    }
    free(labirinto.matriz);
    free(labirinto.nomeArquivo);
    return 0;
}

char *readline() // vai retornar um ponteiro de char
{ 
    char c = ' ';
    char *endereco = NULL; 
    int cont_char = 0;
    // aqui faz a leitura e concatenacao da string
    do{
        c = fgetc(stdin);
    }while(c == '\n');
    ungetc(c, stdin);
 
    while ( c != '\n' && c != EOF)
    {
        c = getchar();
        cont_char++;
        endereco = realloc(endereco, cont_char*(sizeof(char)));
        *(endereco + cont_char - 1) = c; // endereço[cont_char - 1]
    }
    *(endereco + cont_char - 1) = '\0';
    
    return endereco;
}

void receberDesenho(desenho_t *desenho, ponto_t *ponto){
    char entrada;
    FILE *arquivoLeitura = fopen(desenho->nomeArquivo, "r");
    fscanf(arquivoLeitura, "%d %d", &desenho->qtdLinhas, &desenho->qtdColunas);

    desenho->matriz = realloc(desenho->matriz, sizeof(char *) * desenho->qtdLinhas);
    for (int i = 0; i < desenho->qtdLinhas; i++){
        desenho->matriz[i] = NULL;
    }
    for (int i = 0; i < desenho->qtdLinhas; i++){
        desenho->matriz[i] = realloc(desenho->matriz[i], sizeof(char) * desenho->qtdColunas);
    }

    fscanf(arquivoLeitura, "%d %d%*c", &ponto->coordX, &ponto->coordY);
   for (int i = 0; i < desenho->qtdLinhas; i++){
       for (int j = 0; j < desenho->qtdColunas; j++){
           fscanf(arquivoLeitura,"%c",&entrada);
            desenho->matriz[i][j] = entrada;
            if(entrada == '#')
                desenho->nPessoas+=1;
            else if( entrada == '.' )
                desenho->caminhos += 1;
       }
       fscanf(arquivoLeitura,"%*c");
   }
    
    fclose(arquivoLeitura);
}

void printarDesenho(desenho_t desenho){
    for (int i = 0; i < desenho.qtdLinhas; i++){
       for (int j = 0; j < desenho.qtdColunas; j++){
           printf("%c", desenho.matriz[i][j]);
       }
       printf("\n");
   }
    desenho.exploracao = (desenho.visitados*100)/desenho.caminhos;

   printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
   printf("Veja abaixo os detalhes da sua fuga:\n");
   printf("----Pessoas te procurando: %d\n", desenho.nPessoas);
   printf("----Numero total de caminhos validos:   %d\n", desenho.caminhos);
   printf("----Numero total de caminhos visitados: %d\n", desenho.visitados);
   printf("----Exploracao total do labirinto: %.1lf%%\n", desenho.exploracao);
}

void fugirDosParentes( desenho_t *desenho, int coordX, int coordY, int *finalizou){

// primeira etapa finalizou é falso
    if (*finalizou == FALSE){
        desenho->matriz[coordX][coordY] = '*';
        desenho->visitados+=1;  
    }
    if ( (coordX > 0 && coordX < desenho->qtdLinhas - 1) 
        && (coordY > 0 && coordY < desenho->qtdColunas - 1) ){
        
        if( desenho->matriz[coordX - 1][coordY] == '.' && *finalizou == FALSE){ // CIMA
            fugirDosParentes(desenho, coordX - 1, coordY, finalizou);
        }
        if( desenho->matriz[coordX][coordY + 1] == '.' && *finalizou == FALSE ){ // DIREITA
            fugirDosParentes(desenho, coordX, coordY + 1, finalizou);
        }
        if ( desenho->matriz[coordX + 1][coordY] == '.' && *finalizou == FALSE ){ // BAIXO
            fugirDosParentes(desenho, coordX + 1, coordY, finalizou);
        }
        if ( desenho->matriz[coordX][coordY - 1] == '.' && *finalizou == FALSE ){ // ESQUERDA
            fugirDosParentes(desenho, coordX, coordY - 1, finalizou);
        }
    }
    else if( coordX == 0 || coordX == desenho->qtdLinhas-1 ||
    coordY == 0 || coordY == desenho->qtdColunas-1 ){
        *finalizou = TRUE;
    }

}