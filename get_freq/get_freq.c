#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"get_freq.h"

char_info* new_char(char_info* s,char c)
{
    char_info* n;
    n=(char_info*)malloc(sizeof(char_info));
    n->ch=c;
    n->times=1;
    n->next=s;

    char_info* check;
    check=s;
    int dup=0;
    
    while(check!=NULL)
    {
        if((check->ch)==c)
        {
            dup=1;
            break;
        }
        check=check->next;
    }

    if(dup==1)
    {
        (check->times)++;
        free(n);
        return s;
    }
    else
        return n;   
};

char_info* make_list(char_info* got,char* ob,int size)
{
    for(int i=0;i<size;i++)
    {
        got=new_char(got,ob[i]);
    }
    return got;
};

void get_freq(char_info* got,float* prob,char* words,int* type_num,int size)
{
    while(got!=NULL)
    {
        (*type_num)++;
        prob[(*type_num)-1]=(got->times)/size;
        words[(*type_num)-1]=(got->ch);
        char_info* t;
        t=got;
        got=got->next;
        free(t);
    }
}
