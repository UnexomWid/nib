/**
 * NIB (https://github.com/UnexomWid/nib)
 *
 * This project is licensed under the MIT license.
 * Copyright (c) 2019 UnexomWid (https://uw.exom.dev)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "nib.h"

#define MEM_STEP_SIZE 32768u
#define SAFE false

/**
 * The main function.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 *
 * @return The program exit code.
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        error("Invalid arguments");
    }

    // Ignore the executable name and jump straight to the file name.
    FILE* inputFile = fopen(*(++argv), "r");
    if(inputFile == NULL)
        error("Invalid input file, or insufficient permissions");

    // The amount of extra memory to allocate for the data array and loops stack when they run out of it, in bytes.
    uint32_t memStepSize = MEM_STEP_SIZE;
    // Whether or not to interpret safely and to ignore some invalid instructions (e.g. moving to a negative index).
    bool safe = SAFE;

    // Jump to additional arguments.
    ++argv;
    argc -= 2;

    for(; argc > 0; --argc, ++argv) {
        // Convert to lowercase.
        uint32_t length = 0;
        for(; **argv; ++*argv, ++length) **argv = (char) tolower(**argv);
        *argv -= length;

        // Check the argument.
        if(strcmp("-m", *argv) == 0 || strcmp("--memory-size", *argv) == 0) {
            if (argc == 1)
                error("Expected memory step size");
            memStepSize = (uint32_t) strtol(*(++argv), (char**) NULL, 10);
            --argc;

            if (memStepSize == 0 || errno == ERANGE)
                error("Invalid memory step size");
        } else if(strcmp("-s", *argv) == 0 || strcmp("--safe", *argv) == 0) {
            safe = true;
        } else error("Invalid argument '%s'", *argv);
    }

    // Sets up the interpreter and runs it.
    run(&inputFile, memStepSize, safe);
}