#include<stdio.h>
#include<stdlib.h>
#include"d_b.h"

int main()
{
    int b[MAX_BIT];
    float d,d1;
    d=0.5;
    d_to_b(b,d);
    for(int i=0;i<MAX_BIT;i++)
        printf("%d",b[i]);
    printf("\n");
    b_to_d(b,&d1);
    printf("%f",d1);
}