typedef struct huff_node_t
{
    struct huff_node_t *parent;
    struct huff_node_t *zero;
    struct huff_node_t *one;
    char  word;
    float freq;

}huff_node;
void sorting_probs(char*,float*,int);
huff_node* new_leaf(char,float);
huff_node* new_parent(huff_node*,huff_node*);
huff_node* make_huff_tree(char*,float*,int);
void get_char_code(char*[],huff_node*,char*,int);
char* huff_enc(char*[],char*,char* ,int );
char* huff_dec(huff_node*,char*);