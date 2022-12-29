#include <stdio.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int amountSymbols = 0;

  while (*format) {
    if (*format == '%') {
      int counter = 0;
      const char *spec = format + 1;
      char exp[100] = "\0";
      char flag[100] = "\0";
      s21_size_t width = 0;
      int precision = -1;
      char specifier[100] = "\0";

      if (*spec == '%') {
        *str++ = '%';
        format++;
        amountSymbols++;
      } else {
        while (!s21_strchr("cdifsu", spec[counter - 1])) {
          exp[counter] = spec[counter];
          counter++;
        }
        parseExp(exp, flag, &width, &precision, specifier);
      }

      // formating

      if (*specifier == 'd' || *specifier == 'i' || specifier[1] == 'd' ||
          specifier[1] == 'i' || *specifier == 'u' || specifier[1] == 'u') {
        if (precision == -1) precision = 0;
        char *formatValue = formatInt(args, flag, width, precision, specifier);
        char *p = formatValue;

        while (*p) {
          *str++ = *p++;
          amountSymbols++;
        }

        free(formatValue);
      } else if (s21_strchr(specifier, 'f')) {
        double value = va_arg(args, double);
        if (precision == -1) precision = 6;
        char *formatValue = formatFloat(value, flag, width, precision);
        char *p = formatValue;

        while (*p) {
          *str++ = *p++;
          amountSymbols++;
        }
        free(formatValue);
      } else if (*specifier == 's' || specifier[1] == 's') {
        char *value = va_arg(args, char *);
        char *formatValue = formatStr(value, flag, width, precision);
        char *p = formatValue;
        while (*p) {
          *str++ = *p++;
          amountSymbols++;
        }
        free(formatValue);

      } else if (*specifier == 'c' || specifier[1] == 'c') {
        char value = (char)va_arg(args, int);
        if (width) {
          int sideFlag = s21_strchr(flag, '-') ? 1 : 0;
          char *formatValue = calloc(width + 1, sizeof(char));
          char *p = formatValue;
          char *strChar = calloc(3, sizeof(char));
          *strChar = value;
          formatWidth(strChar, formatValue, width, sideFlag);
          while (*p) {
            *str++ = *p++;
            amountSymbols++;
          }
          free(strChar);
          free(formatValue);
        } else {
          *str++ = value;
          amountSymbols++;
        }
      }
      format += counter + 1;
    } else {
      *str++ = *format++;
      amountSymbols++;
    }
    *str = '\0';
  }
  va_end(args);
  return amountSymbols;
}

int s21_atoi(char *str) {
  int result = 0;
  while (*str >= '0' && *str <= '9') {
    result *= 10;
    result += *str++;
    result -= '0';
  }
  return result;
}

char *s21_itoa(int number) {
  char *destination = calloc(30, sizeof(char));
  int negative = number < 0;
  int count = 0;

  do {
    int digit = number % 10;
    if (negative) {
      destination[count++] = -1 * digit + '0';
    } else {
      destination[count++] = digit + '0';
    }
  } while ((number /= 10) != 0);
  if (negative) {
    destination[count] = '-';
    count++;
  }
  destination[count] = '\0';
  for (int i = 0; i < count / 2; ++i) {
    char symbol = destination[i];
    destination[i] = destination[count - i - 1];
    destination[count - i - 1] = symbol;
  }

  return destination;
}

char *s21_ltoa(long number) {
  char *destination = calloc(30, sizeof(char));
  int negative = number < 0;
  int count = 0;

  do {
    int digit = number % 10;
    if (negative) {
      destination[count++] = -1 * digit + '0';
    } else {
      destination[count++] = digit + '0';
    }
  } while ((number /= 10) != 0);
  if (negative) {
    destination[count] = '-';
    count++;
  }
  destination[count] = '\0';
  for (int i = 0; i < count / 2; ++i) {
    char symbol = destination[i];
    destination[i] = destination[count - i - 1];
    destination[count - i - 1] = symbol;
  }

  return destination;
}

char *s21_utoa(unsigned long number) {
  char *destination = calloc(30, sizeof(char));
  int count = 0;
  do {
    int digit = number % 10;
    destination[count++] = digit + '0';
  } while ((number /= 10) != 0);

  destination[count] = '\0';
  for (int i = 0; i < count / 2; ++i) {
    char symbol = destination[i];
    destination[i] = destination[count - i - 1];
    destination[count - i - 1] = symbol;
  }

  return destination;
}

char *s21_hutoa(unsigned short number) {
  char *destination = calloc(30, sizeof(char));
  int count = 0;
  do {
    int digit = number % 10;
    destination[count++] = digit + '0';
  } while ((number /= 10) != 0);

  destination[count] = '\0';
  for (int i = 0; i < count / 2; ++i) {
    char symbol = destination[i];
    destination[i] = destination[count - i - 1];
    destination[count - i - 1] = symbol;
  }

  return destination;
}

char *s21_ftoa(double number, int precision) {
  char *destination = calloc(30, sizeof(char));
  char *destPtr = destination;

  if (isnan(number)) {
    s21_strcpy(destination, "nan");
  } else {
    int negative = number < 0;
    if (negative) number *= -1;
    long exp = pow(10.0, precision);

    if (negative) *(destPtr++) = '-';
    if (!precision) {
      number = floor(number + 0.5);
    }

    long intPart = (long)number;
    double floatPart = ((number - intPart) * exp + 0.5) / exp;
    char *intStr = s21_ltoa(intPart);

    char *p = intStr;
    while (*p) {
      *destPtr++ = *p++;
    }
    if (precision != 0) {
      *destPtr++ = '.';
      int digit = floor(floatPart * 10);
      for (int i = 0; i < precision; i++) {
        *destPtr++ = digit + '0';
        floatPart *= 10;
        floatPart -= digit;
        digit = floor(floatPart * 10);
      }
    }
    *destPtr = '\0';

    free(intStr);
    // free(floatStr);
  }

  return destination;
}

