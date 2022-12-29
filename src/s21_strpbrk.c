#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    char *sbk = s21_NULL;
    while (*str2) {
        if (sbk == s21_NULL ||
        //  (int)(sbk - str1 + 1) позиция символа
        //  с номером первого символа  строки стр2 с учётом сдвига указателя
        (int) (sbk - str1 + 1) > (int)(s21_strchr(str1, *str2)- str1 + 1)) {
            if (s21_strchr(str1, *str2) != s21_NULL) {
            //  записываю в сбк первый символ строки стр2
                sbk = s21_strchr(str1, *str2);
            }
            //  сдвигаю стр2 на 1 и первым символом стал следующий
            //  да да сдвигаю именно указатель
            str2++;
        } else {
            str2++;
        }
    }
    return (char*)sbk;
}
