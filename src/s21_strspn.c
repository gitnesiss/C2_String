#include "s21_string.h"

s21_size_t s21_strspn(const char* str, const char* sym) {
    char *str1 = (char *)str;
    char *str2 = (char *)sym;
    s21_size_t sum = 0;
    int flag = 0;
    for (s21_size_t i = 0; str1[i] != '\0' && flag == 0; i++) {
        for (int j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                flag = 1;
            }
        }
        if (flag == 1) {
            sum += 1;
            flag = 0;
        } else {
            flag = 1;
        }
    }
    return sum;
}
