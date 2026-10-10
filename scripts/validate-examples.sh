#!/usr/bin/env bash
set -uo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
failed=0
checked=0

for tool in gcc g++; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "Required compiler not found: $tool" >&2
    exit 2
  fi
done

modules=()
for dir in "$root"/m*-*; do
  [[ -d "$dir" ]] || continue
  modules+=("$dir")
done
if (( ${#modules[@]} == 0 )); then
  echo "No course module directories were found." >&2
  exit 2
fi

while IFS= read -r -d '' file; do
  rel="${file#"$root"/}"
  checked=$((checked + 1))
  if ! gcc -std=gnu11 -fsyntax-only "$file" >/tmp/course-check.out 2>&1; then
    printf 'FAIL [C] %s\n' "$rel"
    sed -n '1,8p' /tmp/course-check.out
    failed=$((failed + 1))
  fi
done < <(find "${modules[@]}" -type f -name '*.c' ! -name '*helper*' ! -name 'no-code.c' -print0)

while IFS= read -r -d '' file; do
  rel="${file#"$root"/}"
  checked=$((checked + 1))
  if ! g++ -std=c++17 -fsyntax-only "$file" >/tmp/course-check.out 2>&1; then
    printf 'FAIL [C++] %s\n' "$rel"
    sed -n '1,8p' /tmp/course-check.out
    failed=$((failed + 1))
  fi
done < <(find "${modules[@]}" -type f -name '*.cpp' ! -name '*helper*' ! -name 'no-code.cpp' ! -name 'start.cpp' -print0)

rm -f /tmp/course-check.out
printf 'Syntax check complete: %d files checked, %d failed.\n' "$checked" "$failed"
(( failed == 0 ))
