#include "s21_string.h"

void *s21_to_lower(const char *str) {
    char *str1 = s21_NULL;
    if (str) {
        str1 = (char*)malloc((s21_strlen(str) + 1)*sizeof(char));
    }
    if (str1) {
        s21_strncpy(str1, str, s21_strlen(str) + 1);
        for (char *i = str1; *i; i++) {
            if (*i >= 65 && *i <= 90) {
                *i += 32;
            }
        }
    }
    return (void *)str1;
}
