#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int rez = 0;
    const unsigned char* s1 = (unsigned char*) str1;
    const unsigned char* s2 = (unsigned char*) str2;
    if (n) {
        while (n) {
            if (*s1 != *s2) {
                rez = (*s1 - *s2);
                break;
            }
            s1++;
            s2++;
            n--;
        }
    }
    return rez;
}

