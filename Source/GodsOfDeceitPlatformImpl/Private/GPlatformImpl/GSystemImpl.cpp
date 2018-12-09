/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 Mohammad S. Babaei
 * Copyright (c) 2018 Seditious Games Studio
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
 * Provides a low-level implementation for an abstraction layer on top of the
 * platform-specific API.
 */


#include "GSystemImpl.h"

#include <Containers/StringConv.h>
#include <Misc/AssertionMacros.h>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

THIRD_PARTY_INCLUDES_START
#include <fmt/format.h>
THIRD_PARTY_INCLUDES_END

#include <GHacks/GInclude_Windows.h>

#include <GVersionImpl/GBuildInfoImpl.h>

FString GSystemImpl::GetExecutablePath()
{
    boost::filesystem::path Path(
                boost::filesystem::initial_path<boost::filesystem::path>());

#if defined ( __linux__ )
    char ExePathBuffer[PATH_MAX];
    std::memset(ExePathBuffer, 0, sizeof(ExePathBuffer));

    /// NOTE
    /// /proc/self/exe yealds the same result
    char ProcPathBuffer[PATH_MAX];
    pid_t Pid = getpid();
    std::sprintf(ProcPathBuffer, "/proc/%d/exe", Pid);

    ssize_t Count = readlink(ProcPathBuffer, ExePathBuffer, PATH_MAX);
    bool bResult = (Count > 0);

    checkf(bResult, TEXT("FATAL: failed to get current directory path!"));

    FString PathString(StringCast<TCHAR>(ExePathBuffer).Get());
#elif defined ( _WIN32 ) || defined ( _WIN64 )
    char PathBuffer[MAX_PATH];
    DWORD Result = GetModuleFileNameA(NULL, PathBuffer, MAX_PATH);
    FString PathString(StringCast<TCHAR>(PathBuffer).Get());

    if (Result == ERROR_SUCCESS)
    {
        MessageBoxA(0,
                    fmt::format(
                        "FATAL: failed to get the current directory path! Error code: {0}",
                        Result).c_str(),
                    "IO Error", MB_OK);
        checkf(false, TEXT("Failed to get the current directory path!"));
    }
#else
    static_assert(false, "FATAL: unsuported platform!");
#endif  /* defined ( __linux__ ) */

    if (PathString.EndsWith(GSystemImpl::GetDirectorySeparatorChar(),
                            ESearchCase::IgnoreCase))
    {
        PathString = PathString.LeftChop(PathString.Len() - 2);
    }

    Path = boost::filesystem::system_complete(
                boost::filesystem::path(
                    StringCast<ANSICHAR>(*PathString).Get()));

    return FString(StringCast<TCHAR>(Path.string().c_str()).Get());
}

FString GSystemImpl::GetCurrentPath()
{
    boost::filesystem::path Path(
                boost::filesystem::system_complete(
                    boost::filesystem::current_path()));
    return FString(StringCast<TCHAR>(Path.string().c_str()).Get());
}

