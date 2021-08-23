#include <stdio.h>
#include <stdlib.h>
#define INCREMENTAR_VALOR_INDICE '+'
#define DECREMENTAR_VALOR_INDICE '-'
#define INCREMENTAR_INDICE '>'
#define DECREMENTAR_INDICE '<'
#define IMPRIMIR_VALOR_ASCII '.'
#define INICIO_LOOP '['
#define FINAL_LOOP ']' 

int main(int argc, char const *argv[])
{
    FILE *arquivoEscrita = fopen("arquivinho.c","w");
    char entrada;
    fprintf(arquivoEscrita, "#include <stdio.h>\n");
    fprintf(arquivoEscrita, "int main() {\n");
    fprintf(arquivoEscrita, "char mem[30000];\n int i = 0; \n");
    fprintf(arquivoEscrita, "for(int i = 0; i < 30000; i++) {\n \t\t mem[i] = 0;}\n");
    do
    {
        entrada = getchar();
        switch (entrada)
        {
        case INCREMENTAR_VALOR_INDICE:
            fprintf(arquivoEscrita, "\tmem[i]++;\n");
            break;
        case INCREMENTAR_INDICE:
            fprintf(arquivoEscrita, "\ti++;\n");
            break;
        case DECREMENTAR_VALOR_INDICE:
            fprintf(arquivoEscrita, "\tmem[i]--;\n");
            break;
        case DECREMENTAR_INDICE:
            fprintf(arquivoEscrita, "\ti--;\n");
            break;
        case IMPRIMIR_VALOR_ASCII:
            fprintf(arquivoEscrita, "\tputchar(mem[i]);"); 
            break;
        case INICIO_LOOP:
            fprintf(arquivoEscrita, "while(mem[i]){");
            break;
        case FINAL_LOOP:
            fprintf(arquivoEscrita, "}\n");
            break;
        default:
            break;
        }

    } while (entrada != EOF);
    fprintf(arquivoEscrita, "printf(\"\\n\"); for(int j = 0; j < 30000; j++){\n if(mem[j] != 0 ){ printf(\"%%d \", mem[j]);\n }\n }\n printf(\"\\n\");\n return 0;\n }");

    fclose(arquivoEscrita);
    system("gcc arquivinho.c -o arq");
    system("./arq");
    return 0;
}