int parseExp(char *exp, char *flag, s21_size_t *width, int *precision,
             char *specifier) {
  char flags[] = "+- ";
  char numbers[] = "1234567890";
  char *widthStr = calloc(100, sizeof(char));
  char *precisionStr = calloc(100, sizeof(char));
  int errorFlag = 0;

  s21_size_t counter = s21_strspn(exp, flags);
  if (counter) {
    for (s21_size_t i = 0; i < counter; i++) {
      flag[i] = exp[i];
    }
    exp += counter;
  }

  counter = s21_strspn(exp, numbers);
  if (counter) {
    for (s21_size_t i = 0; i < counter; i++) {
      widthStr[i] = exp[i];
    }
    exp += counter;
    *width = s21_atoi(widthStr);
  }

  if (*exp == '.') {
    exp++;
    counter = s21_strspn(exp, numbers);
    if (counter) {
      for (s21_size_t i = 0; i < counter; i++) {
        precisionStr[i] = exp[i];
      }
      *precision = s21_atoi(precisionStr);
      exp += counter;
    } else {
      *precision = 0;
    }
  }

  counter = s21_strspn(exp, "cdifsuhl");
  for (s21_size_t i = 0; i < counter; i++) {
    specifier[i] = exp[i];
  }

  free(widthStr);
  free(precisionStr);
  return errorFlag;
}

void parseFlag(char *flag, int *signFlag, int *sideFlag) {
  if (s21_strchr(flag, '+')) {
    *signFlag = 2;
  } else if (s21_strchr(flag, ' ')) {
    *signFlag = 1;
  }
  if (s21_strchr(flag, '-')) {
    *sideFlag = 1;
  }
}

char *formatInt(va_list args, char *flag, s21_size_t width, int precision,
                char *specifier) {
  int signFlag = 0, sideFlag = 0;
  parseFlag(flag, &signFlag, &sideFlag);
  s21_size_t destSize =
      width > (s21_size_t)precision ? width + 30 : (s21_size_t)precision + 30;
  char *destination = calloc(destSize, sizeof(char));
  char *formatValue = calloc(destSize, sizeof(char));
  char *p = formatValue;

  char *strValue = s21_NULL;
  if (s21_strchr(specifier, 'u')) {
    if (*specifier == 'l' || *specifier == 'u') {
      unsigned long value = va_arg(args, unsigned long);
      strValue = s21_utoa(value);
    } else if (*specifier == 'h') {
      unsigned short value = (unsigned short)va_arg(args, int);
      strValue = s21_hutoa(value);
    }
  } else if (*specifier == 'l') {
    long value = va_arg(args, long);
    strValue = s21_ltoa(value);
  } else {
    int value = va_arg(args, int);
    strValue = s21_itoa(value);
  }

  s21_size_t sizeValue = s21_strlen(strValue);

  if (signFlag == 2 && !s21_strchr(specifier, 'u')) {
    *p++ = '+';
  } else if (signFlag == 1) {
    *p++ = ' ';
  }
  // Дописываем нули перед числом, если есть точность
  if (precision) {
    precision -= sizeValue;
    for (int i = 0; i < precision; i++) {
      *p++ = '0';
    }
  }

  s21_strcat(formatValue, strValue);
  formatWidth(formatValue, destination, width, sideFlag);
  free(formatValue);
  free(strValue);
  return destination;
}

char *formatFloat(double value, char *flag, s21_size_t width, int precision) {
  int signFlag = 0, sideFlag = 0;
  parseFlag(flag, &signFlag, &sideFlag);
  int negative = value < 0;

  s21_size_t destSize =
      width > (s21_size_t)precision ? width + 30 : (s21_size_t)precision + 30;
  char *destination = calloc(destSize, sizeof(char));
  char *formatValue = calloc(destSize, sizeof(char));

  char *strValue = s21_ftoa(value, precision);

  if (signFlag == 2 && !negative) {
    *formatValue = '+';
  } else if (signFlag == 1 && !negative) {
    *formatValue = ' ';
  }

  s21_strcat(formatValue, strValue);
  formatWidth(formatValue, destination, width, sideFlag);

  free(strValue);
  free(formatValue);
  return destination;
}

char *formatStr(char *value, char *flag, s21_size_t width, int precision) {
  s21_size_t sizeValue = s21_strlen(value);
  s21_size_t destSize = width > sizeValue ? width + 10 : sizeValue + 10;
  int sideFlag = s21_strchr(flag, '-') ? 1 : 0;
  char *destination = calloc(destSize, sizeof(char));
  char *formatValue = calloc(destSize, sizeof(char));
  s21_strcpy(formatValue, value);
  if (precision >= 0 && (s21_size_t)precision < sizeValue) {
    formatValue[precision] = '\0';
  }

  formatWidth(formatValue, destination, width, sideFlag);
  free(formatValue);
  return destination;
}

void formatWidth(const char *str, char *destination, s21_size_t width,
                 int sideFlag) {
  s21_size_t sizeStr = s21_strlen(str);

  if (width > sizeStr) {
    if (!sideFlag) {
      while (width > sizeStr) {
        *destination++ = ' ';
        width--;
      }
    }

    while (*str) {
      *destination++ = *str++;
    }

    if (sideFlag) {
      while (width > sizeStr) {
        *destination++ = ' ';
        width--;
      }
    }
  } else {
    while (*str) {
      *destination++ = *str++;
    }
  }
  *destination = '\0';
}
