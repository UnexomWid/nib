# About <a href="https://cmake.org/cmake/help/v3.0/release/3.0.0.html"><img align="right" src="https://img.shields.io/badge/CMake-3.0-CCCCCD?logo=CMake" alt="CMake 3.0" /></a><a href="https://en.wikipedia.org/wiki/C_(programming_language)"><img align="right" src="https://img.shields.io/badge/C-11-A5B4C6?logo=data:image/svg+xml;base64,PHN2ZyByb2xlPSJpbWciIHZpZXdCb3g9IjAgMCAyNCAyNCIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+QysrIGljb248L3RpdGxlPjxwYXRoIGZpbGw9IiNmZmZmZmYiIGQ9Ik0yMi4zOTMgNmMtLjE2Ny0uMjktLjM5OC0uNTQzLS42NTItLjY5TDEyLjkyNS4yMmMtLjUwOC0uMjkzLTEuMzM5LS4yOTMtMS44NDcgMEwyLjI2IDUuMzFjLS41MDguMjkzLS45MjMgMS4wMTMtLjkyMyAxLjZ2MTAuMThjMCAuMjk0LjEwNC42Mi4yNzEuOTEuMTY3LjI5LjM5OC41NDMuNjUyLjY4OWw4LjgxNiA1LjA5MWMuNTA4LjI5MyAxLjMzOS4yOTMgMS44NDcgMGw4LjgxNi01LjA5MWMuMjU0LS4xNDYuNDg1LS4zOTkuNjUyLS42ODlzLjI3MS0uNjE2LjI3MS0uOTFWNi45MWMuMDAyLS4yOTQtLjEwMi0uNjItLjI2OS0uOTF6TTEyIDE5LjEwOWMtMy45MiAwLTcuMTA5LTMuMTg5LTcuMTA5LTcuMTA5UzguMDggNC44OTEgMTIgNC44OTFhNy4xMzMgNy4xMzMgMCAwIDEgNi4xNTYgMy41NTJsLTMuMDc2IDEuNzgxQTMuNTY3IDMuNTY3IDAgMCAwIDEyIDguNDQ1Yy0xLjk2IDAtMy41NTQgMS41OTUtMy41NTQgMy41NTVTMTAuMDQgMTUuNTU1IDEyIDE1LjU1NWEzLjU3IDMuNTcgMCAwIDAgMy4wOC0xLjc3OGwzLjA3NyAxLjc4QTcuMTM1IDcuMTM1IDAgMCAxIDEyIDE5LjEwOXoiLz48L3N2Zz4=" alt="C 11" /></a>
**NIB** (_from nibble, meaning 4 bits_) is an esoteric programming language that uses instructions encoded as nibbles.

This is a cross-platform [C11](https://en.wikipedia.org/wiki/C11_\(C_standard_revision\)) interpreter for NIB.

# License <a href="https://github.com/UnexomWid/nib/blob/master/LICENSE"><img align="right" src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT" /></a>
**NIB** was created by [UnexomWid](https://github.com/UnexomWid).

The NIB language is licensed under the [MIT](https://github.com/UnexomWid/nib/blob/master/LICENSE) license.

# Releases

>Note: versions with the suffix **R** are considered stable releases, while those with the suffix **D** are considered unstable.

None.

# NIB

The NIB language is similar to [BF](https://en.wikipedia.org/wiki/Brainfuck) (_i.e. they share the same instructions_).

However, while BF stores instructions as characters, NIB stores them as [nibbles](https://en.wikipedia.org/wiki/Nibble).

## Instructions

All nibbles that start with the bit `0` are considered instructions.

The table below contains all NIB instructions.

|    Instruction    | BF Equivalent | Nibble |
|:-----------------:|:-------------:|:------:|
| INCREMENT_POINTER |       >       |  0011  |
| DECREMENT_POINTER |       <       |  0110  |
|  INCREMENT_VALUE  |       +       |  0010  |
|  DECREMENT_VALUE  |       -       |  0101  |
|    WRITE_VALUE    |       .       |  0000  |
|     READ_VALUE    |       ,       |  0111  |
|     LOOP_START    |       [       |  0100  |
|      LOOP_END     |       ]       |  0001  |

Nibbles that start with the bit `1` are ignored, and can used for padding.

> One byte stores exactly 2 instructions.
>
> If you have an odd number of instructions, the last nibble should be a padding nibble.
>
> **Note:** The standard padding nibble is `1000`.