#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"huffman.h"

#define TYPE_NUM 4



int main()
{
    char words[TYPE_NUM]={'a','b','c','d'};
    float probs[TYPE_NUM]={0.4,0.2,0.3,0.1};
    
    sorting_probs(words,probs,TYPE_NUM);
    
    huff_node* huff_tree;
    huff_tree=make_huff_tree(words,probs,TYPE_NUM);

    char* char_code[27];
    for(int i=0;i<TYPE_NUM;i++)
        char_code[i]=(char*)malloc(sizeof(char));
    get_char_code(char_code,huff_tree,words,TYPE_NUM);
    for(int i=0;i<TYPE_NUM;i++)
        printf("%c : %s\n",words[i],char_code[i]);

    char* code;
    code=(char*)malloc(sizeof(char));
    char* ob;
    ob=(char*)malloc(sizeof(char));
    printf("input: ");
    scanf(" %s",ob);
    code=huff_enc(char_code,words,ob,TYPE_NUM);
    printf("code : %s\n",code);
    
    char* decode_result;
    decode_result=huff_dec(huff_tree,code);
    printf("decode result: %s\n",decode_result);

}

