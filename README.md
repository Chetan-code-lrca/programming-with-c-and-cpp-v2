# Programming with C and C++ — Course Examples

This repository contains source examples and selected solutions organized by course module:

- `m1-getting-started-with-programming-in-c/`
- `m2-diving-into-c-programming/`
- `m3-oops-fundamentals-using-cpp/`
- `m4-diving-into-cpp-programming/`
- `m5-building-cricket-game-application/`

The files are intended for learning, not as a single application. Some examples are standalone programs, some are partial teaching snippets, and some helper files are meant to be included from another source file.

## Requirements

- GCC for C examples
- G++ with C++17 support for C++ examples

On Ubuntu or WSL:

    sudo apt update
    sudo apt install -y build-essential

## Compile one example

For C:

    gcc -std=gnu11 -Wall -Wextra -fsyntax-only path/to/example.c

For C++:

    g++ -std=c++17 -Wall -Wextra -fsyntax-only path/to/example.cpp

Using `-fsyntax-only` checks syntax and declarations without linking or running the program. Runtime behavior and output should still be tested individually.

## Automated checks

GitHub Actions runs syntax checks on ordinary `.c` and `.cpp` examples and validates patch whitespace. Helper files that are intentionally incomplete or platform-specific may need individual handling rather than being silently excluded.

## Contribution notes

- Keep code in the module/topic folder where it belongs.
- Preserve teaching starter/end examples when they explain a learning step.
- Fix syntax/type errors, but do not change lesson behavior without explaining why.
- Do not commit compiled binaries or IDE/build output.
