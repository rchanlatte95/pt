#pragma once
#include "rac.hpp"

#ifdef _MSC_VER
#define MAP_FAILED    ((void *) -1)
#endif

// NOTE(RYAN_2024-08-25): This is intended to be a wrapper class for
// useful memory functions that Windows makes a bit tedious compared to
// something Unix-like
namespace rac::mem::windows
{
	enum MemoryMapType : i32
	{
		Shared = 0x1, Private = 0x2, Anonymous = 0x20,
	};
	enum MemoryMapProtection : i32
	{
		None = 0x0,

		Read = 0x1, Write = 0x2, Execute = 0x4,

		ReadWrite = Read | Write, Full = Read | Write | Execute
	};

	u64 PAGE_BYTE_SIZE = 4 * KB;

	INLINE ptr AlignPow2(ptr memory_handle, u64 pow2_alignment)
	{
		if (memory_handle == nullptr) { return nullptr; }

		u64 addr = (u64)memory_handle;
		u64 mod = addr & (pow2_alignment - 1);
		if (mod == 0) { return memory_handle; }

		u64 offset = pow2_alignment - mod;
		mut_i8ptr aligned_ptr = (mut_i8ptr)memory_handle + offset;
		return (ptr)aligned_ptr;
	}

	INLINE ptr AlignToPage(ptr memory_handle)
	{
		return AlignPow2(memory_handle, PAGE_BYTE_SIZE);
	}

	INLINE ptr Align(ptr memory_handle, u64 alignment_multiple)
	{
		if (memory_handle == nullptr) { return nullptr; }

		u64 addr = (u64)memory_handle;
		u64 mod = addr % alignment_multiple;
		if (mod == 0) { return memory_handle; }

		u64 offset = alignment_multiple - mod;
		mut_i8ptr aligned_ptr = (mut_i8ptr)memory_handle + offset;
		return (ptr)aligned_ptr;
	}

	// TODO(RYAN_2024-08-25): Implement mmap equivalent and helper
	// functions
	//
	// references:
	//		https://man7.org/linux/man-pages/man2/mmap.2.html
	//		https://bytes.com/topic/c/651056-c-efficiently-writing-large-quantities-data-file
	//		https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga
	//		https://github.com/inexinferis/SyscallWrapper/blob/88005067e5ad96d19dcf6adfb15ef064ef62f3a1/kernel.cpp#L2889
	//		https://github.com/m-labs/uclibc-lm32/blob/master/utils/mmap-windows.c
	//
	// void *mmap(void addr[.length], size_t length, int prot, int flags, int fd, off_t offset);
	MAY_INLINE ptr mmap(ptr start, u64 len, MemoryMapProtection prot, MemoryMapType flags, HANDLE file_descriptor, ptr_offset offset)
	{
		if (prot & ~(MemoryMapProtection::Full))
		{
			return MAP_FAILED;
		}
		bool anonymous = flags & MemoryMapType::Anonymous;
		if (file_descriptor == INVALID_HANDLE_VALUE)
		{
			if (!anonymous || offset)
			{
				return MAP_FAILED;
			}
		}
		else if (anonymous)
		{
			return MAP_FAILED;
		}
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile
	INLINE bool munmap(mut_ptr addr)
	{
		if (UnmapViewOfFile(addr) != 0)
		{
			addr = nullptr;
			return true;
		}

		return false;
	}
}