#include<stdio.h>
#include<stdlib.h>
#include"d_b.h"

float power(int x,int n)
{
    float a=1;
    for(int i=0;i<n;i++)
    {
        a=a*x;
    }
    return a;
}
void b_to_d(int b[] ,float* d)
{
    float t=0;
    float t1;
    for(int i=0;i<MAX_BIT;i++)
    {
        t1=b[i];
        t=t+t1/power(2,i+1);
    }
    *d=t;
}
void d_to_b(int b[] ,float d)
{
    int bit;
    float t;
    for(int i=0;i<MAX_BIT;i++)
    {
        bit=2*d;
        t=bit;
        d=d*2;
        d=d-t;
        b[i]=bit;
    }
}
