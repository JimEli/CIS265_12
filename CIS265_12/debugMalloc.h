// Simple debug print malloc/free functions.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#ifndef _DEBUG_MALLOC_H_
#define _DEBUG_MALLOC_H_

#ifdef _DEBUG

// Memory paint values.
static unsigned char _deadLandFill = 0xDD;  // Fill free objects with this value.
static unsigned char _cleanLandFill = 0xCC; // Fill new objects with this value.

// Memory statistics.
static size_t currentMemory = 0;
static size_t peakMemory = 0;

// Redirection function definitions.
void *_debugMalloc(size_t nSize, char *, int);
void _debugFree(void *pMem, char *, int);
void _debugExit(int const status);

#endif
#endif


