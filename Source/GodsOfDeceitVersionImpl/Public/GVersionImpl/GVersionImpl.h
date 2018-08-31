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
 * Provides a C-compatible wrapper around the version module's low-level
 * implementation.
 */


#pragma once

//// NOTE
/// Defines a C++ like static_assert
#include <cassert>

//// NOTE
/// Contains __bool_true_false_are_defined macro that can be used to check if
/// boolean type is supported.
#include <cstdbool>

#include <HAL/Platform.h>
#include <UObject/ObjectMacros.h>

//// NOTE
/// Check at compile time wheter C compiler has support for bool, true, and
/// false macros.
static_assert(__bool_true_false_are_defined,
              "Error: bool, true, and false are not defined!");

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

#if defined ( GOD_BUILDING_IMPL )

DLLEXPORT const TCHAR* GetProductCompanyName();
DLLEXPORT const TCHAR* GetProductName();
DLLEXPORT const TCHAR* GetProductInternalName();
DLLEXPORT const TCHAR* GetProductDescription();
DLLEXPORT const TCHAR* GetProductCopyrightNotice();
DLLEXPORT const uint8 GetProductMajorVersion();
DLLEXPORT const uint8 GetProductMinorVersion();
DLLEXPORT const uint8 GetProductPatchVersion();
DLLEXPORT const TCHAR* GetProductBranchName();
DLLEXPORT const TCHAR* GetProductShortRevisionHash();
DLLEXPORT const TCHAR* GetProductVersion();
DLLEXPORT const TCHAR* GetProductRevision();
DLLEXPORT const TCHAR* GetProductBuildHost();
DLLEXPORT const TCHAR* GetProductBuildDate();
DLLEXPORT const TCHAR* GetProductBuildTime();

DLLEXPORT const bool GetProductBuildInfoAsJson(
        TCHAR* Out_Json, const bool bPretty);

#else

DLLIMPORT const TCHAR* GetProductCompanyName();
DLLIMPORT const TCHAR* GetProductName();
DLLIMPORT const TCHAR* GetProductInternalName();
DLLIMPORT const TCHAR* GetProductDescription();
DLLIMPORT const TCHAR* GetProductCopyrightNotice();
DLLIMPORT const uint8 GetProductMajorVersion();
DLLIMPORT const uint8 GetProductMinorVersion();
DLLIMPORT const uint8 GetProductPatchVersion();
DLLIMPORT const TCHAR* GetProductBranchName();
DLLIMPORT const TCHAR* GetProductShortRevisionHash();
DLLIMPORT const TCHAR* GetProductVersion();
DLLIMPORT const TCHAR* GetProductRevision();
DLLIMPORT const TCHAR* GetProductBuildHost();
DLLIMPORT const TCHAR* GetProductBuildDate();
DLLIMPORT const TCHAR* GetProductBuildTime();

DLLIMPORT const bool GetProductBuildInfoAsJson(
        TCHAR* Out_Json, const bool bPretty);

#endif  /* defined ( GOD_BUILDING_IMPL ) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
