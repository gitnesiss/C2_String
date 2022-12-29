#include "s21_string.h"

char* s21_strtok(char* str, const char* delitel) {
    static char *word;
    int flag = 1;
    if (str) {
        word = str;
        while (*word && s21_strchr(delitel, *word)) {
            *word++ = '\0';
        }
    }
    if (!*word) {
        flag = 0;
    }
    str = word;
    while (*word && !s21_strchr(delitel, *word)) {
        word++;
    }
    while (*word && s21_strchr(delitel, *word)) {
        *word++ = '\0';
    }
    return flag ? str : s21_NULL;
}
