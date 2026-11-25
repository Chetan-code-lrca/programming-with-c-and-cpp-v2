#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tmp_dir="$(mktemp -d)"
trap 'rm -rf "$tmp_dir"' EXIT

source_file="$root/m1-getting-started-with-programming-in-c/t11-miscellaneous-concepts/clear-input-buffer.c"
binary="$tmp_dir/clear-input-buffer"

gcc -std=c11 -Wall -Wextra -Werror "$source_file" -o "$binary"

printf 'Asha Rao\n42\nF\n19\n' | "$binary" >"$tmp_dir/valid.out"
grep -Fq 'Asha Rao' "$tmp_dir/valid.out"
grep -Fq '42' "$tmp_dir/valid.out"
grep -Fq 'F' "$tmp_dir/valid.out"
grep -Fq '19' "$tmp_dir/valid.out"

if printf 'Asha Rao\nnot-an-id\n' | "$binary" >"$tmp_dir/invalid.out" 2>"$tmp_dir/invalid.err"; then
    echo 'Expected non-numeric ID input to fail.' >&2
    exit 1
fi
grep -Fq 'Invalid id.' "$tmp_dir/invalid.err"

if printf 'Asha Rao\n999999999999999999999999999999\n' | "$binary" >"$tmp_dir/range.out" 2>"$tmp_dir/range.err"; then
    echo 'Expected an out-of-range ID to fail.' >&2
    exit 1
fi
grep -Fq 'Invalid id.' "$tmp_dir/range.err"

if printf 'Asha Rao\n42\nF\n-1\n' | "$binary" >"$tmp_dir/age.out" 2>"$tmp_dir/age.err"; then
    echo 'Expected a negative age to fail.' >&2
    exit 1
fi
grep -Fq 'Invalid age.' "$tmp_dir/age.err"

long_name="$(printf '%040d' 0 | tr '0' 'A')"
if printf '%s\n42\nF\n19\n' "$long_name" | "$binary" >"$tmp_dir/long.out" 2>"$tmp_dir/long.err"; then
    echo 'Expected an overlong name to fail.' >&2
    exit 1
fi
grep -Fq 'Name must contain' "$tmp_dir/long.err"

if printf '%050d' 0 | tr '0' 'A' | timeout 2s "$binary" >"$tmp_dir/eof.out" 2>"$tmp_dir/eof.err"; then
    echo 'Expected an unterminated overlong name to fail.' >&2
    exit 1
fi
grep -Fq 'Name must contain' "$tmp_dir/eof.err"

echo 'Input-buffer regression tests passed (valid input, invalid/range ID, negative age, overlong name, EOF).'
