/*
━━━━━━━━┛ ✠ ┗━━━━━━━━━━━━━━━━┛ ✠ ┗━━━━━━━━
Davi Fagundes, nUSP: 12544013, ICMC USP
━━━━━━━━┓ ✠ ┏━━━━━━━━━━━━━━━━┓ ✠ ┏━━━━━━━━
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LINHAS 32
#define COLUNAS 64
#define AREIA '#'
#define AGUA '~'
#define CIMENTO '@'
#define AR ' '

char frames[LINHAS][COLUNAS];

void calcular_fisica(){
        char copia[LINHAS][COLUNAS];
        for (int i = 0; i < LINHAS; i++){
                for (int j = 0; j < COLUNAS; j++){
                        copia[i][j] = frames[i][j];
                }
                
        }
        // copia = frame
        // i = x
        // j = y
        for (int i = 0; i < LINHAS; i++){
                for (int j = 0; j < COLUNAS; j++){
                        
                        char esquerda = CIMENTO, direita = CIMENTO, abaixo = CIMENTO, esquerda_cima, direita_cima;
                
                        esquerda_cima = j > 0 ? frames[i][j - 1] : CIMENTO;
                        direita_cima = j < (COLUNAS - 1) ? frames[i][j + 1] : CIMENTO;
                        
                        if(i < (LINHAS - 1)){
                                abaixo = frames[i+1][j];
                                esquerda = j > 0 ? frames[i+1][j - 1] : CIMENTO;
                                direita = j < (COLUNAS - 1) ? frames[i+1][j + 1] : CIMENTO;
                        }

                        if (frames[i][j] == AREIA){
                                
                                if (abaixo == AGUA || abaixo == AR ) // 1
                                {
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i + 1][j];
                                        copia[i + 1][j] = aux;
                                        
                                }
                                else if (esquerda == AGUA || esquerda == AR ) // 2
                                {
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i+1][j - 1];
                                        copia[i+1][j - 1] = aux;
                                }
                                else if(direita == AGUA || direita == AR){ // 3
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i+1][j + 1];
                                        copia[i+1][j + 1] = aux;
                                }      
                        }
                        else if(frames[i][j] == AGUA){
                                if (abaixo == AR ) // 1
                                {
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i + 1][j];
                                        copia[i + 1][j] = aux;
                                }
                                else if (esquerda == AR ) // 2
                                {
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i+1][j - 1];
                                        copia[i+1][j - 1] = aux;
                                }
                                else if(direita == AR){ // 3 
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i+1][j + 1];
                                        copia[i+1][j + 1] = aux;
                                }
                                else if (esquerda_cima == AR ) // 4
                                {
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i][j - 1];
                                        copia[i][j - 1] = aux;
                                } 
                                else if (direita_cima == AR ) // 5
                                {
                                        char aux = copia[i][j];
                                        copia[i][j] = copia[i][j + 1];
                                        copia[i][j + 1] = aux;
                                }   
                        }
                        
                }
                
        }
        for (int i = 0; i < LINHAS; i++){
                for (int j = 0; j < COLUNAS; j++){
                        frames[i][j] = copia[i][j];
                }
                
        }
}

void imprime_matriz(){
        
        usleep(100000);
        system("clear");
        for (int i = 0; i < LINHAS; i++){
                for (int j = 0; j < COLUNAS; j++){
                        if(frames[i][j] == AREIA)
                                printf("\033[1;33m");
                        else if(frames[i][j] == AGUA)
                                printf("\033[1;36m");
                        else if(frames[i][j] == CIMENTO)
                                printf("\033[1;34m");
                        printf("%c", frames[i][j]); 
                }
                printf("\n");
                
        }
        
}

void inicializar_matriz(){
       for (int i = 0; i < LINHAS; i++){
                for (int j = 0; j < COLUNAS; j++){
                        frames[i][j] = AR; 
                }
        } 
}

int main(int argc, char const *argv[])
{
        inicializar_matriz();
        int n_frames, frame_leitura, x, y;
        char nova_particula;

        scanf("%d", &n_frames);

        int frame_atual = 0;
        while (frame_atual < n_frames) {

                // `scanf` retorna EOF quando chega ao fim da entrada.
                int n_lido = scanf(" %d: %d %d %c", &frame_leitura, &x, &y, &nova_particula);

                // Se não há mais partículas a serem criadas, continue até o final
                // da simulação.
                if (n_lido == EOF) {
                        frame_leitura = n_frames;
                }

                // Calcula todos os frames até o próximo frame onde queremos criar
                // uma partícula.
                while (frame_atual < frame_leitura) {
                        printf("frame: %d\n", frame_atual + 1);
                        imprime_matriz();
                        calcular_fisica();
                        frame_atual++;
                }

                // Se há uma particula a ser criada, crie ela.
                if (n_lido != EOF) {
                        frames[y][x] = nova_particula;
                }
        }
    return 0;
}
