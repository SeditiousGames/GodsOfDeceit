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


#include "GVersionImpl.h"
#include "GBuildInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

const TCHAR* GetProductCompanyName()
{
    return GBuildInfo::GetProductCompanyName();
}

const TCHAR* GetProductName()
{
    return GBuildInfo::GetProductName();
}

const TCHAR* GetProductInternalName()
{
    return GBuildInfo::GetProductInternalName();
}

const TCHAR* GetProductDescription()
{
    return GBuildInfo::GetProductDescription();
}

const TCHAR* GetProductCopyrightNotice()
{
    return GBuildInfo::GetProductCopyrightNotice();
}

const uint8 GetProductMajorVersion()
{
    return GBuildInfo::GetProductMajorVersion();
}

const uint8 GetProductMinorVersion()
{
    return GBuildInfo::GetProductMajorVersion();
}

const uint8 GetProductPatchVersion()
{
    return GBuildInfo::GetProductPatchVersion();
}

const TCHAR* GetProductBranchName()
{
    return GBuildInfo::GetProductBranchName();
}

const TCHAR* GetProductShortRevisionHash()
{
    return GBuildInfo::GetProductShortRevisionHash();
}

const TCHAR* GetProductVersion()
{
    return GBuildInfo::GetProductVersion();
}

const TCHAR* GetProductRevision()
{
    return GBuildInfo::GetProductRevision();
}

const TCHAR* GetProductBuildHost()
{
    return GBuildInfo::GetProductBuildHost();
}

const TCHAR* GetProductBuildDate()
{
    return GBuildInfo::GetProductBuildDate();
}

const TCHAR* GetProductBuildTime()
{
    return GBuildInfo::GetProductBuildTime();
}

const bool GetProductBuildInfoAsJson(
        TCHAR* Out_Json, const bool bPretty)
{
    return GBuildInfo::ToJson(Out_Json, bPretty);
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
