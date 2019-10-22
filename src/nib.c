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

void error(const char* format, ...) {
    va_list va;
    va_start(va, format);

    vfprintf(stderr, format, va);

    va_end(va);
    exit(1);
}

void freeAll(enum POINTER_TYPE type, const uint32_t count, ...) {
    va_list va;
    va_start(va, count);

    // The switch is outside the loop in order to avoid repeated checks inside.
    switch(type) {
        case CHAR: {
            for(uint32_t i = 0; i < count; ++i) {
                char** pointer = va_arg(va, char**);
                free(*pointer);
                *pointer = NULL;
            }
            break;
        }
        case UINT8: {
            for(uint32_t i = 0; i < count; ++i) {
                uint8_t** pointer = va_arg(va, uint8_t**);
                free(*pointer);
                *pointer = NULL;
            }
            break;
        }
        case UINT32: {
            for(uint32_t i = 0; i < count; ++i) {
                uint32_t** pointer = va_arg(va, uint32_t**);
                free(*pointer);
                *pointer = NULL;
            }
            break;
        }
        default: {
            break;
        }
    }

    va_end(va);
}

void closeAll(const uint32_t count, ...) {
    va_list va;
    va_start(va, count);

    for(uint32_t i = 0; i < count; ++i)
        fclose(va_arg(va, FILE*));

    va_end(va);
}

void run(FILE** input, const uint32_t memStepSize, const bool safe) {
    // Data info.
    uint8_t* data = (uint8_t*) calloc(memStepSize, 1);
    uint32_t dataIndex = 0;
    uint32_t dataLimit = memStepSize;

    // Loop stack info.
    uint32_t* loopStack = calloc(memStepSize, 4);
    uint32_t loopStackIndex = -1;
    uint32_t loopStackLimit = memStepSize;

    // Get the input size.
    fseek(*input, 0, SEEK_END);
    int32_t fileSize = ftell(*input);
    if(fileSize == -1) {
        freeAll(UINT8, 1, data);
        freeAll(UINT32, 1, loopStack);
        error("Could not determine input file size (file could be too large)");
    }
    fseek(*input, 0, SEEK_SET);

    // Read the input.
    uint8_t* fileData = (uint8_t*) malloc(fileSize);
    fread(fileData, 1, fileSize, *input);
    if(ferror(*input)) {
        freeAll(UINT8, 2, data, fileData);
        freeAll(UINT32, 1, loopStack);
        closeAll(1, *input);
        error("Could not read input file");
    }
    fclose(*input);

    // Decode the input.
    uint8_t* inputData = NULL;
    uint32_t inputSize = decode(fileData, fileSize, &inputData);
    uint32_t inputIndex = 0;
    free(fileData);

    // Interpret, either normally or safely.
    // Both interpreters could be merged into one, as they only differ in one line of code.
    // However, it would be slower because the value of "safe" would need to be checked for every instruction.
    // Also, merging them would make it harder for the safe interpreter to be changed in the future.
    // There is also the option of merging them and checking the value of "safe" at the beginning, basically splitting the function body.
    if(safe)
        interpretSafely(memStepSize, &inputData, inputSize, &inputIndex, &data, &dataIndex, &dataLimit, &loopStack, &loopStackIndex, &loopStackLimit);
    else interpret(memStepSize, &inputData, inputSize, &inputIndex, &data, &dataIndex, &dataLimit, &loopStack, &loopStackIndex, &loopStackLimit);

    // Free the used memory.
    freeAll(UINT8, 2, &data, &inputData);
    freeAll(UINT32, 1, &loopStack);
}

uint32_t decode(const uint8_t* source, const uint32_t sourceSize, uint8_t** result) {
    // Result info.
    uint32_t resultSize = sourceSize * 2;
    uint32_t resultOffset = 0;
    *result = (uint8_t*) malloc(resultSize);

    // Decode the source.
    for(uint32_t i = 0; i < sourceSize; ++i) {
        uint8_t current = *(source + i);

        *(*result + (resultOffset++)) = (current & LEFT_MASK) >> 4u;
        *(*result + (resultOffset++)) = current & RIGHT_MASK;
    }
    return resultSize;
}

void interpret(const uint32_t memStepSize, uint8_t** inputData, const int32_t inputSize, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize) {
    while(*inputIndex < inputSize) {
        uint8_t instruction;
        bool skipLoop = false;
        bool inputIndexChanged = false;

        // Parse the instruction.
        instruction = *(*inputData + *inputIndex);
        parseInstruction(instruction, memStepSize, inputData, inputIndex, data, dataIndex, dataSize, loopStack, loopStackIndex, loopStackSize, &skipLoop, &inputIndexChanged);

        // Skip the loop.
        if(skipLoop) {
            uint32_t loopCount = 1;

            while (loopCount > 0 && *inputIndex < inputSize) {
                instruction = *(*inputData + ++(*inputIndex));

                if (instruction == NIB_LOOP_START)
                    ++loopCount;
                else if (instruction == NIB_LOOP_END)
                    --loopCount;
            }

            if (*inputIndex == inputSize)
                error("Expected end of loop");
        }

        // Keep any changes made to the input index.
        if(!inputIndexChanged)
            ++(*inputIndex);
    }
}

