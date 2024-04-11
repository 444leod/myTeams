/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** escaped_print
*/

#include <stdio.h>
#include <string.h>
#include "escaped.h"
#include "macros.h"
#include "lib.h"
#include "garbage_collector.h"

struct special_char_s special_chars[] = {
    {'\n', "\\n"},
    {'\t', "\\t"},
    {'\v', "\\v"},
    {'\b', "\\b"},
    {'\r', "\\r"},
    {'\f', "\\f"},
    {'\a', "\\a"},
    {'\\', "\\\\"},
    {'\?', "\\?"},
    {'\'', "\\'"},
    {'\"', "\\\""},
    {0, NULL}
};

UNUSED static char *get_special_char(char str)
{
    for (int i = 0; special_chars[i].str; i++) {
        if (special_chars[i].str == str)
            return special_chars[i].escaped;
    }
    return NULL;
}

void print_escaped(const char *str)
{
    char *escaped = get_escaped_string(str);

    printf("%s\n", escaped);
}

char *get_escaped_string(const char *str)
{
    char *escaped = my_malloc(sizeof(char) * (strlen(str) * 2 + 1));
    char *tmp;
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (get_special_char(str[i])) {
            strcat(escaped, get_special_char(str[i]));
            j += strlen(get_special_char(str[i]));
        } else {
            escaped[j] = str[i];
            j++;
        }
    }
    escaped[j] = '\0';
    tmp = my_strdup(escaped);
    my_free(escaped);
    return tmp;
}
