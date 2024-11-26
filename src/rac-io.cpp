#include "headers/rac-io.hpp"

namespace rac::io
{
    MAY_INLINE std::filesystem::path GetDesktopPath()
    {
        wchar_t* p;
        if (S_OK != SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &p))
        {
            return EMPTY_STD_STRING;
        }
        std::filesystem::path result = p;
        CoTaskMemFree(p);
        return result;
    }
    MAY_INLINE std::string GetDesktopPathStr()
    {
        return GetDesktopPath().string();
    }

    FileSaveResult::mut_FileSaveResult() {}
    FileSaveResult::mut_FileSaveResult(bool result)
    {
        Succeeded = result;
    }
    FileSaveResult::mut_FileSaveResult(i8 result)
    {
        Succeeded = result != 0;
    }
    FileSaveResult::mut_FileSaveResult(i16 result)
    {
        Succeeded = result != 0;
    }
    FileSaveResult::mut_FileSaveResult(i32 result)
    {
        Succeeded = result != 0;
    }
    FileSaveResult::mut_FileSaveResult(i64 result)
    {
        Succeeded = result != 0;
    }
    FileSaveResult::mut_FileSaveResult(ptr result)
    {
        Succeeded = result != nullptr;
    }

    constexpr bool FileSaveResult::Failed() const noexcept
    {
        return !Succeeded;
    }
}