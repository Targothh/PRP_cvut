#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 101
#define MAX_PRIME 1000000

void copy_arr(char source[], char destination[], int size)
{
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

int divide(char input_arr[], int divider,int size)
{
    int rem = 0;
    int digit;
    int after;
    char temp_arr[size];
    copy_arr(input_arr, temp_arr, size);
    for(int i = 0; i < size ; i++){
        digit = (rem * 10) + temp_arr[i];
        rem = digit % divider;
        after = digit / divider;
        temp_arr[i] = after;
    }
    if (rem == 0){
        copy_arr(temp_arr, input_arr, size);
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    char array[MAX];
    while(1){
    char c = 0;
    int input = 0;
    int znam = 0;
    while((c = getchar()) != '\n' && c != EOF){
        if(c < '0' || c > '9'){
            fprintf(stderr,"Error: Chybny vstup!\n");
            exit(100);
        }
        array[input] = c;
        input ++;
    }
    for (int i = 0; i < input; i++){
            array[i] = array[i] - '0';
    }

    if ((input == 1 && array[0] == 1)){
        printf("Prvociselny rozklad cisla ");
        for (int i = 0; i < input; i++){
            printf("%d", array[i]);
        }
        printf(" je:\n1\n");
    }else if (input == 1 && array[0] == 0){
        exit(0);
    } else {
        printf("Prvociselny rozklad cisla ");
        for (int i = 0; i < input; i++){
            printf("%d", array[i]);
        }
        printf(" je:\n");
        int count = 0;
        for(int i = 2; i < MAX_PRIME;){
            if (divide(array, i, input) != 0){
                if(count != 0){
                    if(count == 1){
                        if(znam == 0){
                            znam++;
                        }else{
                            printf(" x ");
                        }
                        printf("%d",i);
                    } else{
                        if(znam == 0){
                            znam++;
                        }else{
                            printf(" x ");
                        }
                        printf("%d^%d",i,count);
                    }
                }
                i++;
                count = 0;
            } else {
                count++;
            }
        }
        printf("\n");
    }
    }
    return (0);
}
