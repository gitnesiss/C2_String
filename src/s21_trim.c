#include <stdio.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  s21_size_t sizeSrc = s21_strlen(src);
  char *dest = calloc(sizeSrc, sizeof(char));
  char *p = dest;
  while (s21_strchr(trim_chars, *src)) {
    src++;
  }
  while (!s21_strchr(trim_chars, *src)) {
    *p++ = *src++;
  }
  return dest ? dest : s21_NULL;
}
