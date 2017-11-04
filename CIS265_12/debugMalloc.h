#ifndef _DEBUG_MALLOC_H_
#define _DEBUG_MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#ifndef NDEBUG
static size_t currentMemory = 0;
static size_t peakMemory = 0;

void *debugMalloc(size_t nSize, char *, int);
void debugFree(void *pMem, char *, int);

#include "debugMalloc.c"
#endif

#endif
