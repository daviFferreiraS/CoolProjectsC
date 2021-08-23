/*
━━━━━━━━┛ ✠ ┗━━━━━━━━━━━━━━━━┛ ✠ ┗━━━━━━━━
Davi Fagundes, nUSP: 12544013, ICMC USP
━━━━━━━━┓ ✠ ┏━━━━━━━━━━━━━━━━┓ ✠ ┏━━━━━━━━
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define VIVO 'x'
#define MORTO '.'
#define NEUMANN 'N'
#define MOORE 'M'


char status_celula( int contador, char mesmo_estado){
    if(mesmo_estado == VIVO && (contador < 2 || contador > 3)){
        return MORTO;
    }
    else if(mesmo_estado == MORTO && (contador == 3)){
        return VIVO;
    }
    else{
        return mesmo_estado;
    }
    return 'o';
}


void calcular_moore(char **tabuleiro, int linhas, int colunas){
    int contador_vizinhos = 0;

    char copia[linhas][colunas];

    // Fazendo a cópia da matriz para manipular as celulas
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            copia[i][j] = tabuleiro[i][j];
        }
    }
    

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            // Definindo as coordenadas de cada situação do Moore
            int esquerda, cima, baixo, direita;
            cima = i > 0 ? i-1 : linhas - 1;
            baixo = (i + 1) % linhas; // valores até linhas - 1 
            esquerda = j > 0 ? j - 1 : colunas -1;
            direita = (j + 1) % colunas;

            // Checar os vizinhos com as coordenadas definidas
            if(copia[i][esquerda] == VIVO)
                contador_vizinhos++;
            if(copia[baixo][esquerda] == VIVO)
                contador_vizinhos++;
            if(copia[cima][esquerda] == VIVO)
                contador_vizinhos++;
            if(copia[i][direita] == VIVO)
                contador_vizinhos++;
            if(copia[baixo][direita] == VIVO)
                contador_vizinhos++;
            if(copia[cima][direita] == VIVO)
                contador_vizinhos++;
            if(copia[cima][j] == VIVO)
                contador_vizinhos++;
            if(copia[baixo][j] == VIVO)
                contador_vizinhos++;

            // Alterando o tabuleiro e resetando o contador pra próxima manipulação.
            tabuleiro[i][j] = status_celula(contador_vizinhos, tabuleiro[i][j]);
            contador_vizinhos = 0;
        }     
    }
}

void calcular_von_neumann(char **tabuleiro, int linhas, int colunas){
    int contador_vizinhos = 0;
    char copia[linhas][colunas];
    // Fazendo a cópia da matriz para manipular as celulas
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            copia[i][j] = tabuleiro[i][j];
        }
    }
    
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            // Definindo as coordenadas de cada situação do van neumann
            int esquerda, cima, baixo, direita, direita_direita, esquerda_esquerda, cima_cima, baixo_baixo;
            cima = i > 0 ? i-1 : linhas - 1;
            baixo = (i + 1) % linhas; // valores até linhas - 1 
            esquerda = j > 0 ? j - 1 : colunas - 1;
            direita = (j + 1) % colunas;

            cima_cima = cima > 0 ? cima - 1 : linhas - 1;
            direita_direita = direita < (colunas - 1) ? direita + 1 : 0;
            esquerda_esquerda = esquerda > 0 ? esquerda - 1 : colunas - 1;
            baixo_baixo = baixo < (linhas - 1) ? baixo + 1 : 0;  

            // Checar os vizinhos com as coordenadas definidas
            if(copia[cima][j] == VIVO)
                contador_vizinhos++;
            if(copia[cima_cima][j] == VIVO)
                contador_vizinhos++;
            if(copia[baixo][j] == VIVO)
                contador_vizinhos++;
            if(copia[baixo_baixo][j] == VIVO)
                contador_vizinhos++;
            if(copia[i][esquerda] == VIVO)
                contador_vizinhos++;
            if(copia[i][esquerda_esquerda] == VIVO)
                contador_vizinhos++;
            if(copia[i][direita] == VIVO)
                contador_vizinhos++;
            if(copia[i][direita_direita] == VIVO)
                contador_vizinhos++;

            // Alterando o tabuleiro e resetando o contador pra próxima manipulação.
            tabuleiro[i][j] = status_celula(contador_vizinhos, tabuleiro[i][j]);
            contador_vizinhos = 0;
        }
        
    }
    
    

} 

void liberar_tabuleiro(char **tabuleiro, int linhas){
    for (int i = 0; i < linhas; i++)
    {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void imprime_matriz(char **tabuleiro, int linhas, int colunas){
    usleep(100000);
    system("clear");
    for (int i = 0; i < linhas; i++)
    {  
        for (int j = 0; j < colunas; j++)
        {
            if(tabuleiro[i][j] == VIVO)
                printf("\033[1;33m");
            else if(tabuleiro[i][j] == MORTO)
                printf("\033[1;36m");
            printf("%c",tabuleiro[i][j]);   
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    // Definição, preenchimento e verificação dos dados inseridos antes do tabuleiro ser definido.
    int linhas, colunas, geracoes;
    char modelo;
    
    scanf("%d %d", &linhas, &colunas);
    scanf("%d", &geracoes);
    if(linhas <= 0 || colunas <= 0 || geracoes <= 0 ){
        printf("Dados de entrada apresentam erro.\n");
        exit(0);
    }

    scanf(" %c%*c", &modelo);
    if(modelo != MOORE && modelo != NEUMANN){
        printf("Dados de entrada apresentam erro.\n");
        exit(0);
    }

    // Matriz de char dinamicamente alocada que serve de tabuleiro. Preenchido depois.
    char **tabuleiro = malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++)
    {
        tabuleiro[i] = malloc(colunas * sizeof(char));
    }
    
    for (int i = 0; i < linhas; i++)
    {  
        for (int j = 0; j < colunas - 1; j++)
        {
            scanf("%c",&tabuleiro[i][j]);    
        }
        scanf("%c%*c", &tabuleiro[i][colunas - 1]);// Evitar de sempre perguntar se tá no ultimo caractere pra ignorar o '\n'
    }
    
    // Definição de calculo das células de acordo com o modelo e o próprio calculo.
    if (modelo == MOORE)
    {
        for (int i = 0; i < geracoes; i++)
        {
            calcular_moore(tabuleiro, linhas, colunas);
            imprime_matriz(tabuleiro, linhas, colunas);
        }
    }
    else{
        for (int i = 0; i < geracoes; i++)
        {
            calcular_von_neumann(tabuleiro, linhas, colunas);
            imprime_matriz(tabuleiro, linhas, colunas);
        }
    }
    
    // Print do último tabuleiro.
    imprime_matriz(tabuleiro, linhas, colunas);

    // Desalocando memória
    liberar_tabuleiro(tabuleiro, linhas);

    return 0;
}

