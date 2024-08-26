#pragma once
#include "rac.hpp"

// NOTE(2024-08-25): This is intended to be a wrapper class for useful
// memory functions that Windows makes a bit tedious compared to
// something like Linux

#ifdef _MSC_VER

#define MAP_FAILED    ((void *) -1)

#endif

namespace rac::mem
{
	enum MemoryMapType : u32
	{
		Shared = 0x1, Private = 0x2, Anonymous = 0x20,
	};

	enum MemoryMapProtection : u32
	{
		None = 0x0,

		Read = 0x1, Write = 0x2, Execute = 0x4,

		ReadWrite = Read | Write, ReadWriteExecute = Read | Write | Execute
	};
}