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
 * Provides a thin C-compatible wrapper around the version module's low-level
 * implementation.
 */


#pragma once

/// NOTE
/// Defines a C++ like static_assert
#ifdef __cplusplus
#include <cassert>
#else
#include <assert.h>
#endif  /* __cplusplus */

/// NOTE
/// Contains __bool_true_false_are_defined macro that can be used in order to
/// check whether boolean type is supported by the compiler or not.
#ifdef __cplusplus
#include <cstdbool>
#else
#include <stdbool.h>
#endif  /* __cplusplus */

#include <CoreTypes.h>

#include <GTypes/GVersionTypes.h>

/// NOTE
/// Check at compile time whether the C compiler has support for bool, true,
/// and false macros.
static_assert(__bool_true_false_are_defined,
              "Error: bool, true, and false are not defined!");

/// NOTE
/// If C++ is used switch to C mode in order to prevent C++'s name mangling of
/// method names.
#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

#if defined ( GOD_BUILDING_VERSION_IMPL_MODULE )

DLLEXPORT void BuildInfo_GetProductCompanyName(void* Out_Name);
DLLEXPORT void BuildInfo_GetProductName(void* Out_Name);
DLLEXPORT void BuildInfo_GetProductInternalName(void* Out_Name);
DLLEXPORT void BuildInfo_GetProductDescription(void* Out_Description);
DLLEXPORT void BuildInfo_GetProductCopyrightHolder(void* Out_Notice);
DLLEXPORT void BuildInfo_GetProductCopyrightNotice(void* Out_Notice);
DLLEXPORT void BuildInfo_GetProductVersionNumbers(
        FGProductVersionNumbers* Out_Numbers);
DLLEXPORT void BuildInfo_GetProductBranchName(void* Out_Name);
DLLEXPORT void BuildInfo_GetProductShortRevisionHash(void* Out_Hash);
DLLEXPORT void BuildInfo_GetProductVersion(void* Out_Version);
DLLEXPORT void BuildInfo_GetProductRevision(void* Out_Revision);
DLLEXPORT void BuildInfo_GetProductBuildHost(void* Out_Host);
DLLEXPORT void BuildInfo_GetProductBuildDate(void* Out_Date);
DLLEXPORT void BuildInfo_GetProductBuildTime(void* Out_Time);

DLLEXPORT bool BuildInfo_GetProductBuildInfoAsJson(
        void* Out_Json, const bool bPretty);

#else

DLLIMPORT void BuildInfo_GetProductCompanyName(void* Out_Name);
DLLIMPORT void BuildInfo_GetProductName(void* Out_Name);
DLLIMPORT void BuildInfo_GetProductInternalName(void* Out_Name);
DLLIMPORT void BuildInfo_GetProductDescription(void* Out_Description);
DLLIMPORT void BuildInfo_GetProductCopyrightHolder(void* Out_Notice);
DLLIMPORT void BuildInfo_GetProductCopyrightNotice(void* Out_Notice);
DLLIMPORT void BuildInfo_GetProductVersionNumbers(
        FGProductVersionNumbers* Out_Numbers);
DLLIMPORT void BuildInfo_GetProductBranchName(void* Out_Name);
DLLIMPORT void BuildInfo_GetProductShortRevisionHash(void* Out_Hash);
DLLIMPORT void BuildInfo_GetProductVersion(void* Out_Version);
DLLIMPORT void BuildInfo_GetProductRevision(void* Out_Revision);
DLLIMPORT void BuildInfo_GetProductBuildHost(void* Out_Host);
DLLIMPORT void BuildInfo_GetProductBuildDate(void* Out_Date);
DLLIMPORT void BuildInfo_GetProductBuildTime(void* Out_Time);

DLLIMPORT bool BuildInfo_GetProductBuildInfoAsJson(
        void* Out_Json, const bool bPretty);

#endif  /* defined ( GOD_BUILDING_VERSION_IMPL_MODULE ) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
