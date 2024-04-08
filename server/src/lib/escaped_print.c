/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** escaped_print
*/

#include <stdio.h>
#include <string.h>
#include "escaped.h"

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

static char *get_special_char(char str)
{
    for (int i = 0; special_chars[i].str; i++) {
        if (special_chars[i].str == str)
            return special_chars[i].escaped;
    }
    return NULL;
}

void print_escaped(const char *str)
{
    char *escaped;

    for (int i = 0; str[i]; i++) {
        escaped = get_special_char(str[i]);
        if (escaped)
            printf("%s", escaped);
        else
            printf("%c", str[i]);
    }
    printf("\n");
}
