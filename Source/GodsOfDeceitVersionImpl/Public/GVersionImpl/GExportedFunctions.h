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

DLLEXPORT void GBuildInfo_GetProductCompanyName(void* Out_Name);
DLLEXPORT void GBuildInfo_GetProductName(void* Out_Name);
DLLEXPORT void GBuildInfo_GetProductInternalName(void* Out_Name);
DLLEXPORT void GBuildInfo_GetProductDescription(void* Out_Description);
DLLEXPORT void GBuildInfo_GetProductCopyrightHolder(void* Out_Notice);
DLLEXPORT void GBuildInfo_GetProductCopyrightNotice(void* Out_Notice);
DLLEXPORT void GBuildInfo_GetProductVersionNumbers(
        FGProductVersionNumbers* Out_Numbers);
DLLEXPORT void GBuildInfo_GetProductBranchName(void* Out_Name);
DLLEXPORT void GBuildInfo_GetProductShortRevisionHash(void* Out_Hash);
DLLEXPORT void GBuildInfo_GetProductVersion(void* Out_Version);
DLLEXPORT void GBuildInfo_GetProductRevision(void* Out_Revision);
DLLEXPORT void GBuildInfo_GetProductBuildHost(void* Out_Host);
DLLEXPORT void GBuildInfo_GetProductBuildDate(void* Out_Date);
DLLEXPORT void GBuildInfo_GetProductBuildTime(void* Out_Time);

DLLEXPORT bool GBuildInfo_GetProductBuildInfoAsJson(
        void* Out_Json, const bool bPretty);

#else

DLLIMPORT void GBuildInfo_GetProductCompanyName(void* Out_Name);
DLLIMPORT void GBuildInfo_GetProductName(void* Out_Name);
DLLIMPORT void GBuildInfo_GetProductInternalName(void* Out_Name);
DLLIMPORT void GBuildInfo_GetProductDescription(void* Out_Description);
DLLIMPORT void GBuildInfo_GetProductCopyrightHolder(void* Out_Notice);
DLLIMPORT void GBuildInfo_GetProductCopyrightNotice(void* Out_Notice);
DLLIMPORT void GBuildInfo_GetProductVersionNumbers(
        FGProductVersionNumbers* Out_Numbers);
DLLIMPORT void GBuildInfo_GetProductBranchName(void* Out_Name);
DLLIMPORT void GBuildInfo_GetProductShortRevisionHash(void* Out_Hash);
DLLIMPORT void GBuildInfo_GetProductVersion(void* Out_Version);
DLLIMPORT void GBuildInfo_GetProductRevision(void* Out_Revision);
DLLIMPORT void GBuildInfo_GetProductBuildHost(void* Out_Host);
DLLIMPORT void GBuildInfo_GetProductBuildDate(void* Out_Date);
DLLIMPORT void GBuildInfo_GetProductBuildTime(void* Out_Time);

DLLIMPORT bool GBuildInfo_GetProductBuildInfoAsJson(
        void* Out_Json, const bool bPretty);

#endif  /* defined ( GOD_BUILDING_VERSION_IMPL_MODULE ) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
