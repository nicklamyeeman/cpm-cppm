#include <stdio.h>
#include "explode.h"

int nb_line(char const *str, char separator)
{
    int line = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == separator)
            line += 1;
    }
    if (i > 0)
        line += 1;
    return (line);
}

char **malloc_array(char const *str, char separator)
{
    char **array = malloc(sizeof(char *) * (nb_line(str, separator) + 1));
    int line = 0;
    int word_len = 1;
    int i = 0;

    if (!array)
        return (NULL);
    for (; str[i] != '\0'; i++, word_len++) {
        if (str[i] == separator) {
            array[line++] = malloc(sizeof(char) * (word_len + 1));
            word_len = 0;
        }
    }
    if (i > 0)
        array[line++] = malloc(sizeof(char) * (word_len + 1));
    array[line] = NULL;
    return (array);
}

char *clean_string(char const *str, char separator)
{
    char *clean_str = malloc(sizeof(char) * 1);
    int k = 0;
    int c = 0;

    for (; str[k] != '\0' && str[k] == separator; k++);
    for (c = 0; str[k] != '\0';) {
        for (; str[k + 1] != '\0' && str[k] == separator && str[k + 1] == separator; k++);
        clean_str[c++] = str[k++];
        clean_str = realloc(clean_str, sizeof(char) * (c + 1));
    }
    if (k > 0 && str[k - 1] == separator)
        clean_str[--c] = '\0';
    else {
        clean_str = realloc(clean_str, sizeof(char) * (c + 1));
        clean_str[c] = '\0';
    }
    return clean_str;
}

char **explode(char const *str, char separator)
{
    char *clean_str = clean_string(str, separator);
    char **array = malloc_array(clean_str, separator);
    int i, col, line = 0;

    if (!array)
        return (NULL);
    for (i = 0, col = 0; clean_str[i] != '\0'; i++, col++) {
        if (clean_str[i] == separator) {
            array[line][col] = '\0';
            line += 1;
            col = -1;
        } else
            array[line][col] = clean_str[i];
    }
    if (i > 0 && clean_str[i - 1] != separator)
        array[line][col] = '\0';
    (clean_str) ? free(clean_str) : 0;
    return (array);
}