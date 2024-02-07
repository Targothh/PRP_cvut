#include <stdio.h>
#define OUT_OF_INTERVAL 100
#define EXIT_SUCCES 0

int enumeration();
void print_results();
int number;
int n_count;
int pos_count;
int neg_count;
int odd_count;
int even_count;
int sum;
int max_num;
int min_num;
int ret_code = EXIT_SUCCES;

int main()
{
    while(scanf("%d", &number) == 1) {
        ret_code = enumeration();
        if (ret_code == 100) {
            break;
        }
    }
    if(ret_code == EXIT_SUCCES) {
        print_results();
        return ret_code;
    } else {
        return ret_code;
    }
}

int enumeration()
{
    if(number > 10000 || number < -10000) {
        printf("\nError: Vstup je mimo interval!\n");
        return OUT_OF_INTERVAL;
    }
    if (n_count >= 1) {
        printf(", %d", number);
    }else{ // pri zadani prvniho cisla se nevypise carka
        min_num = number; // pro spravny min a max se uklada prvni cislo
        max_num = number;
        printf("%d", number);
    }
    n_count++;
    if (number > 0) {
        pos_count++;
    } 
    if (number < 0) {
        neg_count++;
    }
    if (number % 2 == 0) {
        even_count++;
    } else {
        odd_count++;
    }
    if (number > max_num) {
        max_num = number;
    }
    if (number < min_num) {
        min_num = number;
    }
    sum = sum + number;
    return 0;
}

void print_results()
{
    printf("\nPocet cisel: %d\n", n_count);
    printf("Pocet kladnych: %d\n", pos_count);
    printf("Pocet zapornych: %d\n", neg_count);
    printf("Procento kladnych: %.2f\n", 100 * (float)pos_count / n_count);
    printf("Procento zapornych: %.2f\n", 100 * (float)neg_count / n_count);
    printf("Pocet sudych: %d\n", even_count);
    printf("Pocet lichych: %d\n", odd_count);
    printf("Procento sudych: %.2f\n", 100 * (float)even_count / n_count);
    printf("Procento lichych: %.2f\n", 100 * (float)odd_count / n_count);
    printf("Prumer: %.2f\n", (float)sum / n_count);
    printf("Maximum: %d\n", max_num);
    printf("Minimum: %d\n", min_num);

}
