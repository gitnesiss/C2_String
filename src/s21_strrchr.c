#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
    int i = s21_strlen(str), fl = 0;
    char *sn = (char*)str;
    while (i > 0 && sn[i] != c) {
        i--;
    }
    if (sn[i] == c) {
        fl = 1;
        for (int j = 0; j < i; j++) {
            sn++;
        }
    }
    return fl ? (char*) sn : s21_NULL;
}
