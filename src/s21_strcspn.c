#include "s21_string.h"

s21_size_t s21_strcspn(const char* str, const char* sym) {
s21_size_t rez = 0, i, j;
int flag = 0;
const char* arr = str;
const char* arr1 = sym;
if (*arr1) {
    for (i = 0; arr[i] && flag == 0; i++) {
        for (j = 0; arr1[j]; j++) {
            if (arr[i] == arr1[j]) {
                rez = i;
                flag++;
                break;
            }
        }
         if (arr[i+1] == '\0' && flag == 0) {
                rez = s21_strlen(str);
            }
    }
} else {
    rez = s21_strlen(str);
}
    return rez;
}
