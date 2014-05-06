// SwiftShader Software Renderer
//
// Copyright(c) 2005-2012 TransGaming Inc.
//
// All rights reserved. No part of this software may be copied, distributed, transmitted,
// transcribed, stored in a retrieval system, translated into any human or computer
// language by any means, or disclosed to third parties without the explicit written
// agreement of TransGaming Inc. Without such an agreement, no rights or licenses, express
// or implied, including but not limited to any patent rights, are granted to you.
//

#include "Memory.hpp"

#include "Types.hpp"
#include "Debug.hpp"

#if defined(_WIN32)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
#else
	#include <sys/mman.h>
	#include <unistd.h>
#endif

#include <memory.h>

#undef allocate
#undef deallocate
#undef allocateZero
#undef deallocateZero

struct Allocation
{
//	size_t bytes;
	unsigned char *block;
};

void *allocate(size_t bytes, int alignment)
{
	unsigned char *block = new unsigned char[bytes + sizeof(Allocation) + alignment];
	unsigned char *aligned = (unsigned char*)((uintptr_t)(block + sizeof(Allocation) + alignment - 1) & -(uintptr_t)alignment);
	Allocation *allocation = (Allocation*)(aligned - sizeof(Allocation));

//	allocation->bytes = bytes;
	allocation->block = block;

	return aligned;
}

void *allocateZero(size_t bytes, int alignment)
{
	void *memory = allocate(bytes, alignment);

	memset(memory, 0, bytes);

	return memory;
}

void deallocate(void *memory)
{
	if(memory)
	{
		unsigned char *aligned = (unsigned char*)memory;
		Allocation *allocation = (Allocation*)(aligned - sizeof(Allocation));

		delete[] allocation->block;
	}
}

void *allocateExecutable(size_t bytes)
{
	int pageSize = 4096;

	#if defined(_WIN32)
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		pageSize = systemInfo.dwPageSize;
	#else
		pageSize = getpagesize();
	#endif

	return allocate((bytes + pageSize - 1) & -pageSize, pageSize);
}

void markExecutable(void *memory, size_t bytes)
{
	#if defined(_WIN32)
		unsigned long oldProtection;
		VirtualProtect(memory, bytes, PAGE_EXECUTE_READ, &oldProtection);
	#else
		mprotect(memory, bytes, PROT_READ | PROT_WRITE | PROT_EXEC);
	#endif
}

void deallocateExecutable(void *memory, size_t bytes)
{
	#if defined(_WIN32)
		unsigned long oldProtection;
		VirtualProtect(memory, bytes, PAGE_READWRITE, &oldProtection);
	#else
		mprotect(memory, bytes, PROT_READ | PROT_WRITE);
	#endif

	deallocate(memory);
}

void *allocate(size_t bytes, const char *function)
{
	trace("[0x%0.8X]%s(...)\n", 0xFFFFFFFF, function);

	void *memory = allocate(bytes);

	trace("\t0x%0.8X = allocate(%d)\n", memory, bytes);

	return memory;
}

void *allocateZero(size_t bytes, const char *function)
{
	trace("[0x%0.8X]%s(...)\n", 0xFFFFFFFF, function);

	void *memory = allocateZero(bytes);

	trace("\t0x%0.8X = allocateZero(%d)\n", memory, bytes);

	return memory;
}

void deallocate(void *memory, const char *function)
{
	if(memory)
	{
		trace("[0x%0.8X]%s(...)\n", 0xFFFFFFFF, function);
		trace("\tdeallocate(0x%0.8X)\n", memory);

		deallocate(memory);
	}
}