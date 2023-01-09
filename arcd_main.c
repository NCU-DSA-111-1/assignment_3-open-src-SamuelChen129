#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arcd/arcd.h"
#include"get_freq/get_freq.h"
#include <time.h>

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
    
    /************************* arcd coding *********************************/
    
    // 儲存時間用的變數
    clock_t start_enc, end_enc;

    interval ch[type_num];
    float arcd_code;

    adjust_interval(ch,0,1,probs,words,type_num);

    // 開始計算編碼時間
    start_enc = clock();
    printf("start : %ld\n",start_enc);

    arcd_code=arcd_enc(ch,ob,probs,words,type_num);

    // 結束計算編碼時間
    end_enc = time(NULL);
    printf("end : %ld\n",end_enc);

    printf("arcd encode result: %f\n",arcd_code);

    // 計算實際編碼花費時間
    clock_t diff_enc ;
    diff_enc=(end_enc-start_enc);
    printf("encode time = %ld\n", diff_enc);

    
    char de[5]="aaaa";
    ob=de;

    clock_t start_dec, end_dec;
    
    adjust_interval(ch,0,1,probs,words,type_num);

    // 開始計算解碼時間
    start_dec = clock();
    printf("start : %ld\n",start_dec);

    arcd_dec(ch,arcd_code,probs,words,type_num,ob);
    
    // 結束計算解碼時間
    end_dec = clock();
    printf("end : %ld\n",end_dec);

    printf("arcd decode result: %s\n",ob);

    // 計算實際解碼花費時間
    clock_t diff_dec ;
    diff_dec=(end_dec-start_dec);
    printf("decode time = %ld\n", diff_dec);

}