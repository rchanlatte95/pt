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
	class mut_WinU16;
	typedef WinU32* mut_WinU16ptr;
	typedef WinU32& mut_WinU16ref;
	typedef const WinU32 WinU16;
	typedef const WinU32* WinU16ptr;
	typedef const WinU32& WinU16ref;

	class mut_WinU32;
	typedef WinU32* mut_WinU32ptr;
	typedef WinU32& mut_WinU32ref;
	typedef const WinU32 WinU32;
	typedef const WinU32* WinU32ptr;
	typedef const WinU32& WinU32ref;

	class mut_WinU64;
	typedef WinU32* mut_WinU64ptr;
	typedef WinU32& mut_WinU64ref;
	typedef const WinU32 WinU64;
	typedef const WinU32* WinU64ptr;
	typedef const WinU32& WinU64ref;

	class mut_WinU16
	{
		union
		{
			mut_u8 low;
			mut_u8 high;

			mut_u16 word;
		};

	public:
		mut_WinU16() { word = 0; }
		mut_WinU16(u16 w) { word = w; }
		mut_WinU16(WORD w) { word = w; }
		mut_WinU16(u8 low_bits, u8 high_bits)
		{
			low = low_bits;
			high = high_bits;
		}
		mut_WinU16(BYTE low_bits, BYTE high_bits)
		{
			low = low_bits;
			high = high_bits;
		}
	};

	class mut_WinU32
	{
		union
		{
			mut_u8 bytes[sizeof(u32)];

			mut_u16 low;
			mut_u16 high;

			mut_u32 dword;
		};

	public:
		mut_WinU32() { dword = 0; }
		mut_WinU32(u32 dw) { dword = dw; }
		mut_WinU32(DWORD dw) { dword = dw; }
		mut_WinU32(u16 low_bits, u16 high_bits)
		{
			low = low_bits;
			high = high_bits;
		}
		mut_WinU32(WORD low_bits, WORD high_bits)
		{
			low = low_bits;
			high = high_bits;
		}
		mut_WinU32(u8 b0, u8 b1, u8 b2, u8 b3)
		{
			bytes[0] = b0;
			bytes[1] = b1;
			bytes[2] = b2;
			bytes[3] = b3;
		}
		mut_WinU32(BYTE b0, BYTE b1, BYTE b2, BYTE b3)
		{
			bytes[0] = b0;
			bytes[1] = b1;
			bytes[2] = b2;
			bytes[3] = b3;
		}
	};

	class mut_WinU64
	{
		union
		{
			mut_u8 bytes[sizeof(u64)];
			mut_WinU16 words[sizeof(u64) / sizeof(u16)];

			mut_WinU32 low;
			mut_WinU32 high;

			mut_u64 qword;
		};

	public:
		mut_WinU64() { qword = 0; }
		mut_WinU64(u64 q) { qword = q; }
		mut_WinU64(QWORD q) { qword = q; }
	};

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

	INLINE i32 GetFileDescriptor(mut_FileHandle file)
	{
		return _fileno(file);
	}

	INLINE errno_t SetFileSize(i32 file_descriptor, u64 len)
	{
		return _chsize_s(file_descriptor, len);
	}

	INLINE errno_t SetFileSize(mut_FileHandle file, u64 len)
	{
		return _chsize_s(GetFileDescriptor(file), len);
	}

	INLINE errno_t ftruncate(mut_FileHandle file, u64 len)
	{
		return _chsize_s(GetFileDescriptor(file), len);
	}

	INLINE errno_t ftruncate(i32 file_descriptor, u64 len)
	{
		return _chsize_s(file_descriptor, len);
	}

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
	MAY_INLINE ptr mmap(ptr start, u64 len, MemoryMapProtection prot, MemoryMapType flags, mut_FileHandle file, ptr_offset offset)
	{
		if (prot & ~(MemoryMapProtection::Full))
		{
			return MAP_FAILED;
		}
		bool anonymous = flags & MemoryMapType::Anonymous;
		if (file == nullptr)
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