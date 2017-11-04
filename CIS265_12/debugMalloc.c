#include "debugMalloc.h"

#ifndef NDEBUG

void *debugMalloc(size_t nSize, char *file, int line) {
	void *pMem = malloc(sizeof(size_t) + nSize);
	if (pMem) {
		size_t *pSize = (size_t *)pMem;
		memcpy(pSize, &nSize, sizeof(nSize));
		currentMemory += nSize;
		if (currentMemory > peakMemory)
			peakMemory = currentMemory;
		fprintf(stdout, "malloc: %s, line #%d\n", file, line);
		fprintf(stdout, "  %#x Size: %d, total: %d, peak: %d\n", (unsigned int)pSize, nSize, currentMemory, peakMemory);
		return(pSize + 1);
	}
	return NULL;
}

void debugFree(void *pMem, char *file, int line) {
	if (pMem) {
		size_t *pSize = (size_t *)pMem;
		--pSize;
		assert(currentMemory >= *pSize);
		currentMemory -= *pSize;
		fprintf(stdout, "free: %s, line #%d\n", file, line);
		fprintf(stdout, "  %#x Size: %d, total: %d, peak: %d\n", (unsigned int)pSize, *pSize, currentMemory, peakMemory);
		free(pSize);
	}
}

// Macros define after our replacement functions.
#define malloc(size) debugMalloc(size, __FILE__, __LINE__)
#define free(p) debugFree(p, __FILE__, __LINE__)

#endif
