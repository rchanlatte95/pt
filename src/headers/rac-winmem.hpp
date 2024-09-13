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

		ExecuteRead = Read |	Execute,
		ExecuteReadWrite = ReadWrite | Execute,
		Full = ExecuteReadWrite
	};

	u64 PAGE_BYTE_SIZE = 4 * KB;
	u64 MAX_FILE_BYTE_SIZE = 8 * GB;

	INLINE bool ValidFileSize(u64 byte_len)
	{
		return byte_len > 0 && byte_len <= MAX_FILE_BYTE_SIZE;
	}
	INLINE bool InvalidFileSize(u64 byte_len)
	{
		return !ValidFileSize(byte_len);
	}

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
		// https://stackoverflow.com/questions/3989545/how-do-i-get-the-file-handle-from-the-fopen-file-structure
		// supposedly you can cast the file descriptor and it'll be a valid
		// HANDLE; however, that may not be portable to all Windows
		// platforms? Not sure. Better safe than sorry.
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
							p64 bytesToMap,
							LPCWSTR Name)
	{
		return CreateFileMappingW(file_handle,
								FileMappingAttributes,
								flProtect,
								bytesToMap.High(),
								bytesToMap.Low(),
								Name);
	}

	INLINE HANDLE CreateFileMap(HANDLE file_handle,
							u32 flProtect,
							p64 bytesToMap)
	{
		return CreateFileMappingW(file_handle,
								NULL,
								flProtect,
								bytesToMap.High(),
								bytesToMap.Low(),
								NULL);
	}

	INLINE mut_ptr GetMapView(HANDLE FileMappingObject,
							u32 DesiredAccess,
							p64 FileOffset,
							u64 bytesToMap)
	{
		return MapViewOfFile(FileMappingObject,
							DesiredAccess,
							FileOffset.High(),
							FileOffset.Low(),
							bytesToMap);
	}

	INLINE mut_ptr GetMapView(HANDLE FileMappingObject,
							u32 DesiredAccess,
							u64 bytesToMap)
	{
		return MapViewOfFile(FileMappingObject,
							DesiredAccess,
							0,
							0,
							bytesToMap);
	}

	INLINE HANDLE CreateFileMap(mut_FilePtr File,
							u32 flProtect,
							p64 bytesToMap)
	{
		return CreateFileMappingW(File,
								NULL,
								flProtect,
								bytesToMap.High(),
								bytesToMap.Low(),
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
	MAY_INLINE ptr mmap(PageMemProtection prot,
					MemoryMapType flags,
					mut_FilePtr file,
					ptr_offset file_ptr_offset,
					u64 byte_len)
	{
		if (InvalidFileSize(byte_len)) { return MAP_FAILED; }
		if (prot & ~(PageMemProtection::Full)) { return MAP_FAILED; }

		bool anonymous = flags & MemoryMapType::Anonymous;
		if (file == nullptr)
		{
			if (!anonymous || file_ptr_offset) { return MAP_FAILED; }
		}
		else if (anonymous) { return MAP_FAILED; }

		mut_u32 fl_protect;
		if (prot & PageMemProtection::Write)
		{
			if (prot & PageMemProtection::Execute)
			{
				fl_protect = PAGE_EXECUTE_READWRITE;
			}
			else { fl_protect = PAGE_READWRITE; }
		}
		else if (prot & PageMemProtection::Execute)
		{
			if (prot & PageMemProtection::Read)
			{
				fl_protect = PAGE_EXECUTE_READ;
			}
			else { fl_protect = PAGE_EXECUTE; }
		}
		else { fl_protect = PAGE_READONLY; }

		HANDLE target_file_handle = GetHandleFromFile(file);
		if (target_file_handle == INVALID_HANDLE_VALUE)
		{
			return MAP_FAILED;
		}

		mut_p64 end = file_ptr_offset + byte_len;
		HANDLE map_handle = CreateFileMappingW(target_file_handle,
												NULL,
												fl_protect,
												end.High(),
												end.Low(),
												NULL);
		if (map_handle == NULL) { return MAP_FAILED; }

		mut_u32 desired_access;
		if (prot & PageMemProtection::Write)
		{
			desired_access = FILE_MAP_WRITE;
		}
		else  { desired_access = FILE_MAP_READ; }

		if (prot & PageMemProtection::Execute)
		{
			desired_access |= FILE_MAP_EXECUTE;
		}
		if (flags & MemoryMapType::Private)
		{
			desired_access |= FILE_MAP_COPY;
		}

		mut_p64 offset_ = file_ptr_offset;
		mut_ptr ret = GetMapView(map_handle, desired_access, offset_, byte_len);
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
		return mmap(PageMemProtection::None, flags, file, offset, length);
	}
	MAY_INLINE ptr MapPrivateMem(mut_FilePtr file,
							u64 length,
							ptr_offset offset,
							PageMemProtection prot = PageMemProtection::None)
	{
		return mmap(prot, MemoryMapType::Private, file, offset, length);
	}
	MAY_INLINE ptr MapSharedMem(mut_FilePtr file,
							u64 length,
							ptr_offset offset,
							PageMemProtection prot = PageMemProtection::None)
	{
		return mmap(prot, MemoryMapType::Shared, file, offset, length);
	}
	MAY_INLINE ptr MapAnonMem(mut_FilePtr file,
							u64 length,
							ptr_offset offset,
							PageMemProtection prot = PageMemProtection::None)
	{
		return mmap(prot, MemoryMapType::Anonymous, file, offset, length);
	}
	MAY_INLINE ptr MapMem(mut_FilePtr file, u64 length,
						MemoryMapType flags = MemoryMapType::Private)
	{
		return mmap(PageMemProtection::Full, flags, file, 0, length);
	}
	MAY_INLINE ptr MapPrivateMem(mut_FilePtr file,
							u64 length,
							PageMemProtection prot = PageMemProtection::None)
	{
		return mmap(prot, MemoryMapType::Private, file, 0, length);
	}
	MAY_INLINE ptr MapSharedMem(mut_FilePtr file,
							u64 length,
							PageMemProtection prot = PageMemProtection::None)
	{
		return mmap(prot, MemoryMapType::Shared, file, 0, length);
	}
	MAY_INLINE ptr MapAnonMem(mut_FilePtr file,
							u64 length,
							PageMemProtection prot = PageMemProtection::None)
	{
		return mmap(prot, MemoryMapType::Anonymous, file, 0, length);
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
	INLINE bool UnmapMem(ptr addr)
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
