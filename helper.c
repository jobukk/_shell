#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"


int countWords(char *str, char *d) {
    int count = 0;
    int inWord = 0;

    while (*str) {
        if (strchr(d, *str)) {
            if (inWord) {
                inWord = 0;
            }
        } else {
            if (!inWord) {
                inWord = 1;
                count++;
            }
        }
        str++;
    }

    return count;
}

int skipDelimiters(char *str, char *d, int i) {
    while (str[i] && strchr(d, str[i]))
        i++;
    return i;
}

int getWordLength(char *str, char *d, int i) {
    int length = 0;
    while (str[i + length] && !strchr(d, str[i + length]))
        length++;
    return length;
}

char *extractWord(char *str, int i, int k) {
    char *word = malloc(k + 1);
    if (!word)
        return NULL;

    strncpy(word, str + i, k);
    word[k] = '\0';

    return word;
}

void freeMemory(char **s, int j) {
    int index = 0;
    for (index = 0; index < j; index++) {
        free(s[index]);
    }
    free(s);
}