FString GSystemImpl::GetSystemDirectoryPath(const EGSystemDirectory Directory)
{
    boost::filesystem::path Path;
    FString PathString;

    switch (Directory)
    {

    case EGSystemDirectory::UserDesktop:
    {
#if defined ( __linux__ )
        PathString = GSystemImpl::GetSystemDirectoryPath(
                    EGSystemDirectory::UserHome);
        if (PathString.EndsWith(GSystemImpl::GetDirectorySeparatorChar(),
                                ESearchCase::IgnoreCase))
        {
            PathString = PathString.LeftChop(PathString.Len() - 2);
        }

        PathString += GSystemImpl::GetDirectorySeparatorChar()
                + TEXT("Desktop");
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        char PathBuffer[MAX_PATH];
        HRESULT result = SHGetFolderPathA(
                    NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, PathBuffer);

        if (result != S_OK)
        {
            MessageBoxA(0, fmt::format("Error code: {0}", result).c_str(),
                        "IO Error", MB_OK);
            checkf(false,
                   TEXT("FATAL: failed to get the user's desktop directory path!"));
        }

        PathString = StringCast<TCHAR>(PathBuffer).Get();
#endif  /* defined ( __linux__ ) */
    } break;

    case EGSystemDirectory::UserDocuments:
    {
#if defined ( __linux__ )
        PathString = GSystemImpl::GetSystemDirectoryPath(
                    EGSystemDirectory::UserHome);
        if (PathString.EndsWith(GSystemImpl::GetDirectorySeparatorChar(),
                                ESearchCase::IgnoreCase))
        {
            PathString = PathString.LeftChop(PathString.Len() - 2);
        }

        PathString += GSystemImpl::GetDirectorySeparatorChar()
                + TEXT("Documents");
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        char PathBuffer[MAX_PATH];
        HRESULT Result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL,
                                          SHGFP_TYPE_CURRENT, PathBuffer);

        if (Result != S_OK)
        {
            MessageBoxA(0,
                        fmt::format("FATAL: error code: {0}", Result).c_str(),
                        "IO Error", MB_OK);
            checkf(false,
                   TEXT("Failed to get the user's desktop directory path!"));
        }

        PathString = StringCast<TCHAR>(PathBuffer).Get();
#endif  /* defined ( __linux__ ) */
    } break;

    case EGSystemDirectory::UserGameData:
    {
#if defined ( __linux__ )
        PathString = GSystemImpl::GetSystemDirectoryPath(
                    EGSystemDirectory::UserHome);
        if (PathString.EndsWith(GSystemImpl::GetDirectorySeparatorChar(),
                                ESearchCase::IgnoreCase))
        {
            PathString = PathString.LeftChop(PathString.Len() - 2);
        }

        PathString += GSystemImpl::GetDirectorySeparatorChar()
                + FString(TEXT(".local"))
                + GSystemImpl::GetDirectorySeparatorChar()
                + FString(TEXT("share"))
                + GSystemImpl::GetDirectorySeparatorChar()
                + GBuildInfoImpl::GetProductCompanyName()
                + GSystemImpl::GetDirectorySeparatorChar()
                + GBuildInfoImpl::GetProductName();
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        PathString = GSystemImpl::GetSystemDirectoryPath(
                    EGSystemDirectory::UserDocuments);
        if (PathString.EndsWith(GSystemImpl::GetDirectorySeparatorChar(),
                                ESearchCase::IgnoreCase))
        {
            PathString = PathString.LeftChop(PathString.Len() - 2);
        }

        PathString += GSystemImpl::GetDirectorySeparatorChar()
                + FString(StringCast<TCHAR>(
                              GOD_WINDOWS_MY_GAMES_DIRECTORY_NAME).Get())
                + GSystemImpl::GetDirectorySeparatorChar()
                + GBuildInfoImpl::GetProductCompanyName()
                + GSystemImpl::GetDirectorySeparatorChar()
                + GBuildInfoImpl::GetProductName();
#endif  /* defined ( __linux__ ) */
    } break;

    case EGSystemDirectory::UserHome:
    {
#if defined ( __linux__ )
        const char *HomeDirectory = nullptr;
        if ((HomeDirectory = getenv("HOME")) == nullptr)
        {
            struct passwd *pwd = getpwuid(getuid());
            if (pwd)
            {
                HomeDirectory = pwd->pw_dir;
            }
            else
            {
                checkf(false,
                       TEXT("Failed to get user's home directory path!"));
            }
        }
        else
        {
            /// FIXME
            /// THIS CRASHES THE ENGINE AT THE GAME'S INITILIZATION STAGE
            ///checkf(false,
            ///       TEXT("FATAL: failed to get the user's home directory path!"));
        }

        PathString = StringCast<TCHAR>(HomeDirectory).Get();
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        char PathBuffer[MAX_PATH];
        HRESULT Result = SHGetFolderPathA(
                    NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, PathBuffer);

        if (Result != S_OK) {
            MessageBoxA(0,
                        fmt::format("FATAL: error code {0}", Result).c_str(),
                        "IO Error", MB_OK);
            checkf(false,
                   TEXT("FATAL: failed to get the user's home directory path!"));
        }

        PathString = StringCast<TCHAR>(PathBuffer).Get();
#endif  /* defined ( __linux__ ) */
    } break;

    }

    if (PathString.EndsWith(GSystemImpl::GetDirectorySeparatorChar(),
                            ESearchCase::IgnoreCase))
    {
        PathString = PathString.LeftChop(PathString.Len() - 2);
    }

    Path = boost::filesystem::system_complete(
                boost::filesystem::path(
                    StringCast<ANSICHAR>(*PathString).Get()));

    return FString(StringCast<TCHAR>(Path.string().c_str()).Get());
}
