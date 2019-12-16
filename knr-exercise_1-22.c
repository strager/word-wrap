#include <stdio.h>

/* Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the
 * n-th column of input. Make sure your program does something intelligent
 * with very long lines, and if there are no blanks or tabs before the
 * specified column.
 */

#define MAXLINE 50
#define CUTOFF 15

int mygetline(char line[], int len);
void fold(char line[], int cutoff);

int main(void) {
    int i;
    char line[MAXLINE];

    for (i = 0; i < MAXLINE; i++) {
        line[i] = 0;
    }

    while (mygetline(line, MAXLINE) > 0) {
        fold(line, CUTOFF);
        printf("%s", line);
    }

    return 0;
}

void fold(char line[], int cutoff) {
    int i, len, lastspace, chars_folded;

    lastspace = -1;
    chars_folded = 0;

    for (len = 0; line[len] != '\0'; len++)
        ;

    for (i = 0; i < len; i++) {
        if (line[i] == ' ') {
            lastspace = i;
        }

        if (i - chars_folded >= cutoff && lastspace >= 0) {
            line[lastspace] = '\n';
            chars_folded += (lastspace - chars_folded) + 1;
            i = lastspace;
            lastspace = -1;
        }
    }
}

int mygetline(char line[], int maxlen) {
    int i, c;

    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF; i++) {
        line[i] = c;

        if (c == '\n') {
            i++;
            break;
        }
    }

    line[i] = '\0';

    return i;
}
