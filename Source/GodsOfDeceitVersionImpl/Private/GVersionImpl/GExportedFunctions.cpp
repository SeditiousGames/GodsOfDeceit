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
 * Provides a thin C-compatible wrapper around the version module's low-level
 * implementation.
 */


#include "GVersionImpl/GExportedFunctions.h"

#include <GInterop/GIC_FString.h>

#include "GVersionImpl/GBuildInfoImpl.h"

void GBuildInfo_GetProductCompanyName(void* Out_Name)
{
    static_cast<GIC_FString*>(Out_Name)->String =
            GBuildInfoImpl::GetProductCompanyName();
}

void GBuildInfo_GetProductName(void* Out_Name)
{
    static_cast<GIC_FString*>(Out_Name)->String =
            GBuildInfoImpl::GetProductName();
}

void GBuildInfo_GetProductInternalName(void* Out_Name)
{
    static_cast<GIC_FString*>(Out_Name)->String =
            GBuildInfoImpl::GetProductInternalName();
}

void GBuildInfo_GetProductDescription(void* Out_Description)
{
    static_cast<GIC_FString*>(Out_Description)->String =
            GBuildInfoImpl::GetProductDescription();
}

void GBuildInfo_GetProductCopyrightHolder(void* Out_Notice)
{
    static_cast<GIC_FString*>(Out_Notice)->String =
            GBuildInfoImpl::GetProductCopyrightHolder();
}

void GBuildInfo_GetProductCopyrightNotice(void* Out_Notice)
{
    static_cast<GIC_FString*>(Out_Notice)->String =
            GBuildInfoImpl::GetProductCopyrightNotice();
}

void GBuildInfo_GetProductVersionNumbers(
        FGProductVersionNumbers* Out_Numbers)
{
    *Out_Numbers = GBuildInfoImpl::GetProductVersionNumbers();
}

void GBuildInfo_GetProductBranchName(void* Out_Name)
{
    static_cast<GIC_FString*>(Out_Name)->String =
            GBuildInfoImpl::GetProductBranchName();
}

void GBuildInfo_GetProductShortRevisionHash(void* Out_Hash)
{
    static_cast<GIC_FString*>(Out_Hash)->String =
            GBuildInfoImpl::GetProductShortRevisionHash();
}

void GBuildInfo_GetProductVersion(void* Out_Version)
{
    static_cast<GIC_FString*>(Out_Version)->String =
            GBuildInfoImpl::GetProductVersion();
}

void GBuildInfo_GetProductRevision(void* Out_Revision)
{
    static_cast<GIC_FString*>(Out_Revision)->String =
            GBuildInfoImpl::GetProductRevision();
}

void GBuildInfo_GetProductBuildHost(void* Out_Host)
{
    static_cast<GIC_FString*>(Out_Host)->String =
            GBuildInfoImpl::GetProductBuildHost();
}

void GBuildInfo_GetProductBuildDate(void* Out_Date)
{
    static_cast<GIC_FString*>(Out_Date)->String =
            GBuildInfoImpl::GetProductBuildDate();
}

void GBuildInfo_GetProductBuildTime(void* Out_Time)
{
    static_cast<GIC_FString*>(Out_Time)->String =
            GBuildInfoImpl::GetProductBuildTime();
}

bool GBuildInfo_GetProductBuildInfoAsJson(void* Out_Json, const bool bPretty)
{
    return GBuildInfoImpl::ToJson(static_cast<GIC_FString*>(Out_Json)->String,
                                  bPretty);
}