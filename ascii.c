#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int eixo_x;
    int eixo_y;
    char cor;
} ponto_t;

typedef struct 
{
    char *nome_desenho;
    int qtd_linhas;
    int qtd_colunas;
    char **matriz;
} desenho_t;


void receberDesenho(desenho_t *desenho);

char *readline();

void imprimirDesenho(desenho_t desenho);

void pintarDesenho(desenho_t *desenho, ponto_t ponto, char original);

void escreverArquivo();

void enquadra_arte(char *nome_do_arquivo_da_arte, int  altura_do_quadro, int  largura_do_quadro);

void salvarDesenho(desenho_t desenho);

int main(int argc, char const *argv[]){
    desenho_t desenho;
    desenho.nome_desenho = readline();
    desenho.qtd_linhas = 0;
    desenho.qtd_colunas = 0;
    desenho.matriz = NULL;
    int etapa;
    char caractere_original;


    receberDesenho(&desenho);
    scanf("%d%*c", &etapa);
    printf("Arte inicial:\n");
    imprimirDesenho(desenho);
    
    for (int i = 0; i < etapa; i++)
    {
        ponto_t ponto;
        scanf("%c %d%*c %d%*c", &ponto.cor, &ponto.eixo_x, &ponto.eixo_y);
        caractere_original = desenho.matriz[ponto.eixo_x][ponto.eixo_y];
        pintarDesenho(&desenho, ponto, caractere_original);
        printf("\nArte apos a etapa %d:\n", i);
        imprimirDesenho(desenho);
    }
    salvarDesenho(desenho);
    printf("\nArte enquadrada:\n");
    enquadra_arte(desenho.nome_desenho,desenho.qtd_linhas, desenho.qtd_colunas);
 
    // desalocando o desenho todo
    for (int i = 0; i < desenho.qtd_linhas; i++)
    {
        free(desenho.matriz[i]);
    }
    free(desenho.matriz);
    free(desenho.nome_desenho);
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
// Aloca e preenche a matriz do desenho
void receberDesenho(desenho_t *desenho){ 
    char entrada;
    FILE *arquivoLeitura = fopen(desenho->nome_desenho,"r");
    int controle;

    do{
        desenho->qtd_linhas++;
        desenho->matriz = realloc( desenho->matriz , sizeof(char *) * desenho->qtd_linhas);
        desenho->matriz[desenho->qtd_linhas - 1] = NULL;
        desenho->qtd_colunas = 0;
        do{
            controle = fscanf(arquivoLeitura, "%c", &entrada);
            desenho->qtd_colunas++;
            desenho->matriz[desenho->qtd_linhas - 1] = realloc( desenho->matriz[desenho->qtd_linhas - 1], 
                sizeof(char) * desenho->qtd_colunas);
            desenho->matriz[desenho->qtd_linhas- 1][desenho->qtd_colunas - 1] = entrada;

        } while (entrada != '\n' && controle != EOF);
        desenho->qtd_colunas--;
        desenho->matriz[desenho->qtd_linhas - 1] = realloc( desenho->matriz[desenho->qtd_linhas - 1], 
            sizeof(char) * desenho->qtd_colunas); 
    } while (controle != EOF);
    fclose(arquivoLeitura);
}
// Printa a matriz do desenho
void imprimirDesenho(desenho_t desenho){
    for (int i = 0; i < desenho.qtd_linhas; i++)
    {
        for (int j = 0; j < desenho.qtd_colunas; j++)
        {
            printf("%c", desenho.matriz[i][j]);   
        }
        printf("\n");
    }
}
// Recursão pra pintar o desenho
void pintarDesenho(desenho_t *desenho, ponto_t ponto, char original){
    // Checar se ponto(x,y) é válido
    if((ponto.eixo_x >= 0 && ponto.eixo_x < desenho->qtd_linhas)
    && (ponto.eixo_y >= 0 && ponto.eixo_y < desenho->qtd_colunas)){
        // ponto_original(x,y) == ponto_matriz(x,y) 
        if ( desenho->matriz[ponto.eixo_x][ponto.eixo_y] == original ){
            desenho->matriz[ponto.eixo_x][ponto.eixo_y] = ponto.cor;
            ponto.eixo_x -=1;
            pintarDesenho(desenho, ponto, original);
            ponto.eixo_x += 2;
            pintarDesenho(desenho, ponto, original);
            ponto.eixo_x -=1;
            ponto.eixo_y -=1;
            pintarDesenho(desenho, ponto, original);
            ponto.eixo_y+=2;
            pintarDesenho(desenho, ponto, original);
        }
    }
}
// Escrever o desenho num arquivo
void salvarDesenho(desenho_t desenho){
    FILE *arquivo_escrita = fopen(desenho.nome_desenho, "w");
    for (int i = 0; i < desenho.qtd_linhas; i++)
    {
        for (int j = 0; j < desenho.qtd_colunas; j++)
        {
            fprintf(arquivo_escrita, "%c", desenho.matriz[i][j]);
        }
        if(i != desenho.qtd_linhas - 1)
            fprintf(arquivo_escrita, "\n" );
    }
    fclose(arquivo_escrita);
}
// Função de vcs que enquadra a arte
void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro
) {
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}
