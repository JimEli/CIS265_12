// Simple debug print malloc/free functions.
#include "debugMalloc.h"

#ifdef _DEBUG

void *_debugMalloc(size_t nSize, char *file, int line) {
	// Attempt to allocate requested size + 1.
	void *pMem = malloc(sizeof(size_t) + nSize);
	if (pMem) {
		size_t *pSize = (size_t *)pMem;
		// Save allocation size.
		memcpy(pSize, &nSize, sizeof(nSize));
		// Paint memory as uninitailized.
		memset(pSize + 1, _cleanLandFill, nSize);
		// Keep count of total allocation.
		currentMemory += nSize;
		if (currentMemory > peakMemory)
			peakMemory = currentMemory;
		// Print statistics.
		fprintf(stdout, "malloc: %s, line #%d\n", file, line);
		fprintf(stdout, "  %#x Size: %d, total: %d, peak: %d\n", (unsigned int)pSize, nSize, currentMemory, peakMemory);
		// Retun memory requested.
		return(pSize + 1);
	}
	return NULL;
}

void _debugFree(void *pMem, char *file, int line) {
	if (pMem) {
		// Get original location of this block.
		size_t *pSize = (size_t *)pMem;
		--pSize;
		assert(currentMemory >= *pSize);
		// Paint memory as dead.
		memset(pSize + 1, _deadLandFill, *pSize);
		// Decrement count of memory.
		currentMemory -= *pSize;
		// Report statistics.
		fprintf(stdout, "free: %s, line #%d\n", file, line);
		fprintf(stdout, "  %#x Size: %d, total: %d, peak: %d\n", (unsigned int)pSize, *pSize, currentMemory, peakMemory);
		free(pSize);
	}
}

// Macros defined after our replacement functions.
#define malloc(size) _debugMalloc(size, __FILE__, __LINE__)
#define free(p) _debugFree(p, __FILE__, __LINE__)

#endif
