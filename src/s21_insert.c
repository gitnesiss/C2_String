#include "s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
    s21_size_t lensrc = s21_strlen(src);
    s21_size_t lenstr = s21_strlen(str);
    s21_size_t i = 0;
    char* dest = s21_NULL;
    if (start_index <= lensrc) {
        dest = malloc((lensrc + lenstr + 1) * sizeof(char));
        for (i = 0; i < start_index; i++) {
            dest[i] = src[i];
        }
        for (i = start_index; *str; str++) {
            dest[i++] = *str;
        }
        for (s21_size_t j = start_index; src[j] != '\0'; j++) {
            dest[i++] = src[j];
        }
        dest[i] = '\0';
    }
    return dest ? dest : s21_NULL;
}
