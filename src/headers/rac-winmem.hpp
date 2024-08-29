#pragma once
#pragma warning(push)
#pragma warning(disable:4201)

#include "rac.hpp"

#ifdef _MSC_VER
#define MAP_FAILED    ((void *) -1)
#endif

// NOTE(RYAN_2024-08-25): This is intended to be a wrapper class for
// useful memory functions that Windows makes a bit tedious compared to
// something Unix-like
namespace rac::mem::windows
{
	class mut_wordU16;
	typedef mut_wordU16* mut_wordU16ptr;
	typedef mut_wordU16& mut_wordU16ref;
	typedef const mut_wordU16 wordU16;
	typedef const mut_wordU16* wordU16ptr;
	typedef const mut_wordU16& wordU16ref;

	class mut_dwordU32;
	typedef mut_dwordU32* mut_dwordU32ptr;
	typedef mut_dwordU32& mut_dwordU32ref;
	typedef const mut_dwordU32 dwordU32;
	typedef const mut_dwordU32* dwordU32ptr;
	typedef const mut_dwordU32& dwordU32ref;

	class mut_qwordU64;
	typedef mut_qwordU64* mut_qwordU64ptr;
	typedef mut_qwordU64& mut_qwordU64ref;
	typedef const mut_qwordU64 qwordU64;
	typedef const mut_qwordU64* qwordU64ptr;
	typedef const mut_qwordU64& qwordU64ref;

	static i32 HIGH = 0;
	static i32 LOW = 1;

	struct packed_dword
	{
		union
		{
			mut_u8 bytes[sizeof(u32)];
			mut_u16 words[sizeof(u32) / sizeof(u16)];
		};
	};

	class mut_wordU16
	{
		union
		{
			mut_u16 word;
			struct
			{
				mut_u8 bytes[sizeof(u16)];
			};
		};

	public:
		mut_wordU16()
		{
			word = 0;
			bytes[HIGH] = 0;
			bytes[1] = 0;
		}

		// mut_wordU16(WORD w)
		mut_wordU16(u16 w)
		{
			bytes[HIGH] = 0;
			bytes[1] = 0;
			word = w;
		}

		// mut_wordU16(BYTE low_bits, BYTE high_bits)
		mut_wordU16(u8 low_bits, u8 high_bits)
		{
			word = 0;
			bytes[HIGH] = low_bits;
			bytes[1] = high_bits;
		}
	};

	class mut_dwordU32
	{
		union
		{
			mut_u32 dword;
			struct packed_dword packed;
		};

	public:
		mut_dwordU32()
		{
			packed.words[HIGH] = 0;
			packed.words[LOW] = 0;
			dword = 0;
		}

		// mut_dwordU32(DWORD dw)
		mut_dwordU32(u32 dw)
		{
			packed.words[HIGH] = 0;
			packed.words[LOW] = 0;
			dword = dw;
		}

		// mut_dwordU32(WORD low_bits, WORD high_bits)
		mut_dwordU32(u16 low_bits, u16 high_bits)
		{
			dword = 0;
			packed.words[HIGH] = high_bits;
			packed.words[LOW] = low_bits;
		}

		// mut_dwordU32(BYTE b0, BYTE b1, BYTE b2, BYTE b3)
		mut_dwordU32(u8 b0, u8 b1, u8 b2, u8 b3)
		{
			dword = 0;
			packed.bytes[0] = b0;
			packed.bytes[1] = b1;
			packed.bytes[2] = b2;
			packed.bytes[3] = b3;
		}

		INLINE u32 Dword() const noexcept { return dword; }
		INLINE u16 High() const noexcept { return packed.words[HIGH]; }
		INLINE u16 Low() const noexcept { return packed.words[LOW]; }
	};

	class mut_qwordU64
	{
		mut_u64 qword;
		union
		{
			mut_u8 bytes[sizeof(u64)];
			mut_wordU16 words[sizeof(u64) / sizeof(u16)];
			mut_dwordU32 dwords[sizeof(u64) / sizeof(u32)];
		};

	public:
		mut_qwordU64()
		{
			dwords[HIGH] = 0;
			dwords[LOW] = 0;
			qword = 0;
		}

		// mut_qwordU64(QWORD q)
		mut_qwordU64(u64 q)
		{
			dwords[HIGH] = 0;
			dwords[LOW] = 0;
			qword = q;
		}
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

	INLINE i32 GetFileDescriptor(mut_FilePtr file)
	{
		return _fileno(file);
	}

	INLINE HANDLE GetHandleFromDescriptor(i32 file_descriptor)
	{
		return file_descriptor == -1 ? INVALID_HANDLE_VALUE : (HANDLE)_get_osfhandle(file_descriptor);
	}

	INLINE HANDLE GetHandleFromFile(mut_FilePtr file)
	{
		//https://stackoverflow.com/questions/3989545/how-do-i-get-the-file-handle-from-the-fopen-file-structure
		// supposedly you can cast the file descriptor and it'll be a valid
		// HANDLE; however, that may not be portable to all Windows platforms?
		// Not sure. Better safe than sorry.
		if (file == nullptr)
		{
			return INVALID_HANDLE_VALUE;
		}
		return GetHandleFromDescriptor(GetFileDescriptor(file));
	}

	INLINE errno_t SetFileSize(i32 file_descriptor, u64 len)
	{
		return _chsize_s(file_descriptor, len);
	}

