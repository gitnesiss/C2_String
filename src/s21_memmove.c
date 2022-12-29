#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
        if (dest <= src) {
            char *d = (char *)dest;
            char *s = (char *)src;
            while (n--) {
                *d++ = *s++;
            }
        } else {
            char *d = (char *)dest + n;
            char *s = (char *)src + n;
            while (n--) {
                *--d = *--s;
            }
        }
    return dest;
}
