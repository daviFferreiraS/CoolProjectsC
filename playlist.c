/*
━━━━━━━━┛ ✠ ┗━━━━━━━━━━━━━━━━┛ ✠ ┗━━━━━━━━
Davi Fagundes, nUSP: 12544013, ICMC USP
━━━━━━━━┓ ✠ ┏━━━━━━━━━━━━━━━━┓ ✠ ┏━━━━━━━━
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// main -> linha 173

typedef struct 
{
    char *nome_musica;
    int duracao;
    char *nome_artista;
} musica;

typedef struct 
{
    char *nome_playlist;
    int qtd_musicas;
    musica musicas[15];
    char *nome_arquivo;
} playlist;

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

// Essa função adiciona a música através do ponteiro da playlist
void adicionar_musica(  playlist *lista ){
    lista->musicas[lista->qtd_musicas].nome_musica = readline();
    lista->musicas[lista->qtd_musicas].nome_artista = readline();
    scanf("%d",&lista->musicas[lista->qtd_musicas].duracao);
    lista->qtd_musicas++; 
}

// Desaloca as strings lidas e alocadas dinamicamente
void desalocar_musicas( playlist *lista ){
    for (int i = 0; i <= lista->qtd_musicas; i++){
        free(lista->musicas[i].nome_musica);
        free(lista->musicas[i].nome_artista);
        lista->musicas[i].duracao = 0;
    }
    
}

// Soma polinomial que interpreta o valor binário como um valor numérico.
// Quanto mais próximo o valor de retorno, mais próximo seu binário está do ideal.
// Não há necessidade de entender o funcionamento dessa função.
void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}

// Essa função imprime a lista usando o ponteiro da playlist e o ponteiro da musica_tocando a fim de
// poder saber qual é a musica tocada no momento de impressão
void imprimir_lista( playlist *lista, musica *musica_tocando){
    printf("---- Playlist: %s ----\n", lista->nome_playlist);
    printf("Total de musicas: %d\n\n", lista->qtd_musicas);
    for (int i = 0; i < lista->qtd_musicas; i++){
        if (musica_tocando == (&lista->musicas[i])){
            printf("=== NOW PLAYING ===\n");
        }
        
        printf("(%d). '%s'\n",i + 1 ,lista->musicas[i].nome_musica);
        printf("Artista: %s\n", lista->musicas[i].nome_artista);
        printf("Duracao: %d segundos\n\n", lista->musicas[i].duracao);
    }
}

// A função salva num arquivo .dat a playlist
void salvar_arquivo(playlist *lista){
    FILE *arquivo_escrita = NULL;
    arquivo_escrita = fopen(lista->nome_arquivo,"wb");
    if(arquivo_escrita == NULL){
        printf("Arquivo %s nao existe.\n", lista->nome_arquivo);
    }
    else{
        // Escrevendo o cabeçalho
        int tamanhoNomePlaylist = strlen(lista->nome_playlist);
        fwrite(&tamanhoNomePlaylist , sizeof(int) , 1, arquivo_escrita);
        fwrite(lista->nome_playlist, sizeof(char), tamanhoNomePlaylist, arquivo_escrita);
        fwrite(&lista->qtd_musicas, sizeof(int), 1, arquivo_escrita);

        // Escrevendo as musicas
        for (int i = 0; i < lista->qtd_musicas; i++){
            int tamanhoNomeMusica = strlen(lista->musicas[i].nome_musica);
            int tamanhoNomeArtista = strlen(lista->musicas[i].nome_artista);
            fwrite(&tamanhoNomeMusica, sizeof(int), 1, arquivo_escrita);
            fwrite(lista->musicas[i].nome_musica, sizeof(char), tamanhoNomeMusica,
            arquivo_escrita);
            fwrite(&tamanhoNomeArtista, sizeof(int), 1, arquivo_escrita);
            fwrite(lista->musicas[i].nome_artista, sizeof(char), tamanhoNomeArtista, 
            arquivo_escrita);
            fwrite(&lista->musicas[i].duracao, sizeof(int), 1, arquivo_escrita);
        }

        fclose(arquivo_escrita);
        printf("Playlist %s salva com sucesso.\n", lista->nome_arquivo);
        binaryToNum(lista->nome_arquivo);
    }
}

// A função carrega para a memória RAM a playlist advinda do arquivo
void carregar_playlist(playlist *lista){
    FILE *arquivoLeitura = fopen(lista->nome_arquivo, "rb");
    if(arquivoLeitura == NULL){
        printf("Arquivo %s nao existe.\n", lista->nome_arquivo);
        free(lista->nome_arquivo);
        free(lista->nome_playlist);
        exit(0);
    }
    else{
        // Lendo o cabeçalho
        int tamanhoNomePlaylist;
        fread(&tamanhoNomePlaylist, sizeof(int), 1, arquivoLeitura);
        free(lista->nome_playlist);
        lista->nome_playlist = malloc( sizeof(char) * (tamanhoNomePlaylist + 1));
        fread(lista->nome_playlist, sizeof(char), tamanhoNomePlaylist, arquivoLeitura);
        lista->nome_playlist[tamanhoNomePlaylist] = '\0';
        fread(&lista->qtd_musicas, sizeof(int), 1, arquivoLeitura);

        // Limpeza das musicas
        for (int i = 0; i < lista->qtd_musicas; i++){
            free(lista->musicas[i].nome_musica);
            free(lista->musicas[i].nome_artista);
        }
        // Preenchimento das musicas
        for (int i = 0; i < lista->qtd_musicas; i++){
            int tamanhoNomeMusica;
            int tamanhoNomeArtista;

            fread(&tamanhoNomeMusica, sizeof(int), 1, arquivoLeitura);
            lista->musicas[i].nome_musica = malloc( sizeof(char) * (tamanhoNomeMusica + 1));
            fread(lista->musicas[i].nome_musica, sizeof(char), tamanhoNomeMusica,
            arquivoLeitura);
            lista->musicas[i].nome_musica[tamanhoNomeMusica] = '\0';

            fread(&tamanhoNomeArtista, sizeof(int), 1, arquivoLeitura);
            lista->musicas[i].nome_artista = malloc( sizeof(char) * (tamanhoNomeArtista + 1));
            fread(lista->musicas[i].nome_artista, sizeof(char), tamanhoNomeArtista, 
            arquivoLeitura);
            lista->musicas[i].nome_artista[tamanhoNomeArtista] = '\0';
            fread(&lista->musicas[i].duracao, sizeof(int), 1, arquivoLeitura);
        }

        fclose(arquivoLeitura);
        printf("Playlist %s carregada com sucesso.\n",lista->nome_arquivo);
        binaryToNum(lista->nome_arquivo);
    }
}

// O valgrind tava dano esse erro, aí criou-se essa função de inicializar as musicas
void inicializar_musicas(musica *musicas){
    for (int i = 0; i < 15; i++){
        musicas[i].nome_musica = NULL;
        musicas[i].nome_artista = NULL;
        musicas[i].duracao = 0;
    }
    
}

int main(int argc, char const *argv[]){
    playlist lista;
    inicializar_musicas(lista.musicas);
    lista.qtd_musicas = 0;
    lista.nome_playlist = readline();
    int comando = 0,indice_musica = 0;
    
    // indice_musica representa o indice dentro do vetor de musicas, que vai mudando dependendo do usuario

    musica *musica_tocando = &lista.musicas[indice_musica];

    while (comando != 7){
        scanf("%d%*c", &comando);
        switch (comando)
        {
        case 1:
            if(lista.qtd_musicas < 15){
                adicionar_musica(&lista);
                printf("Musica %s de %s adicionada com sucesso.\n", 
                lista.musicas[lista.qtd_musicas - 1].nome_musica,
                lista.musicas[lista.qtd_musicas - 1].nome_artista);
            }
            else{
                printf("Playlist cheia!\n");
            }
            break;
        case 2:
            imprimir_lista(&lista, musica_tocando);
            break;

        // Os casos 3 e 4 vão retornar o endereço da musica para o ponteiro musica_tocando a fim de
        // poder comparar lá no print qual é a musica que está tocando.

        case 3:
            musica_tocando = &lista.musicas[++indice_musica];
            break;
        case 4:
            musica_tocando = &lista.musicas[--indice_musica];
            break;
        case 5:
            lista.nome_arquivo = readline();
            salvar_arquivo(&lista);
            break;
        case 6:
            lista.nome_arquivo = readline();
            carregar_playlist(&lista);
            musica_tocando = &lista.musicas[0];
            break;
        case 7: 
            desalocar_musicas(&lista);
            free(lista.nome_playlist);
            free(lista.nome_arquivo);
            break;
        default:
            break;
        }
    }
    
    return 0;
}