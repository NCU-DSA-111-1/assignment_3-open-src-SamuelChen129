typedef struct char_info_t
{
    char ch;
    float times;
    struct char_info_t* next;
}char_info;

char_info* new_char(char_info*,char );
char_info* make_list(char_info*,char*,int);
void get_freq(char_info* ,float* ,char* ,int* ,int );