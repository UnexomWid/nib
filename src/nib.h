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

#ifndef NIB_H
#define NIB_H

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// If you use this header in a larger project, you should replace all #define preprocessor directives
// with something like const uint8_t, as it's better practice to do that. However, #define works just
// fine here, as this is not a large project.

#ifndef LEFT_MASK
#define LEFT_MASK 0b11110000u
#endif
#ifndef RIGHT_MASK
#define RIGHT_MASK 0b00001111u
#endif

#define NIB_INCREMENT_POINTER 0b0011u
#define NIB_DECREMENT_POINTER 0b0110u
#define NIB_INCREMENT_VALUE 0b0010u
#define NIB_DECREMENT_VALUE 0b0101u
#define NIB_WRITE_VALUE 0b0000u
#define NIB_READ_VALUE 0b0111u
#define NIB_LOOP_START 0b0100u
#define NIB_LOOP_END 0b0001u

/**
 * Represents a type of pointer.
 */
enum POINTER_TYPE { CHAR, UINT8, UINT32 };

/**
 * Writes an error to STDERR and terminates the program with the status code 1.
 *
 * @param[in] format The format of the error.
 * @param[in] ... The additional arguments for the error format.
 */
void error(const char* format, ...);
/**
 * Closes all given FILE pointers.
 *
 * @param[in] count The amount of given FILE pointers..
 * @param[in, out] ... The FILE pointers.
 */
void closeAll(uint32_t count, ...);
/**
 * Frees all given pointers of the same type.
 *
 * @param[in] type The type of the pointers.
 * @param[in] count The amount of given pointers.
 * @param[int, out] ... The pointers.
 */
void freeAll(enum POINTER_TYPE type, uint32_t count, ...);

/**
 * Sets up the interpreter for a FILE pointer and runs it.
 *
 * @param[in, out] input The pointer to the input FILE pointer.
 * @param[in] memStepSize The amount of extra memory to allocate for the data array and loops stack when they run out of it, in bytes.
 * @param[in] safe Whether or not to use the safe interpreter.
 *
 * @note The input FILE* is passed by using a pointer because it will be modified inside this function (it will be closed).
 */
void run(FILE** input, uint32_t memStepSize, bool safe);
/**
 * Decodes an array of bytes to an interpretable format.
 *
 * @param[in] source The byte array source to decode.
 * @param[in] sourceSize The size of the source, in bytes.
 * @param[out] result The decoded source, as an array of bytes.
 *
 * @return The size of the decoded source, in bytes.
 */
uint32_t decode(const uint8_t* source, uint32_t sourceSize, uint8_t** result);

/**
 * Interprets an array of instructions.
 *
 * @param[in] memStepSize The amount of extra memory to allocate for the data array and loops stack when they run out of it, in bytes.
 * @param[in, out] inputData The input byte array to interpret.
 * @param[in] inputSize The size of the input
 * @param[in, out] inputIndex The index from which to interpret.
 * @param[in, out] data The data byte array.
 * @param[in, out] dataIndex The data index.
 * @param[in, out] dataSize The size of the data.
 * @param[in, out] loopStack The loop stack.
 * @param[in, out] loopStackIndex The index of the loop stack.
 * @param[in, out] loopStackSize The size of the loop stack.
 */
void interpret(uint32_t memStepSize, uint8_t** inputData, int32_t inputSize, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize);
/**
 * Interprets an array of instructions safely.
 *
 * @param[in] memStepSize The amount of extra memory to allocate for the data array and loops stack when they run out of it, in bytes.
 * @param[in, out] inputData The input byte array to interpret.
 * @param[in] inputSize The size of the input
 * @param[in, out] inputIndex The index from which to interpret.
 * @param[in, out] data The data byte array.
 * @param[in, out] dataIndex The data index.
 * @param[in, out] dataSize The size of the data.
 * @param[in, out] loopStack The loop stack.
 * @param[in, out] loopStackIndex The index of the loop stack.
 * @param[in, out] loopStackSize The size of the loop stack.
 */
void interpretSafely(uint32_t memStepSize, uint8_t** inputData, int32_t inputSize, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize);
/**
 * Parses an instruction and interprets it.
 *
 * @param[in] instruction The instruction to parse.
 * @param[in] memStepSize The amount of extra memory to allocate for the data array and loops stack when they run out of it, in bytes.
 * @param[in, out] inputData The input byte array.
 * @param[in, out] inputIndex The index of the input.
 * @param[in, out] data The data byte array.
 * @param[in, out] dataIndex The data index.
 * @param[in, out] dataSize The size of the data.
 * @param[in, out] loopStack The loop stack.
 * @param[in, out] loopStackIndex The index of the loop stack.
 * @param[in, out] loopStackSize The size of the loop stack.
 * @param[out] skipLoop Whether or not to skip the current loop.
 * @param[out] inputIndexChanged Whether or not the input index was changed, and must not be moved again.
 */
void parseInstruction(uint8_t instruction, uint32_t memStepSize, uint8_t** inputData, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize, bool* skipLoop, bool* inputIndexChanged);
/**
 * Parses an instruction and interprets it safely.
 *
 * @param instruction The instruction to parse.
 * @param memStepSize The amount of extra memory to allocate for the data array and loops stack when they run out of it, in bytes.
 * @param inputIndex The index of the input.
 * @param data The data byte array.
 * @param dataIndex The data index.
 * @param dataSize The size of the data.
 * @param loopStack The loop stack.
 * @param loopStackIndex The index of the loop stack.
 * @param loopStackSize The size of the loop stack.
 * @param skipLoop Whether or not to skip the current loop.
 * @param inputIndexChanged Whether or not the input index was changed, and must not be moved again.
 */
void parseInstructionSafely(uint8_t instruction, uint32_t memStepSize, uint32_t* inputIndex, uint8_t** data, uint32_t* dataIndex, uint32_t* dataSize, uint32_t** loopStack, uint32_t* loopStackIndex, uint32_t* loopStackSize, bool* skipLoop, bool* inputIndexChanged);

#endif
