# huffman coding v.s. arcd coding 
## compile
1. open terminal and enter 
```
g++ huff_main.c get_freq\get_freq.c huff\huffman.c -o huff_main
```
get you will get the _huff_main.exe_
2. enter 
```
g++ arcd_main.c get_freq\get_freq.c arcd\arcd.c -o arcd_main
```
get you will get the _arcd_main.exe_
## Run arcd coding
1. enter the instruction below after compiling
```
./arcd_main
```
2. enter a random string (not too long) beside   "input :", you will get the encoding and decoding
results of arcd coding, include the execution time (unit: clock cycle).

## Run huffman coding
1. enter the instruction below after compiling
```
./huff_main
```
2. enter a string that is same as the input string of arcd coding, you will get the encoding and decoding
results of huff coding, include the execution time (unit: clock cycle).

_p.s._ huffman coding's input should be same as the arcd coding's, otherwise the comparison of the excution time of each coding method is pointless.

## method 
### get appearing frequency of each type symbol
First, I make a linked list . each element on the these contain the type of appearing symbols and the appearing times to each different type of symbol.  

Everytime the program get a symbol of the type that hasn't saved in the list, the type of the symbol will be add to the list and its appearing times will be set as 1. 
If the type of symbol gotten has saved in the list , the appearign times of thie type will be plused 1 (by the "new_char" function):
```sh
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
```

After all of the type of symbol in the input string are recorded by the list, the program will calculate probabilty of each type of the symbols.
And the probabilities and types will be written into the probs[] and words[] separately (by the "get_freq" function):
```sh
void get_freq(char_info* got,float* prob,char* words,int* type_num,int size)
{
    while(got!=NULL)
    {
        (*type_num)++;
        probs[(*type_num)-1]=(got->times)/size;
        words[(*type_num)-1]=(got->ch);
        char_info* t;
        t=got;
        got=got->next;
        free(t);
    }
}
```
By the ways the probability of the correspond type is at the same number of the array, i.e. the  appearing probabilty of words[n] is probs[n].
### arcd encoding
First ,I define a struct called interval:
```sh
typedef struct interval
{
    char  correspond_word;
    float upper;
    float lower;
}interval;
```
it contains the type of symbol's upper bound and lower bound and ,of course,the type of the symbol.

And I make an "interval" array for the arcd coding, just like the picture below.
![image](interval.PNG)

Take an example, if there's 4 symbol types ,the "interval" array will have 4 element. The array will be initialize with upper[3]=1,lower[0]=0, other upper and lower bound will be calculated by the data of probs array, which is created while the <font color=orange>"get appearing frequency of each type symbol"</font> step.  
While encoding, the first symbol of the string comes in, and the correspond upper bound and lower bound will be chosen to be the next upper[3] and lower[0], and the next symbol comes in , and so on. (by "adjust_interval" function)
```sh
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
```
Until the last symbol of the string comes in ,the median of correspond upper bound and lower bound will be chosen to be the code of this string.(by "arcd_enc" funciton)
```sh
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
```
The most important is that I make this code plus the size of the string so that the decode result of the code won't be infinitely long.
### arcd decoding
First, I initialize the "interval" array with upper[3]=1 and lower[0]=0, if there are 4 element in the array. Meanwhile I seperate the size from the code.

Next, the code is between an upper bound and a lower bound of an element, so the first symbol of the decode result will be the type of the symbol that is correspond to the pair of upper and lower bound,  and the correspond upper bound and lower bound will be chosen to be the next upper[3] and lower[0]. After that, use the adjusted "interval" array and the code to get the next symbol, and get the correspond symbol as the deocode result ,and adjust "interval" array,and so on.
Until the number of the gotten symbol is equal to the size, the decode result is complete.
(by "arcd_dec" function)
```sh
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
```

### huffman encoding 
First, I sort the probs array from small to large. After sorting ,the order of words array will still be correspond to the probs array.
(by "sorting_probs" function) 
```sh
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
```

Next, I make a tree that is for encoding.
The struct of the tree node is this:
```sh
typedef struct huff_node_t
{
    struct huff_node_t *parent;
    struct huff_node_t *zero;
    struct huff_node_t *one;
    char  word;
    float freq;

}huff_node;
```
The tree is started by the two node of the two symbol types that has the smallest probabilties.  
And I make a parent of the both node (one connect to the "zero" pointer ,another connect to the "one" pointer), with the parent is given a specific symbol, 'x', so that this node won't be take as the nodes we need while encoding and decoding.  
And the next symbol type that has the smallest probability is add to the tree , by making a new parent node connect to this symbol node and the last created parent node (the symbol node and the last created parent node are connected to the new parent node's "one" and "zero" pointer seperately).
Keeping making tree until there's no more type of symbols.(by "make_huff_tree" function)
```sh
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
```

After making the tree, I give every symbols a correspond code according to the tree.
For example (from the picture below)
![image](huff_tree.PNG)
the code of 't' is 111, the code of 'r' is '1100'
,the code of 'e' is 011. (by "get_char_code" function)
```sh
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
``` 
(the code is the route from the top root to the correspond symbol)
And I encode the string by assembling the symbols' code.   
For example, "tree" will encode to 111 1100 011 011. (by "huff_enc" funciton)
```sh
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
```
### huffman decoding
According to the code ,start from the top root of the huffman tree and go down , if a symbol is gotten , the symbol will be saved to the first decode result.   
After saved the symbol , back to the top root,and continue using the code to go down and find the next symbol of the decode result.  
After find the symbol and saved it , go back to the top root and so on,until all of the code is used. (by "huff_dec" function)
```sh
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
```
