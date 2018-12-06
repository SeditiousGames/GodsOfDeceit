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
 * Provides product's build information such as version, copyright, etc.
 */


#include "GBuildInfo.h"

#include <GInterop/GIC_FString.h>
#include <GVersionImpl/GExportedFunctions.h>

FString GBuildInfo::GetProductCompanyName()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductCompanyName(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductName()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductName(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductInternalName()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductInternalName(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductDescription()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductDescription(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductCopyrightHolder()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductCopyrightHolder(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductCopyrightNotice()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductCopyrightNotice(&InteropContainer);

    return InteropContainer.String;
}

FGProductVersionNumbers GBuildInfo::GetProductVersionNumbers()
{
    FGProductVersionNumbers ProductVersionNumbers;

    BuildInfo_GetProductVersionNumbers(&ProductVersionNumbers);

    return ProductVersionNumbers;
}

FString GBuildInfo::GetProductBranchName()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductBranchName(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductShortRevisionHash()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductShortRevisionHash(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductVersion()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductVersion(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductRevision()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductRevision(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductBuildHost()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductBuildHost(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductBuildDate()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductBuildDate(&InteropContainer);

    return InteropContainer.String;
}

FString GBuildInfo::GetProductBuildTime()
{
    GIC_FString InteropContainer;

    BuildInfo_GetProductBuildTime(&InteropContainer);

    return InteropContainer.String;
}

bool GBuildInfo::ToJson(FString& Out_Json, const bool bPretty)
{
    GIC_FString InteropContainer;

    bool bSucceed = BuildInfo_GetProductBuildInfoAsJson(
                &InteropContainer, bPretty);

    Out_Json = std::move(InteropContainer.String);

    return bSucceed;
}
