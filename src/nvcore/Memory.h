// This code is in the public domain -- castanyo@yahoo.es

#ifndef NV_CORE_MEMORY_H
#define NV_CORE_MEMORY_H

#include <nvcore/nvcore.h>

#include <stdlib.h> // malloc(), realloc() and free()
#include <stddef.h>	// size_t

//#include <new>	// new and delete

// Custom memory allocator
namespace nv
{
	namespace mem 
	{
		NVCORE_API void * malloc(size_t size);
		NVCORE_API void * malloc(size_t size, const char * file, int line);
		
		NVCORE_API void free(const void * ptr);
		NVCORE_API void * realloc(void * ptr, size_t size);
		
	} // mem namespace
	
} // nv namespace

#endif // NV_CORE_MEMORY_H
