#include<stdio.h>

#define EXIT_SUCCES 0
#define WRONG_INPUT 100
#define IS_PRIME 2
#define IS_NOT_PRIME 1
#define WAITING_FOR_EVAL 0
#define MAX 1000000 - 1

int ErrorEval(void);
void *PrimeFact(int num, char *prime_array);
char *Eratos(char *arr, int max_num);

int main(void)
{
    int num;
    int ret_val = EXIT_SUCCES;
    char *prime_array;
    char p_arr[MAX];
    prime_array = Eratos(p_arr, MAX);
    while(ret_val == 0 && num != 0){
        if(scanf("%d", &num) == 1){
            if(num > 0){
                PrimeFact(num, prime_array);
            } else if (num == 0) {
                break;
            } else {
                ret_val = ErrorEval();
            }
        } else {
            ret_val = ErrorEval();
        }

    }
    
    return ret_val;
}

void *PrimeFact(int num, char *prime_array)
 {
    int out_l = 0;
    printf("Prvociselny rozklad cisla %d je:\n", num);
    if(num == 1){
        printf("1");
    }
    int num_eval = num;
    for(int i = 2; i <= MAX; i++){
        if(prime_array[i] >= IS_PRIME && num_eval%i == 0){
            num_eval = num_eval/i;
            prime_array[i] += 2;
            i = 1;
        }
    }
    for(int i = 2; i <= MAX; i++){
        if(prime_array[i] > IS_PRIME){
            if(out_l == 0 && (prime_array[i]-2)/2 == 1){
                printf("%d", i);
                prime_array[i] = IS_PRIME;
            } else if (out_l == 0 && (prime_array[i] - 2)/2 != 1){
                printf("%d^%d", i, (prime_array[i] - 2)/2);
                prime_array[i] = IS_PRIME;
            } else if ((prime_array[i]-2)/2 == 1){
                printf(" x %d", i);
                prime_array[i] = IS_PRIME;
            } else {
                printf(" x %d^%d", i, (prime_array[i]-2)/2);
                prime_array[i] = IS_PRIME;
            }
            out_l ++;
        }
    }
    printf("\n");
    return 0;
 }

char *Eratos(char *arr, int max_num)
{
    int index;
    for(int i = 2; i < max_num; i++) { // cele pole nastavim na 1
        arr[i] = WAITING_FOR_EVAL;
    }
    for(int i = 2; i < max_num; i++){
        if (arr[i] == WAITING_FOR_EVAL){
            index = i;
            arr[i] = IS_PRIME;
            for(int j = index + index; j <= max_num; j = j + index){
                arr[j] = IS_NOT_PRIME; // oznaceni nasobku jako neprvocisla
            }
        }
    }
    return arr;
}

int ErrorEval(void)
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return WRONG_INPUT;
}
