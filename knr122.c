#include <stdio.h>

/* Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the
 * n-th column of input. Make sure your program does something intelligent
 * with very long lines, and if there are no blanks or tabs before the
 * specified column.
 *
 * 0. Should handle input lines and words of arbitrary length.
 * 1. Breaking can only be done at whitespace.
 * 2. Output must contain as few lines as possible.
 */

#define CUTOFF 15

void printchars(char buf[], int len);

int main(void) {
    int i, j, c, lastspace;
    char buf[CUTOFF];

    j = c = 0;

    while (c != EOF) {
        lastspace = -1;

        /* After this loop, buf contains i new characters and lastspace 
         * contains the index of the last space in the buf, or if none, -1. 
         */
        for (i = 0; i < CUTOFF && (c = getchar()) != EOF; i++) {
            buf[i] = c;

            if (c == ' ') {
                lastspace = i;
            } else if (c == '\n') {
                i++;
                break;
            }
        }

        /* Buffers containing a newline can just be printed?
         */
        if (i == CUTOFF && lastspace > -1 && buf[i - 1] != '\n') {
            buf[lastspace] = '\n';
        }

        for (j = 0; j < i; j++) {
            putchar(buf[j]);
        }
    }

    return 0;
}