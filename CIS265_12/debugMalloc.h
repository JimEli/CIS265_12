#ifndef _DEBUG_MALLOC_H_
#define _DEBUG_MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#ifdef _DEBUG
static unsigned char _deadLandFill = 0xDD;  /* fill free objects with this */
static unsigned char _cleanLandFill = 0xCC; /* fill new objects with this */

static size_t currentMemory = 0;
static size_t peakMemory = 0;

void *debugMalloc(size_t nSize, char *, int);
void debugFree(void *pMem, char *, int);

#include "debugMalloc.c"

#endif
#endif
