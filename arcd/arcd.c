#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arcd.h"

void adjust_interval(interval* ch,float min,float max,float* prob,char* words,int type_num)
{
    if(min==0 && max==MAX)
    {
        for(int i=0;i<type_num;i++)
            ch[i].correspond_word=words[i];
    }
    ch[0].upper=prob[0]*(max-min)+min;
    ch[0].lower=min;
    for(int i=1;i<type_num;i++)
    {
        ch[i].lower=ch[i-1].upper;
        ch[i].upper=ch[i].lower+prob[i]*(max-min);
    }
}

void show_interval(interval ch[],int type_num)
{
    printf("interval: \n");
    for(int i=0;i<type_num;i++)
    {
        printf("%c : %f ~ %f\n",ch[i].correspond_word,ch[i].lower,ch[i].upper);
    }
}

float arcd_enc(interval* ch,char* ob,float* prob,char* words,int type_num)
{
    int size=strlen(ob);
    int word_type;
    float code;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<type_num;j++)
        {
            if(ob[i]==(ch[j].correspond_word))
            {
                word_type=j;
                break;
            }
        }
        if(i!=(size-1))
        {
            adjust_interval(ch,ch[word_type].lower,ch[word_type].upper,prob,words,type_num);
            //show_interval(ch,type_num);
        }
        else
            code=(ch[word_type].lower+ch[word_type].upper)/2;
    }
    code=code+size;
    return code;
}

void arcd_dec(interval* ch,float code,float* prob,char* words,int type_num,char* decode_result)
{
    int size;
    size=code;
    //printf("size: %d\n",size);
    float t;
    t=size;
    code=code-t;
    //printf("code: %f\n",code);
    int word_type;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<type_num;j++)
        {
            if(code < (ch[j].upper) && code > (ch[j].lower))
            {
                word_type=j;
                break;
            }
        }
        if(i!=(size-1))
        {
            adjust_interval(ch,ch[word_type].lower,ch[word_type].upper,prob,words,type_num);
            //show_interval(ch,type_num);
        }
        decode_result[i]=ch[word_type].correspond_word;
        //printf("choose: %c\n",decode_result[i]);
    }
    decode_result[size]='\0';
}

