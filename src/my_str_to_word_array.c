/*
** EPITECH PROJECT, 2019
** o
** File description:
** o
*/

#include "../include/ftp.h"

int is_alnum(char const character)
{
    if (character >= '0' && character <= '9')
        return (1);
    if (character >= 'a' && character <= 'z')
        return (1);
    if (character >= 'A' && character <= 'Z')
        return (1);
    if (character == '/')
        return (1);
    return (0);
}

int counts_words(char const *str)
{
    int counter = 0;
    int len = 0;

    len = strlen(str);
    for (int i = 0; i < len; i++) {
        while (is_alnum(str[i]) == 1)
            i++;
        if (i != 0 && is_alnum(str[i - 1]) == 1)
            counter++;
    }
    return (counter);
}

int counts_character(char const *str, int toto)
{
    int counter = 0;

    for (int i = toto; is_alnum(str[i]) == 1; i++)
        counter++;
    return (counter);
}

char **my_str_to_word_array(char const *str)
{
    int l = 0;
    int count_words = counts_words(str);
    int string_length = 0;
    char **array = malloc(sizeof(char *) * (count_words + 1));

    for (int i = 0; str[i] != '\0' && l < count_words; i++) {
        if (str[i] != '\0' && is_alnum(str[i]) == 1) {
            string_length = counts_character(str, i);
            array[l] = malloc(sizeof(char) * (string_length + 1));
            for (int c = 0; c < string_length; c++) {
                array[l][c] = str[i];
                i++;
            }
            l++;
        }
    }
    array[l] = NULL;
    return (array);
}
