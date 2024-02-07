#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define MEMORY_ERROR 99
#define WRONG_INPUT 100
#define WRONG_INPUT_SIZE 101

int ErrorEval(int ret_val);
int StrLoad(void);
int StrShift(char *p_cr_msg, char *p_og_msg, int str_lenght);
void FreeMem(char *p_cr_msg, char *p_og_msg);

int main(int argc, char *argv[])
{
    int ret_val = EXIT_SUCCESS;
    char flag[] = "-prp-optional";
    if (argc > 1 && strcmp(argv[1], flag) == 0) {
        printf("neco");
    } else {
        ret_val = StrLoad();
    }
    return ret_val;
}

int ErrorEval(int ret_val)
{
    switch (ret_val) {
    case MEMORY_ERROR:
        fprintf(stderr,"Memory Error\n");
        return MEMORY_ERROR;
    
    case WRONG_INPUT:
        fprintf(stderr,"Error: Chybny vstup!\n");
        return WRONG_INPUT;
    
    case WRONG_INPUT_SIZE:
        fprintf(stderr,"Error: Chybna delka vstupu!\n");
        return WRONG_INPUT_SIZE;
    }
    return EXIT_SUCCESS;
}

int StrLoad(void)
{
    int str_lenght = 10;
    char *p_cr_msg;
    char *p_og_msg;
    char c;
    int wrong_input = 0;
    int i;
    int j;
    if ((p_cr_msg = (char *) malloc(str_lenght + 1)) == NULL
    || (p_og_msg = (char *) malloc(str_lenght + 1)) == NULL ){
        return ErrorEval(MEMORY_ERROR);
    }
    for (i = 0; (c = getchar()) != '\n'; i++) {
        if (i >= str_lenght) {
            str_lenght += 10;
            if((p_cr_msg = (char *) realloc(p_cr_msg, str_lenght + 1)) == NULL){
                return ErrorEval(MEMORY_ERROR);
            }
        }
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            *(p_cr_msg + i) = c;
        } else {
            *(p_cr_msg + i) = c;
            wrong_input = 1;
        }
    }
    *(p_cr_msg + i) = '\0';
    str_lenght = 10;
    for (j = 0; (c = getchar()) != '\n'; j++) {
        if (j >= str_lenght) {
            str_lenght += 10; //pro pripad vetsiho druheho str na inputu
            if((p_og_msg = (char *) realloc(p_og_msg, str_lenght + 1)) == NULL){
                return ErrorEval(MEMORY_ERROR);
            }
        }
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            *(p_og_msg + j) = c;
        } else {
            *(p_og_msg + i) = c;
            wrong_input = 1;
        }
    }
    *(p_og_msg + j) = '\0';
    if ((strlen(p_cr_msg) != strlen(p_og_msg)) || strlen(p_cr_msg) == 0) {
        FreeMem(p_cr_msg, p_og_msg);
        return ErrorEval(WRONG_INPUT_SIZE);
    }
    if (wrong_input == 1){
        FreeMem(p_cr_msg, p_og_msg);
        return ErrorEval(WRONG_INPUT);
    }
    return StrShift(p_cr_msg, p_og_msg, str_lenght);
}

int StrShift(char *p_cr_msg, char *p_og_msg, int str_lenght)
{
    int best_shift = 0;
    int count = 0;
    char *p_result;
    if ((p_result = (char *) malloc(str_lenght + 1)) == NULL){
        return ErrorEval(MEMORY_ERROR);
    }
    for (int i = 0; i < 52; i++){
        for(int j = 0; *(p_cr_msg + j) != '\0'; j++){
            *(p_cr_msg + j) = *(p_cr_msg + j) + 1;
            if (*(p_cr_msg + j) > 'Z' && *(p_cr_msg + j) < 'a'){
                *(p_cr_msg + j) = 'a';
            }
            if (*(p_cr_msg + j) > 'z'){
                *(p_cr_msg + j) = 'A';
            }
        }
        for (int i = 0; *(p_cr_msg + i) != '\0'  ; i++){
            if (*(p_cr_msg + i) == *(p_og_msg + i)) {
                count++;
            }
        }
        if (count > best_shift) {
            best_shift = count;
            int j;
            for(j = 0; *(p_cr_msg + j) != '\0'; j++){
                p_result[j] = *(p_cr_msg + j);
            }
            p_result[j] = '\0';
        }
        count = 0;
    }
    for (int i = 0; p_result[i] != '\0'; i++){
        printf("%c", p_result[i]);
    }
    printf("\n");
    free(p_result);
    FreeMem(p_cr_msg, p_og_msg);
    return EXIT_SUCCESS;
}

void FreeMem(char *p_cr_msg, char *p_og_msg)
{
    free(p_cr_msg);
    free(p_og_msg);
}
