// Davi Fagundes Ferreira da Silva, nUSP: 12544013
// Instituto de Ciências Matemáticas e Computação, USP.

#include <stdio.h>


int main(int argc, char const *argv[])
{
    // Definição e Preenchimento do vetor.
    int tape[512];
    for (int i = 0; i < 512; i++)
    {
        scanf("%d",&tape[i]);
    }

    printf("Saida do programa:\n");
    
    int i=0;
    while (1)
    {
        //printf("%d\n",i);
        switch (tape[i])
        {
        case 0: // HLT
            printf("\n");
            printf("Estado final da fita:\n");
            
            for (int i = 0; i < 512;i++){
                printf("%d\n", tape[i]);
            }
            return 0;
            break;
        case 1: // ADD
            tape[tape[i+3]] = tape[tape[i+1]] + tape[tape[i+2]];
            i = i+4;
            break;
        case 2: // MUL
            tape[tape[i+3]] = tape[tape[i+1]] * tape[tape[i+2]];
            i = i+4;
            break;
        case 3: // CLT
            if (tape[tape[i+1]] < tape[tape[i+2]]){
                tape[tape[i+3]] = 1;
            }else{
                tape[tape[i+3]] = 0;
            }
            
            /* if (tape[tape[i+1]] > tape[tape[i+2]]){
                tape[tape[i+3]] = 0;
            }*/
            i = i+4;
            break;
        case 4: // CEQ
            if (tape[tape[i+1]] == tape[tape[i+2]]){
                tape[tape[i+3]] = 1;
            }else {
                tape[tape[i+3]] = 0;
            }
            i = i+4;
            break;
        case 5: // JMP
            i = tape[tape[i+1]];  
            break;
        case 6: // JEQ
            if (tape[tape[i+1]] != 0){
                i = tape[tape[i+2]];
            }else{
                i+=3;
            }
            break;
        case 7: // CPY
            tape[tape[i+2]] = tape[tape[i+1]];
            i = i+3; 
            break;
        case 8: // PUT
             printf("%c",tape[tape[i+1]]);
            i = i+2;
            break;
        case 9: // PTN
             printf("%d",tape[tape[i+1]]);
            i = i+2;
            break;
        default: 
            break;
        }
    }  
    return 0;
}

