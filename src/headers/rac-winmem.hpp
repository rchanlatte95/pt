#pragma once
#pragma warning(push)
#pragma warning(disable:4201)

#include "rac.hpp"
#include "rac-packedtypes.hpp"

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

	enum PageMemProtection : u32
	{
		None = 0x0,

		Read = 0x1,
		Write = 0x2,
		ReadWrite = Read | Write,
		Execute = 0x4,

		ExecuteRead = Read | Execute,
		ExecuteReadWrite = ReadWrite | Execute,
		Full = ExecuteReadWrite
	};

	u64 PAGE_BYTE_SIZE = 4 * KB;
	u64 MAX_FILE_BYTE_SIZE = 8 * GB;

	INLINE bool ValidFileSize(u64 byte_len);
	INLINE bool InvalidFileSize(u64 byte_len);
	INLINE i32 GetFileDescriptor(mut_FilePtr file);
	INLINE HANDLE GetHandleFromDescriptor(i32 file_descriptor);
	INLINE HANDLE GetHandleFromFile(mut_FilePtr file);

	INLINE errno_t SetFileSize(i32 file_descriptor, u64 len);
	INLINE errno_t SetFileSize(mut_FilePtr file, u64 len);

	INLINE errno_t ftruncate(mut_FilePtr file, u64 len);
	INLINE errno_t ftruncate(i32 file_descriptor, u64 len);

	// https://man7.org/linux/man-pages/man2/ftruncate.2.html
	INLINE errno_t truncate(cstr path, u64 len);

	INLINE ptr AlignPow2(ptr memory_handle, u64 pow2_alignment);
	INLINE ptr AlignToPage(ptr memory_handle);
	INLINE ptr Align(ptr memory_handle, u64 alignment_multiple);

	INLINE HANDLE CreateFileMap(HANDLE file_handle,
		LPSECURITY_ATTRIBUTES FileMappingAttributes,
		u32 flProtect,
		p64 bytesToMap,
		LPCWSTR Name);
	INLINE HANDLE CreateFileMap(HANDLE file_handle,
		u32 flProtect,
		p64 bytesToMap);

	INLINE mut_ptr GetMapView(HANDLE FileMappingObject,
		u32 DesiredAccess,
		p64 FileOffset,
		u64 bytesToMap);
	INLINE mut_ptr GetMapView(HANDLE FileMappingObject,
		u32 DesiredAccess,
		u64 bytesToMap);

	INLINE HANDLE CreateFileMap(mut_FilePtr File,
		u32 flProtect,
		p64 bytesToMap);

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
	MAY_INLINE ptr mmap(PageMemProtection prot,
		MemoryMapType flags,
		mut_FilePtr file,
		ptr_offset file_ptr_offset,
		u64 byte_len);
	MAY_INLINE ptr MapMem(mut_FilePtr file, u64 length,
		ptr_offset offset,
		MemoryMapType flags = MemoryMapType::Private);
	MAY_INLINE ptr MapPrivateMem(mut_FilePtr file,
		u64 length,
		ptr_offset offset,
		PageMemProtection prot = PageMemProtection::None);
	MAY_INLINE ptr MapSharedMem(mut_FilePtr file,
		u64 length,
		ptr_offset offset,
		PageMemProtection prot = PageMemProtection::None);
	MAY_INLINE ptr MapAnonMem(mut_FilePtr file,
		u64 length,
		ptr_offset offset,
		PageMemProtection prot = PageMemProtection::None);
	MAY_INLINE ptr MapMem(mut_FilePtr file, u64 length,
		MemoryMapType flags = MemoryMapType::Private);
	MAY_INLINE ptr MapPrivateMem(mut_FilePtr file,
		u64 length,
		PageMemProtection prot = PageMemProtection::None);
	MAY_INLINE ptr MapSharedMem(mut_FilePtr file,
		u64 length,
		PageMemProtection prot = PageMemProtection::None);
	MAY_INLINE ptr MapAnonMem(mut_FilePtr file,
		u64 length,
		PageMemProtection prot = PageMemProtection::None);

	// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile
	INLINE bool munmap(mut_ptr addr);
	INLINE bool UnmapMem(ptr addr);
}

#pragma warning(pop)
