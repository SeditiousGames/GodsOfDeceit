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
 * Copyright (c) 2018 Khavaran67
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
 * Provides an abstraction layer on top of platform-specific API.
 */


#include <GPlatform/GSystem.h>

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

#include <GPlatform/GWindows.h>

FString GSystem::GetExecutablePath()
{
    boost::filesystem::path path(
                boost::filesystem::initial_path<boost::filesystem::path>());

#if defined ( __linux__ )
    char exePathBuffer[PATH_MAX];
    std::memset(exePathBuffer, 0, sizeof(exePathBuffer));

    /// NOTE
    /// /proc/self/exe yealds the same result
    char procPathBuffer[PATH_MAX];
    pid_t pid = getpid();
    std::sprintf(procPathBuffer, "/proc/%d/exe", pid);

    ssize_t count = readlink(procPathBuffer, exePathBuffer, PATH_MAX);
    bool bResult = (count > 0);

    checkf(bResult, TEXT("FATAL: failed to get current directory path!"));

    FString pathString(UTF8_TO_TCHAR(exePathBuffer));
#elif defined ( _WIN32 ) || defined ( _WIN64 )
    char pathBuffer[MAX_PATH];
    DWORD result = GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
    FString pathString(UTF8_TO_TCHAR(pathBuffer));

    if (result == ERROR_SUCCESS) {
        MessageBoxA(0, fmt::format("FATAL: failed to get the current directory path! Error code: {0}",
                                   result).c_str(),
                    "IO Error", MB_OK);
        checkf(false, TEXT("Failed to get the current directory path!"));
    }
#else
    static_assert(false, "FATAL: unsuported platform!");
#endif  /* defined ( __linux__ ) */

    if (pathString.EndsWith(GSystem::GetDirectorySeparatorChar(),
                            ESearchCase::IgnoreCase)) {
        pathString = pathString.LeftChop(pathString.Len() - 2);
    }

    path = boost::filesystem::system_complete(
                boost::filesystem::path(TCHAR_TO_UTF8(*pathString)));

    return FString(path.string().c_str());
}

FString GSystem::GetCurrentPath()
{
    boost::filesystem::path path(
                boost::filesystem::system_complete(
                    boost::filesystem::current_path()));
    return FString(path.string().c_str());
}

FString GSystem::GetSystemDirectoryPath(const EGSystemDirectory directory)
{
    boost::filesystem::path path;
    FString pathString;

    switch (directory) {

    case EGSystemDirectory::UserDesktop: {
#if defined ( __linux__ )
        pathString = GSystem::GetSystemDirectoryPath(EGSystemDirectory::UserHome);
        if (pathString.EndsWith(GSystem::GetDirectorySeparatorChar(), ESearchCase::IgnoreCase)) {
            pathString = pathString.LeftChop(pathString.Len() - 2);
        }

        pathString += GSystem::GetDirectorySeparatorChar()
                + TEXT("Desktop");
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        char pathBuffer[MAX_PATH];
        HRESULT result = SHGetFolderPathA(NULL, CSIDL_DESKTOP, NULL,
                                          SHGFP_TYPE_CURRENT, pathBuffer);

        if (result != S_OK) {
            MessageBoxA(0, fmt::format("Error code: {0}", result).c_str(),
                        "IO Error", MB_OK);
            checkf(false, TEXT("FATAL: failed to get the user's desktop directory path!"));
        }

        pathString = UTF8_TO_TCHAR(pathBuffer);
#endif  /* defined ( __linux__ ) */
    } break;

    case EGSystemDirectory::UserDocuments: {
#if defined ( __linux__ )
        pathString = GSystem::GetSystemDirectoryPath(EGSystemDirectory::UserHome);
        if (pathString.EndsWith(GSystem::GetDirectorySeparatorChar(), ESearchCase::IgnoreCase)) {
            pathString = pathString.LeftChop(pathString.Len() - 2);
        }

        pathString += GSystem::GetDirectorySeparatorChar()
                + TEXT("Documents");
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        char pathBuffer[MAX_PATH];
        HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL,
                                          SHGFP_TYPE_CURRENT, pathBuffer);

        if (result != S_OK) {
            MessageBoxA(0, fmt::format("FATAL: error code: {0}", result).c_str(),
                        "IO Error", MB_OK);
            checkf(false, TEXT("Failed to get the user's desktop directory path!"));
        }

        pathString = UTF8_TO_TCHAR(pathBuffer);
#endif  /* defined ( __linux__ ) */
    } break;

    case EGSystemDirectory::UserGameData: {
#if defined ( __linux__ )
        pathString = GSystem::GetSystemDirectoryPath(EGSystemDirectory::UserHome);
        if (pathString.EndsWith(GSystem::GetDirectorySeparatorChar(), ESearchCase::IgnoreCase)) {
            pathString = pathString.LeftChop(pathString.Len() - 2);
        }

//        pathString += GSystem::GetDirectorySeparatorChar()
//                + FString(TEXT(".local"))
//                + GSystem::GetDirectorySeparatorChar()
//                + FString(TEXT("share"))
//                + GSystem::GetDirectorySeparatorChar()
//                + GVersionInfo::CompanyName()
//                + GSystem::GetDirectorySeparatorChar()
//                + GVersionInfo::ProductName();
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        pathString = GSystem::GetSystemDirectoryPath(EGSystemDirectory::UserDocuments);
        if (pathString.EndsWith(GSystem::GetDirectorySeparatorChar(), ESearchCase::IgnoreCase)) {
            pathString = pathString.LeftChop(pathString.Len() - 2);
        }

        pathString += GSystem::GetDirectorySeparatorChar()
                + FString(UTF8_TO_TCHAR(G_WINDOWS_MY_GAMES_DIRECTORY_NAME))
                + GSystem::GetDirectorySeparatorChar()
                + GVersionInfo::CompanyName()
                + GSystem::GetDirectorySeparatorChar()
                + GVersionInfo::ProductName();
#endif  /* defined ( __linux__ ) */
    } break;

    case EGSystemDirectory::UserHome: {
#if defined ( __linux__ )
        const char *homeDirectory = nullptr;
        if ((homeDirectory = getenv("HOME")) == NULL) {
            struct passwd *pwd = getpwuid(getuid());
            if (pwd) {
                homeDirectory = pwd->pw_dir;
            } else {
                checkf(false, TEXT("Failed to get user's home directory path!"));
            }
        } else {
            /// NOTE
            /// THIS CRASHES THE ENGINE AT THE GAME'S INITILIZATION
            ///checkf(false, TEXT("FATAL: failed to get the user's home directory path!"));
        }

        pathString = UTF8_TO_TCHAR(homeDirectory);
#elif defined ( _WIN32 ) || defined ( _WIN64 )
        char pathBuffer[MAX_PATH];
        HRESULT result = SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL,
                                          SHGFP_TYPE_CURRENT, pathBuffer);

        if (result != S_OK) {
            MessageBoxA(0, fmt::format("FATAL: error code {0}", result).c_str(),
                        "IO Error", MB_OK);
            checkf(false, TEXT("FATAL: failed to get the user's home directory path!"));
        }

        pathString = UTF8_TO_TCHAR(pathBuffer);
#endif  /* defined ( __linux__ ) */
    } break;

    }

    if (pathString.EndsWith(GSystem::GetDirectorySeparatorChar(),
                            ESearchCase::IgnoreCase)) {
        pathString = pathString.LeftChop(pathString.Len() - 2);
    }

    path = boost::filesystem::system_complete(
                boost::filesystem::path(TCHAR_TO_UTF8(*pathString)));

    return FString(path.string().c_str());
}
