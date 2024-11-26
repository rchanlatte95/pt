#pragma once
#include "rac.hpp"

namespace rac::io
{
    std::string EMPTY_STD_STRING = std::string("");

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

        mut_FileSaveResult() {}
        mut_FileSaveResult(bool result)
        {
            Succeeded = result;
        }
        mut_FileSaveResult(i8 result)
        {
            Succeeded = result != 0;
        }
        mut_FileSaveResult(i16 result)
        {
            Succeeded = result != 0;
        }
        mut_FileSaveResult(i32 result)
        {
            Succeeded = result != 0;
        }
        mut_FileSaveResult(i64 result)
        {
            Succeeded = result != 0;
        }
        mut_FileSaveResult(ptr result)
        {
            Succeeded = result != nullptr;
        }

        constexpr bool Failed() const noexcept { return !Succeeded; }
    };
}
