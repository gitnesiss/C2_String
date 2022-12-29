#include "s21_string.h"

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
    s21_memmove(dest, src, n);
    *(dest + s21_strlen(dest)) = '\0';
    return dest;
}
