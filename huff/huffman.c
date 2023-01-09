#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"huffman.h"


void sorting_probs(char* words,float* probs,int type_num)
{
    for(int i=1;i<type_num;i++)
    {
        char  c_tmp;
        float p_tmp;
        int pos_for_put;
        c_tmp=words[i];
        p_tmp=probs[i];
        for(int j=i-1;j>=0;j--)
        {
            pos_for_put=j;
            if(probs[pos_for_put]>p_tmp)
            {
                probs[j+1]=probs[j];
                words[j+1]=words[j];
                if(pos_for_put==0)
                {
                    probs[pos_for_put]=p_tmp;
                    words[pos_for_put]=c_tmp;
                }
            }
            else
            {
                probs[pos_for_put+1]=p_tmp;
                words[pos_for_put+1]=c_tmp;
                break;
            }
        }

    }
}

huff_node* new_leaf(char word,float prob)
{
    huff_node* n;
    n=(huff_node*)malloc(sizeof(huff_node));
    n->word=word;
    n->freq=prob;
    n->parent=NULL;
    n->one=NULL;
    n->zero=NULL;
    return n;
}

huff_node* new_parent(huff_node* zero,huff_node* one)
{
    huff_node* n;
    n=(huff_node*)malloc(sizeof(huff_node));
    n->word='x';
    n->freq=(one->freq)+(zero->freq);
    n->parent=NULL;
    n->one=one;
    n->zero=zero;
    
    zero->parent=n;
    one->parent=n;

    return n;
};

huff_node* make_huff_tree(char* words,float* probs,int type_num)
{
    huff_node *p;
    huff_node *q;
    huff_node *root;
    enum {P=0,Q=1};
    bool who_is_next_leaf=P;
    for(int i=0;i<type_num;i++)
    {
        if(i<2)
        {
            if(who_is_next_leaf==P)
                p=new_leaf(words[i],probs[i]);
            if(who_is_next_leaf==Q)
            {
                q=new_leaf(words[i],probs[i]);
                p=new_parent(p,q);
                root=p;
            }
        }
        else
        {
            if(who_is_next_leaf==P)
            {
                p=new_leaf(words[i],probs[i]);
                q=new_parent(p,root);
                root=q;
            }
            if(who_is_next_leaf==Q)
            {
                q=new_leaf(words[i],probs[i]);
                p=new_parent(root,q);
                root=p;
            }
        }
        who_is_next_leaf=!who_is_next_leaf;
    }
    return root;
}


void get_char_code(char* char_code[],huff_node* huff_tree,char* words,int type_num)
{
    char* tmp;
    huff_node* p_for_enc;
    int code_bit;
    char zero='0';
    char one='1';
    for(int i=type_num-1;i>=0;i--)
    {
        tmp=(char*)malloc(sizeof(char));
        p_for_enc=huff_tree;
        code_bit=0;
        while(p_for_enc!=NULL)
        {
            if(words[i]==(p_for_enc->one->word))
            {
                tmp[code_bit]=one;
                code_bit++;
                break;
            }
            else if(words[i]==(p_for_enc->zero->word))
            {
                tmp[code_bit]=zero;
                code_bit++;
                break;
            }
            else if((p_for_enc->one->word)=='x')
            {
                tmp[code_bit]=one;
                p_for_enc=(p_for_enc->one);
            }
            else if((p_for_enc->zero->word)=='x')
            {
                tmp[code_bit]=zero;
                p_for_enc=(p_for_enc->zero);
            }
            code_bit++;
        }    
        tmp[code_bit]='\0';
        char_code[i]=tmp;
    }
}

char* huff_enc(char* char_code[],char* words,char* ob,int type_num)
{
    size_t size=strlen(ob);
    char* code;
    code=(char*)malloc(sizeof(char));
    for(int i=0;i<type_num;i++)
    {
        if(ob[0]==words[i])
        {
            strcpy(code,char_code[i]);
            //don't write "code=char_code[i]",
            //otherwise the char_code[i] will change while using strcat() at col 221
            break;
        }
    }

    for(int j=1;j<size;j++)
    {
        for(int i=0;i<type_num;i++)
        {
            if(ob[j]==words[i])
            {
                strcat(code,char_code[i]);
                break;
            }
        }
    }
    return code;
}

char* huff_dec(huff_node* huff_tree,char* code)
{
    char* decode_result;
    decode_result=(char*)malloc(sizeof(char));
    
    int size=strlen(code);
    huff_node* p_for_dec;
    p_for_dec=huff_tree;
    int count=0;
    for(int i=0;i<size;i++)
    {
        if(code[i]=='0')
        {
            p_for_dec=(p_for_dec->zero);
        }
        if(code[i]=='1')
        {
            p_for_dec=(p_for_dec->one);
        }
        if((p_for_dec->zero)==NULL && (p_for_dec->one)==NULL)
        {
            decode_result[count++]=(p_for_dec->word);
            p_for_dec=huff_tree;
        }
    }
    decode_result[count]='\0';
    
    return decode_result;
}