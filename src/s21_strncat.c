#include "s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
    if (s21_strlen(src) > n) {
        s21_strncpy(dest + s21_strlen(dest), src, n);
    } else {
        s21_strcpy(dest + s21_strlen(dest), src);
    }
    return dest;
}
