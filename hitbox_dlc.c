/*
━━━━━━━━┛ ✠ ┗━━━━━━━━━━━━━━━━┛ ✠ ┗━━━━━━━━
Davi Fagundes, nUSP: 12544013, ICMC USP
━━━━━━━━┓ ✠ ┏━━━━━━━━━━━━━━━━┓ ✠ ┏━━━━━━━━
*/
#include <stdio.h>

int main()
{
    long int x1,x2,largura1,largura2,y1,y2,altura1,altura2;
    long int x1_extremo, x2_extremo, y1_extremo, y2_extremo;
    scanf("%ld %ld %ld %ld",&x1, &y1, &largura1, &altura1);
    scanf("%ld %ld %ld %ld",&x2,&y2, &largura2, &altura2);

    x1_extremo = x1 + largura1;
    x2_extremo = x2 + largura2;
    y1_extremo = y1 + altura1;
    y2_extremo = y2 + altura2;

    if(x1 < x2 && y1 < y2){
        if (x1_extremo < x2 || y1_extremo < y2)
        {
            printf("MISS\n");
        }
        else{
            printf("HIT: %ld %ld %ld %ld\n", x2, y2, x2_extremo < x1_extremo ? largura2 : x1_extremo - x2, y2_extremo < y1_extremo ? altura2 : y1_extremo - y2);
        }
    }
    else{
        if(x1 > x2 && y1 < y2){
            if(x2_extremo < x1 || y1_extremo < y2){
                printf("MISS\n");
            }
            else{
                printf("HIT: %ld %ld %ld %ld\n", x1, y2, x2_extremo < x1_extremo ? x2_extremo - x1 : largura1,y2_extremo < y1_extremo ? altura2 : y1_extremo - y2);
            }
        }
        else if(x1 < x2 && y1 > y2){
            if (x1_extremo < x2 || y2_extremo < y1)
            {
                printf("MISS\n");
            }
            else{
                printf("HIT: %ld %ld %ld %ld\n", x2, y1, x2_extremo < x1_extremo ? largura2 : x1_extremo - x2, y1_extremo < y2_extremo ? altura1 : y2_extremo - y1);
            }
        }
        else{
            if(x2_extremo < x1 || y2_extremo < y1){
                printf("MISS"); 
            }
            else{
                 printf("HIT: %ld %ld %ld %ld\n", x1, y1, x2_extremo < x1_extremo ? x2_extremo - x1 : largura1,y1_extremo < y2_extremo ? altura1 : y2_extremo - y1);
            }
        }   
    }
    return 0;
}