void interpretSafely(const uint32_t memStepSize, uint8_t** inputData, const int32_t inputSize, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize) {
    while(*inputIndex < inputSize) {
        uint8_t instruction;
        bool skipLoop = false;
        bool inputIndexChanged = false;

        // Parse the instruction safely.
        instruction = *(*inputData + *inputIndex);
        parseInstructionSafely(instruction, memStepSize, inputIndex, data, dataIndex, dataSize, loopStack, loopStackIndex, loopStackSize, &skipLoop, &inputIndexChanged);

        // Skip the loop.
        if(skipLoop) {
            uint32_t loopCount = 1;

            while (loopCount > 0 && *inputIndex < inputSize) {
                instruction = *(*inputData + ++(*inputIndex));

                if (instruction == NIB_LOOP_START)
                    ++loopCount;
                else if (instruction == NIB_LOOP_END)
                    --loopCount;
            }

            if (*inputIndex == inputSize)
                error("Expected end of loop");
        }

        // Keep any changes made to the input index.
        if(!inputIndexChanged)
            ++(*inputIndex);
    }
}

void parseInstruction(const uint8_t instruction, const uint32_t memStepSize, uint8_t** inputData, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize, bool* skipLoop, bool* inputIndexChanged) {
    switch(instruction) {
        case NIB_INCREMENT_POINTER: {
            ++(*dataIndex);
            if(*dataIndex == *dataSize) {
                *data = ((uint8_t *) realloc(*data, (*dataSize += memStepSize)));
                memset(*data + *dataSize - memStepSize, 0, memStepSize);
            }
            break;
        }
        case NIB_DECREMENT_POINTER: {
            --(*dataIndex);
            break;
        }
        case NIB_INCREMENT_VALUE: {
            if(*dataIndex >= *dataSize) {
                freeAll(UINT8, 2, data, inputData);
                freeAll(UINT32, 1, loopStack);
                error("Data index out of bounds at input index '%u'", *inputIndex);
            }
            ++(*(*data + *dataIndex));
            break;
        }
        case NIB_DECREMENT_VALUE: {
            if(*dataIndex >= *dataSize) {
                freeAll(UINT8, 2, data, inputData);
                freeAll(UINT32, 1, loopStack);
                error("Data index out of bounds at input index '%u'", *inputIndex);
            }
            --(*(*data + *dataIndex));
            break;
        }
        case NIB_WRITE_VALUE: {
            if(*dataIndex >= *dataSize) {
                freeAll(UINT8, 2, data, inputData);
                freeAll(UINT32, 1, loopStack);
                error("Data index out of bounds at input index '%u'", *inputIndex);
            }
            putchar(*(*data + *dataIndex));
            break;
        }
        case NIB_READ_VALUE: {
            if(*dataIndex >= *dataSize) {
                freeAll(UINT8, 2, data, inputData);
                freeAll(UINT32, 1, loopStack);
                error("Data index out of bounds at input index '%u'", *inputIndex);
            }
            *(*data + *dataIndex) = getchar();
            break;
        }
        case NIB_LOOP_START: {
            if(*(*data + *dataIndex) == 0) {
                *skipLoop = true;
            } else {
                ++(*loopStackIndex);
                if(*loopStackIndex == *loopStackSize) {
                    *loopStack = ((uint32_t *) realloc(*loopStack, (*loopStackSize += memStepSize) * 4)) + *loopStackIndex;
                    memset(*loopStack + *loopStackSize - memStepSize, 0, memStepSize);
                }
                *(*loopStack + *loopStackIndex) = *inputIndex;
            }
            break;
        }
        case NIB_LOOP_END: {
            if(*loopStackIndex >= *loopStackSize) {
                freeAll(UINT8, 2, data, inputData);
                freeAll(UINT32, 1, loopStack);
                error("Unexpected end of loop at input index '%u'", *inputIndex);
            }
            *inputIndex = *((*loopStack + (*loopStackIndex)--));
            *inputIndexChanged = true;
            break;
        }
        default: {
            break;
        }
    }
}

void parseInstructionSafely(const uint8_t instruction, const uint32_t memStepSize, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize, bool* skipLoop, bool* inputIndexChanged) {
    switch(instruction) {
        case NIB_INCREMENT_POINTER: {
            ++(*dataIndex);
            if(*dataIndex == *dataSize) {
                *data = ((uint8_t *) realloc(*data, (*dataSize += memStepSize)));
                memset(*data + *dataSize - memStepSize, 0, memStepSize);
            }
            break;
        }
        case NIB_DECREMENT_POINTER: {
            if(*dataIndex < *dataSize)
                --(*dataIndex);
            break;
        }
        case NIB_INCREMENT_VALUE: {
            // No check needed, as the data index will never be out of bounds.
            ++(*(*data + *dataIndex));
            break;
        }
        case NIB_DECREMENT_VALUE: {
            // No check needed, as the data index will never be out of bounds.
            --(*(*data + *dataIndex));
            break;
        }
        case NIB_WRITE_VALUE: {
            // No check needed, as the data index will never be out of bounds.
            putchar(*(*data + *dataIndex));
            break;
        }
        case NIB_READ_VALUE: {
            // No check needed, as the data index will never be out of bounds.
            *(*data + *dataIndex) = getchar();
            break;
        }
        case NIB_LOOP_START: {
            if(*(*data + *dataIndex) == 0) {
                *skipLoop = true;
            } else {
                ++(*loopStackIndex);
                if(*loopStackIndex == *loopStackSize) {
                    *loopStack = ((uint32_t *) realloc(*loopStack, (*loopStackSize += memStepSize) * 4)) + *loopStackIndex;
                    memset(*loopStack + *loopStackSize - memStepSize, 0, memStepSize);
                }
                *(*loopStack + *loopStackIndex) = *inputIndex;
            }
            break;
        }
        case NIB_LOOP_END: {
            if(*loopStackIndex < *loopStackSize) {
                *inputIndex = *((*loopStack + (*loopStackIndex)--));
                *inputIndexChanged = true;
            }
            break;
        }
        default: {
            break;
        }
    }
}