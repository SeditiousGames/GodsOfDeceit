/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mohammad S. Babaei
 * Copyright (c) 2018 - 2019 Seditious Games Studio
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @section DESCRIPTION
 *
 */


#include "GPlatformImpl/GFileSystemImpl.h"

#include <fstream>
#include <iterator>

#include <Containers/StringConv.h>
#include <Misc/AssertionMacros.h>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

#include <GHacks/GInclude_Windows.h>

#define  GFILESYSTEM_ERROR_DIALOG_TITLE "IO Error"
#define  GFILESYSTEM_UNKNOWN_ERROR      "GFileSystem: unknown error!"

void GFileSystemImpl::CombinePaths(FString& Out_CombinedPaths,
                                   const std::initializer_list<FString>& Paths)
{
    boost::filesystem::path CombinedPaths;

    for (const FString& Path : Paths)
    {
        CombinedPaths /=
                boost::filesystem::path(StringCast<ANSICHAR>(*Path).Get());
    }

    Out_CombinedPaths =
            StringCast<WIDECHAR>(CombinedPaths.string().c_str()).Get();
}

bool GFileSystemImpl::DirectoryExists(const FString& Directory)
{
    try
    {
        boost::filesystem::path Path(StringCast<ANSICHAR>(*Directory).Get());

        if (boost::filesystem::exists(Path))
        {
            if (boost::filesystem::is_directory(Path))
            {
                return true;
            }
            else if (boost::filesystem::is_regular_file(Path))
            {
                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }

    return false;
}

bool GFileSystemImpl::FileExists(const FString& File)
{
    try
    {
        boost::filesystem::path Path(StringCast<ANSICHAR>(*File).Get());

        if (boost::filesystem::exists(Path))
        {
            if (boost::filesystem::is_regular_file(Path))
            {
                return true;
            }
            else if (boost::filesystem::is_directory(Path))
            {
                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }

    return false;
}

std::size_t GFileSystemImpl::GetFileSize(const FString& File)
{
    try
    {
        return boost::filesystem::file_size(StringCast<ANSICHAR>(*File).Get());
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }

    return 0;
}

void GFileSystemImpl::CreateDirectory(const FString& Directory,
                                      const bool bCreateParents)
{
    try {
        boost::filesystem::path Path(StringCast<ANSICHAR>(*Directory).Get());

        if (bCreateParents)
        {
            boost::filesystem::create_directories(Path);
        }
        else
        {
            boost::filesystem::create_directory(Path);
        }
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::Erase(const FString& Path, const bool bRecursive)
{
    try
    {
        if (bRecursive)
        {
            boost::filesystem::remove_all(StringCast<ANSICHAR>(*Path).Get());
        }
        else {
            boost::filesystem::remove(StringCast<ANSICHAR>(*Path).Get());
        }
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::Move(const FString& From, const FString& To)
{
    try
    {
        boost::filesystem::rename(StringCast<ANSICHAR>(*From).Get(),
                                  StringCast<ANSICHAR>(*To).Get());
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::CopyFile(const FString& From, const FString& To,
                               const bool bOverwrite)
{
    try
    {
        boost::filesystem::copy_file(
                    StringCast<ANSICHAR>(*From).Get(),
                    StringCast<ANSICHAR>(*To).Get(),
                    bOverwrite
                    ? boost::filesystem::copy_option::overwrite_if_exists
                    : boost::filesystem::copy_option::fail_if_exists);
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::Read(const FString& File, FString& Out_Data)
{
    try
    {
        Out_Data = TEXT("");

        std::ifstream InputFileStream(StringCast<ANSICHAR>(*File).Get());
        std::string Data((std::istreambuf_iterator<char>(InputFileStream)),
                         std::istreambuf_iterator<char>());
        InputFileStream.close();

        Out_Data = StringCast<WIDECHAR>(Data.c_str()).Get();
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::Read(const FString& File, std::string& Out_Data)
{
    try
    {
        Out_Data.clear();

        std::ifstream InputFileStream(StringCast<ANSICHAR>(*File).Get());
        Out_Data.assign((std::istreambuf_iterator<char>(InputFileStream)),
                        std::istreambuf_iterator<char>());
        InputFileStream.close();
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::Write(const FString& File, const FString& Data)
{
    try
    {
        std::ofstream OutputFileStream(StringCast<ANSICHAR>(*File).Get(),
                                       std::ios::out | std::ios::trunc);
        if (OutputFileStream.is_open())
        {
            OutputFileStream << StringCast<ANSICHAR>(*Data).Get();
            OutputFileStream.close();
        }
        else
        {
#if defined ( _WIN32 ) || defined ( _WIN64 )
            MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                        GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
            checkf(false, TEXT("%s"),
                   StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
        }
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}

void GFileSystemImpl::Write(const FString& File, const std::string& Data)
{
    try
    {
        std::ofstream OutputFileStream(StringCast<ANSICHAR>(*File).Get(),
                                       std::ios::out | std::ios::trunc);
        if (OutputFileStream.is_open())
        {
            OutputFileStream << Data;
            OutputFileStream.close();
        }
        else
        {
#if defined ( _WIN32 ) || defined ( _WIN64 )
            MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                        GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
            checkf(false, TEXT("%s"),
                   StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
        }
    }

    catch (const boost::filesystem::filesystem_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GFILESYSTEM_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GFILESYSTEM_UNKNOWN_ERROR,
                    GFILESYSTEM_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GFILESYSTEM_UNKNOWN_ERROR).Get());
    }
}
