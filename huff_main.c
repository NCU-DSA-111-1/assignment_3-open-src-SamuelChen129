#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"huff/huffman.h"
#include"get_freq/get_freq.h"


int main()
{
    /* getting probabilities and words */

    //get the string, and record the chars 
    //and their appearing times into a list.
    char* ob;
    char_info* got;//list that record the appearing times of the chars
    got=NULL;
    ob=(char*)malloc(sizeof(char));
    printf("input:");
    scanf(" %s",ob);
    int size=strlen(ob);
    got=make_list(got,ob,size); 

    //calculate the appearing probability of each different char
    //by the list made above.
    float* probs;
    char*  words;
    int type_num=0;
    probs=(float*)malloc(sizeof(float));
    words=(char*)malloc(sizeof(char));

    get_freq(got,probs,words,&type_num,size);
    
    /************************* huffman coding *********************************/

    sorting_probs(words,probs,type_num);
    
    huff_node* huff_tree;
    huff_tree=make_huff_tree(words,probs,type_num);

    char* char_code[27];
    for(int i=0;i<type_num;i++)
        char_code[i]=(char*)malloc(sizeof(char));
    get_char_code(char_code,huff_tree,words,type_num);
    for(int i=0;i<type_num;i++)
        printf("%c : %s\n",words[i],char_code[i]);

    char* huff_code;
    huff_code=(char*)malloc(sizeof(char));

    // 儲存編碼時間用的變數
    clock_t start_enc, end_enc;

    // 開始計算編碼時間
    start_enc = clock();
    printf("start : %ld\n",start_enc);

    huff_code=huff_enc(char_code,words,ob,type_num);

    // 結束計算編碼時間
    end_enc = time(NULL);
    printf("end : %ld\n",end_enc);

    printf("huffman encode result : %s\n",huff_code);

    // 計算實際編碼花費時間
    clock_t diff_enc ;
    diff_enc=(end_enc-start_enc);
    printf("encode time = %ld\n", diff_enc);

    
    char* decode_result;
    decode_result=(char*)malloc(sizeof(char));

    // 儲存解碼時間用的變數
    clock_t start_dec, end_dec;
    
    // 開始計算解碼時間
    start_dec = clock();
    printf("start : %ld\n",start_dec);

    decode_result=huff_dec(huff_tree,huff_code);

    // 結束計算解碼時間
    end_dec = clock();
    printf("end : %ld\n",end_dec);

    printf("decode result: %s\n",decode_result);

    // 計算實際解碼花費時間
    clock_t diff_dec ;
    diff_dec=(end_dec-start_dec);
    printf("decode time = %ld\n", diff_dec);
    
}