#include <stdio.h>

int main(void)
{
    char arr_str[] = "لَا إِلَٰهَ إِلَّا ٱللَّٰهُ";
    for (size_t i = 0; i < sizeof(arr_str) / sizeof(arr_str[0]); i++)
        putchar(arr_str[i]);
    putchar('\n');

    char *ptr_str = "مُحَمَّدٌ رَسُولُ ٱللَّٰهِ";
    while (*ptr_str)
        putchar(*ptr_str++);
    putchar('\n');

    return 1;
}
