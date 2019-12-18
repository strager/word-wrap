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

#define CUTOFF 14

static int output_column;

void output(char c) {
    putchar(c);
    fflush(stdout);
    if (c == '\n') {
        output_column = 0;
    } else {
        output_column += 1;
    }
}

int main(void) {
    output_column = 0;

first_word_in_line:;
    for (;;) {
        int c = getchar();
        if (c == EOF) {
            goto eof;
        }

        if (c == ' ') {
            break;
        } else {
            output(c);
        }
    }
    if (output_column >= CUTOFF) {
        output('\n');
        goto first_word_in_line;
    }

    char next_word[CUTOFF];
    int next_word_length = 0;
    for (;;) {
        if (output_column + next_word_length >= CUTOFF) {
            assert(output_column + next_word_length == CUTOFF);
            output('\n');
            for (int j = 0; j < next_word_length; ++j) {
                output(next_word[j]);
            }
            goto first_word_in_line;
        }

        int c = getchar();
        if (c == EOF || c == ' ') {
            output(' ');
            for (int j = 0; j < next_word_length; ++j) {
                output(next_word[j]);
            }
            assert(output_column <= CUTOFF);
            next_word_length = 0;
            if (c == EOF) {
                goto eof;
            }
        } else if (c == '\n') {
            output(' ');
            for (int j = 0; j < next_word_length; ++j) {
                output(next_word[j]);
            }
            output('\n');
            goto first_word_in_line;
        } else {
            next_word[next_word_length] = c;
            next_word_length += 1;
        }
    }

eof:
    return 0;
}
