#pragma once
#include "rac.hpp"

namespace rac::io
{
    MAY_INLINE std::filesystem::path GetDesktopPath();
    MAY_INLINE std::string GetDesktopPathStr();

    class mut_FileSaveResult;
    typedef mut_FileSaveResult* mut_FileSaveResult_ptr;
    typedef mut_FileSaveResult& mut_FileSaveResult_ref;
    typedef const mut_FileSaveResult FileSaveResult;
    typedef const FileSaveResult* FileSaveResult_ptr;
    typedef const FileSaveResult& FileSaveResult_ref;
    class mut_FileSaveResult
    {
    public:
        bool Succeeded = false;

        mut_FileSaveResult();
        mut_FileSaveResult(bool result);
        mut_FileSaveResult(i8 result);
        mut_FileSaveResult(i16 result);
        mut_FileSaveResult(i32 result);
        mut_FileSaveResult(i64 result);
        mut_FileSaveResult(ptr result);

        constexpr bool Failed() const noexcept;
    };
}
