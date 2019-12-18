#!/usr/bin/env bash
set -e
set -u
gcc -fsanitize=address -Wall -Wextra knr-exercise_1-22.c -o knr-exercise_1-22

check() {
    local input="${1}"
    local expected="${2}"
    printf '%s' "${input}" >input.tmp
    printf '%s' "${expected}" >expected.tmp
    check_file input.tmp expected.tmp
}

check_file() {
    local input_file="${1}"
    local expected_file="${2}"
    local output_file=output.tmp
    ./knr-exercise_1-22 <"${input_file}" >"${output_file}" || {
        printf 'CRASH for input: %q\n' "$(cat "${input_file}")" >&2
        exit 1
    }
    if diff -u "${expected_file}" "${output_file}"; then
        printf 'PASS\n' >&2
    else
        printf 'FAIL for input: %q\n' "$(cat "${input_file}")" >&2
        exit 1
    fi
}

check '' ''
check 'hello world' 'hello world'
check 'this is a long line which contains many words' $'this is a long\nline which\ncontains many\nwords'
check 'thisisalongwordwhichshouldnotbebroken' 'thisisalongwordwhichshouldnotbebroken'
check 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
check 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
check 012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789 012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
check '0123456789abcefghijk 0123456789abcefghijk 0123456789abcefghijk' $'0123456789abcefghijk\n0123456789abcefghijk\n0123456789abcefghijk'
check '0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789' $'0123456789\n0123456789\n0123456789\n0123456789\n0123456789\n0123456789\n0123456789\n0123456789'
check 'in a line break and this' $'in a line break\nand this'

check_file gistfile1.txt gistfile1.txt.expected
