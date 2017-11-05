// Simple debug print malloc/free functions.

#ifdef _DEBUG

// Debug memory allocation routines.
#include "debugMalloc.h"

// Macros defined after our replacement functions.
#define malloc(size) _debugMalloc(size, __FILE__, __LINE__)
#define free(p) _debugFree(p, __FILE__, __LINE__)
#define exit(s) _debugExit(s)

#endif
