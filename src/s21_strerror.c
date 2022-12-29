#include "s21_string.h"

char* s21_strerror(int errnum) {
    static char rez[50];
    char* arr[] = MASSIV;
    if (errnum >= 0 && errnum < MAX_ERRORLIST) {
        s21_strcpy(rez, arr[errnum]);
    } else {
        char arr1[20];
        s21_itoae(errnum, arr1);
        if (FLAG == 2) {
            s21_strcpy(rez, "Unknown error: ");
        }
        if (FLAG == 1) {
            s21_strcpy(rez, "Unknown error ");
        }
        s21_strcat(rez, arr1);
    }
    return rez;
}

char* s21_itoae(int number, char* destination) {
    int flag = 0;
    if (number < 0) {
        flag = 1;
        number  *= -1;
    }
    int count = 0;
    do {
    int digit = number % 10;
    destination[count++] = digit + '0';
    } while ((number /= 10) != 0);
    if (flag == 1) {
        destination[count] = '-';
        for (int i = 0; i <= count /2; i++) {
            char symbol = destination[i];
            destination[i] = destination[count-i];
            destination[count-i] = symbol;
        }
        destination[count + 1] ='\0';
    } else {
        destination[count] = '\0';
        for (int i = 0; i < count /2; i++) {
            char symbol = destination[i];
            destination[i] = destination[count-i-1];
            destination[count-i-1] = symbol;
    }
    }
    return destination;
}
