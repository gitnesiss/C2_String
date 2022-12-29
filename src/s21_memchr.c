#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    unsigned char* s = (unsigned char*) str;
    int fl = 0;
    while (n--) {
        if (*s == c) {
            fl = 1;
            break;
        }
        s++;
    }
    return fl ? (void*)s : s21_NULL;
}
