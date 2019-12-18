#include <assert.h>
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
    for (;;) {
beginning_of_line:;
        int output_column = 0;
first_word_in_line:;
        for (;;) {
            int c = getchar();
            if (c == EOF) {
                goto eof;
            }

            if (c == '\n') {
                putchar('\n');
                output_column = 0;
            } else if (c == ' ') {
                break;
            } else {
                putchar(c);
                output_column += 1;
            }
        }
        if (output_column >= CUTOFF) {
            putchar('\n');
            goto beginning_of_line;
        }

        char buffer[CUTOFF];
        int i = 0;
        for (;;) {
            if (output_column + i >= CUTOFF) {
                assert(output_column + i == CUTOFF);
                putchar('\n');
                for (int j = 0; j < i; ++j) {
                    putchar(buffer[j]);
                }
                output_column = i;
                goto first_word_in_line;
            }

            int c = getchar();
            if (c == EOF || c == ' ') {
                putchar(' ');
                output_column += 1;
                for (int j = 0; j < i; ++j) {
                    putchar(buffer[j]);
                    output_column += 1;
                }
                assert(output_column < CUTOFF);
                i = 0;
                if (c == EOF) {
                    goto eof;
                }
            } else if (c == '\n') {
                putchar('\n');
                goto beginning_of_line;
            } else {
                buffer[i] = c;
                i += 1;
            }
        }
    }
eof:

    return 0;
}
