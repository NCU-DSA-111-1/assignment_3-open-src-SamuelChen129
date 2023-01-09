#define MAX 1

typedef struct interval
{
    char  correspond_word;
    float upper;
    float lower;
}interval;

void adjust_interval(interval*,float,float,float*,char*,int);
void show_interval(interval [],int);
float arcd_enc(interval* ,char* ,float* ,char* ,int);
void arcd_dec(interval* ,float ,float* ,char* ,int,char*);
