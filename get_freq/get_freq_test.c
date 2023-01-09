#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "get_freq.h"


int main()
{
    char* object;
    object=(char*)malloc(sizeof(char));
    scanf(" %s",object);
    float size=strlen(object);
    char_info* got;
    got=NULL;
    got=make_list(got,object,size);
    printf("\n");
    
    float* prob;
    char*  words;
    prob=(float*)malloc(sizeof(float));
    words=(char*)malloc(sizeof(char));
    int type_num=0;
    get_freq(got,prob,words,&type_num,size);
    printf("num of type: %d\n",type_num);
    for(int i=0;i<type_num;i++)
    {
        printf("%c : %f\n",words[i],prob[i]);
    }
}