	INLINE errno_t SetFileSize(mut_FilePtr file, u64 len)
	{
		return _chsize_s(GetFileDescriptor(file), len);
	}

	INLINE errno_t ftruncate(mut_FilePtr file, u64 len)
	{
		return _chsize_s(GetFileDescriptor(file), len);
	}

	INLINE errno_t ftruncate(i32 file_descriptor, u64 len)
	{
		return _chsize_s(file_descriptor, len);
	}

	// https://man7.org/linux/man-pages/man2/ftruncate.2.html
	// TODO(RYAN_2024-08-26): Add truncate
	INLINE errno_t truncate(cstr path, u64 len)
	{
		mut_FilePtr fp = nullptr;
		errno_t open_res = fopen_s(&fp, path, "a+");
		if (open_res != 0) { return open_res; }

		errno_t resize_res = _chsize_s(GetFileDescriptor(fp), len);
		fclose(fp);
		return resize_res;
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

	INLINE HANDLE CreateFileMap(HANDLE file_handle,
							LPSECURITY_ATTRIBUTES FileMappingAttributes,
							u32 flProtect,
							dwordU32 maxSize,
							LPCWSTR Name)
	{
		return CreateFileMappingW(file_handle,
								FileMappingAttributes,
								flProtect,
								maxSize.High(),
								maxSize.Low(),
								Name);
	}

	INLINE HANDLE CreateFileMap(HANDLE file_handle,
							u32 flProtect,
							dwordU32 maxSize)
	{
		return CreateFileMappingW(file_handle,
								NULL,
								flProtect,
								maxSize.High(),
								maxSize.Low(),
								NULL);
	}

	INLINE mut_ptr GetMapView(HANDLE FileMappingObject,
							u32 DesiredAccess,
							dwordU32 FileOffset,
							u64 NumberOfBytesToMap)
	{
		return MapViewOfFile(FileMappingObject,
							DesiredAccess,
							FileOffset.High(),
							FileOffset.Low(),
							NumberOfBytesToMap);
	}

	INLINE HANDLE CreateFileMap(mut_FilePtr File,
							u32 flProtect,
							dwordU32 maxSize)
	{
		return CreateFileMappingW(File,
								NULL,
								flProtect,
								maxSize.High(),
								maxSize.Low(),
								NULL);
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
	MAY_INLINE ptr mmap(MemoryMapProtection prot,
						MemoryMapType flags,
						mut_FilePtr file,
						ptr_offset offset,
						u64 length)
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

		mut_u32 fl_protect;
		if (prot & MemoryMapProtection::Write)
		{
			if (prot & MemoryMapProtection::Execute)
			{
				fl_protect = PAGE_EXECUTE_READWRITE;
			}
			else
			{
				fl_protect = PAGE_READWRITE;
			}
		}
		else if (prot & MemoryMapProtection::Execute)
		{
			if (prot & MemoryMapProtection::Read)
			{
				fl_protect = PAGE_EXECUTE_READ;
			}
			else
			{
				fl_protect = PAGE_EXECUTE;
			}
		}
		else
		{
			fl_protect = PAGE_READONLY;
		}

		HANDLE target_map_file = GetHandleFromFile(file);
		if (target_map_file == INVALID_HANDLE_VALUE)
		{
			return MAP_FAILED;
		}

		mut_dwordU32 end = offset + (u32)length;
		HANDLE map_handle = CreateFileMap(target_map_file, fl_protect, end);
		if (map_handle == NULL)
		{
			return MAP_FAILED;
		}

		mut_dwordU32 offset_ = offset;
		mut_u32 desired_access;
		if (prot & MemoryMapProtection::Write)
		{
			desired_access = FILE_MAP_WRITE;
		}
		else
		{
			desired_access = FILE_MAP_READ;
		}

		if (prot & MemoryMapProtection::Execute)
		{
			desired_access |= FILE_MAP_EXECUTE;
		}
		if (flags & MemoryMapType::Private)
		{
			desired_access |= FILE_MAP_COPY;
		}

		mut_ptr ret = GetMapView(map_handle, desired_access, offset_, length);
		if (ret == nullptr)
		{
			CloseHandle(map_handle);
			ret = MAP_FAILED;
		}
		return ret;
	}

	MAY_INLINE ptr MapMem(mut_FilePtr file, u64 length,
						ptr_offset offset,
						MemoryMapType flags = MemoryMapType::Private)
	{
		return mmap(MemoryMapProtection::Full, flags, file, offset, length);
	}
	MAY_INLINE ptr MapPrivateMem(mut_FilePtr file, u64 length, ptr_offset offset, MemoryMapProtection prot = MemoryMapProtection::Full)
	{
		return mmap(prot, MemoryMapType::Private, file, offset, length);
	}
	MAY_INLINE ptr MapSharedMem(mut_FilePtr file, u64 length, ptr_offset offset, MemoryMapProtection prot = MemoryMapProtection::Full)
	{
		return mmap(prot, MemoryMapType::Shared, file, offset, length);
	}
	MAY_INLINE ptr MapAnonMem(mut_FilePtr file, u64 length, ptr_offset offset, MemoryMapProtection prot = MemoryMapProtection::Full)
	{
		return mmap(prot, MemoryMapType::Anonymous, file, offset, length);
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

#pragma warning(pop)
