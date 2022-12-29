#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
      char *ned = s21_NULL;
    if (*needle) {
        while (*haystack && ned == s21_NULL) {
            if ((*haystack == *needle)) {
                if (s21_memcmp(haystack, needle, s21_strlen(needle)) != 0) {
                    ned = s21_NULL;
                } else {
                    ned = (char*)haystack;
                }
            }
            haystack++;
        }
    } else {
        ned = (char*)haystack;
    }
    return ned;
}
