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
 * Provides the low-level implementation for the utils module
 */


#include "GUtilsImpl/GUtilsImpl.h"

#include <Containers/Array.h>
#include <Containers/StringConv.h>

THIRD_PARTY_INCLUDES_START
#include <fmt/format.h>
#include <fmt/ostream.h>
THIRD_PARTY_INCLUDES_END

#include <GHacks/GInclude_Windows.h>

#define     GUTILS_ERROR_DIALOG_TITLE          "Utility Error"
#define     GUTILS_UNKNOWN_ERROR_MESSAGE       "GUtils: unknown error!"

FString GUtilsImpl::CalculateBytes(const uint64 Bytes)
{
    FString Result;

    try
    {
        static const TArray<FString> Units
        {
            TEXT("EB"),
            TEXT("PB"),
            TEXT("TB"),
            TEXT("GB"),
            TEXT("MB"),
            TEXT("KB"),
            TEXT("B")
        };

        static const uint64 Exbibytes = 1024ull * 1024ull * 1024ull
                * 1024ull * 1024ull * 1024ull;

        uint64 Multiplier = Exbibytes;

        if (Bytes != 0)
        {
            for (int32 i = 0; i < Units.Num(); ++i, Multiplier /= 1024)
            {
                if (Bytes < Multiplier)
                    continue;

                if (i < Units.Num() - 1)
                {
                    if (Bytes % Multiplier == 0)
                    {
                        Result = StringCast<WIDECHAR>(
                                    fmt::format(
                                        "{}.00 {}", (Bytes / Multiplier),
                                        StringCast<ANSICHAR>(
                                            *Units[i]).Get()).c_str()).Get();
                    }
                    else
                    {
                        Result = StringCast<WIDECHAR>(
                                    fmt::format(
                                        "{:.2f} {}",
                                        (static_cast<float>(Bytes)
                                         / static_cast<float>(Multiplier)),
                                         StringCast<ANSICHAR>(
                                            *Units[i]).Get()).c_str()).Get();
                    }
                }
                else
                {
                    Result = StringCast<WIDECHAR>(
                                fmt::format(
                                    "{} {}", (Bytes / Multiplier),
                                    StringCast<ANSICHAR>(
                                        *Units[i]).Get()).c_str()).Get();
                }

                return Result;
            }
        }

        Result = TEXT("0");
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GUTILS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GUTILS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GUTILS_UNKNOWN_ERROR_MESSAGE,
                    GUTILS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GUTILS_UNKNOWN_ERROR_MESSAGE).Get());
    }

    return Result;
}
