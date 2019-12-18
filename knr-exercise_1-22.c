#include <assert.h>
#include <stdbool.h>
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
static bool is_first_word_in_line;

void output(char c) {
    putchar(c);
    fflush(stdout);
    if (c == '\n') {
        output_column = 0;
        is_first_word_in_line = true;
    } else {
        output_column += 1;
    }
}

void output_many(const char *cs, int count) {
    for (int i = 0; i < count; ++i) {
        output(cs[i]);
    }
}

int main(void) {
    output_column = 0;
    is_first_word_in_line = true;

    char next_word[CUTOFF];
    int next_word_length = 0;
    for (;;) {
        int c = getchar();
        if (is_first_word_in_line) {
            if (c == EOF) {
                break;
            } else if (c == ' ') {
                assert(next_word_length == 0);
                if (output_column >= CUTOFF) {
                    output('\n');
                    continue;
                }
                is_first_word_in_line = false;
            } else {
                output(c);
                assert(is_first_word_in_line);
            }
        } else {
            if (c == EOF || c == ' ' || c == '\n') {
                output(' ');
                output_many(next_word, next_word_length);
                next_word_length = 0;
                assert(output_column <= CUTOFF);
                if (c == EOF) {
                    break;
                } else if (c == ' ') {
                    assert(!is_first_word_in_line);
                } else if (c == '\n') {
                    output('\n');
                } else {
                    assert(false);
                }
            } else {
                next_word[next_word_length] = c;
                next_word_length += 1;
                assert(!is_first_word_in_line);
            }

            if (output_column + next_word_length >= CUTOFF) {
                // The next word is too large to fit on the
                // current line.
                assert(output_column + next_word_length == CUTOFF);
                output('\n');
                output_many(next_word, next_word_length);
                next_word_length = 0;
                continue;
            }

        }
    }

    return 0;
}
