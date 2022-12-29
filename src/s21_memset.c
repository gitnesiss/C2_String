#include "s21_string.h"

void *s21_memset(void *dest, int c, s21_size_t n) {
    char* d = (char*)dest;
    for (s21_size_t i = 0; i != n; ++i) {
        d[i] = c;
    }
    return dest;
}
