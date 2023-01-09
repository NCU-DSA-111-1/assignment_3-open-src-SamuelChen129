#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arcd.h"
#define CHAR_TYPE_NUM 4

int main()
{
    char  words[CHAR_TYPE_NUM]={'a','b','c','d'};
    float prob[CHAR_TYPE_NUM]={0.1,0.2,0.3,0.4};
    float maximum=MAX;
    float minimum=0;
    interval ch[CHAR_TYPE_NUM];
    adjust_interval(ch,minimum,maximum,prob,words,CHAR_TYPE_NUM);//initialize the interval before encoding
    //show_interval(ch,CHAR_TYPE_NUM);

    char* ob="ababcd";
    int s=strlen(ob);
    float size;
    float code;
    size=s;
    code=arcd_enc(ch,ob,prob,words,CHAR_TYPE_NUM);
    printf("encode: %f\n",code);
    printf("real encode: %f\n",code-size);

    char* decode_result;
    decode_result=(char*)malloc(sizeof(char));
    adjust_interval(ch,minimum,maximum,prob,words,CHAR_TYPE_NUM);//initialize the interval before decoding
    //show_interval(ch,CHAR_TYPE_NUM);
    arcd_dec(ch,code,prob,words,CHAR_TYPE_NUM,decode_result);
    printf("decode: %s",decode_result);
}