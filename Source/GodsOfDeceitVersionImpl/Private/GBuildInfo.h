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
 * Provides low-level implementation for product's build information such
 * as version, copyright, etc.
 */


#pragma once

#include <cstdio>
#include <ctime>

#include <boost/preprocessor/stringize.hpp>

#include <Containers/StringConv.h>
#include <Containers/UnrealString.h>

class GBuildInfo
{
public:
    static FORCEINLINE const TCHAR* GetProductCompanyName()
    {
        static const FString ProductCompanyName(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_COMPANY_NAME).Get());

        return *ProductCompanyName;
    }

    static FORCEINLINE const TCHAR* GetProductName()
    {
        static const FString ProductName(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_NAME).Get());

        return *ProductName;
    }

    static FORCEINLINE const TCHAR* GetProductInternalName()
    {
        static const FString ProductInternalName(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_INTERNAL_NAME).Get());

        return *ProductInternalName;
    }

    static FORCEINLINE const TCHAR* GetProductDescription()
    {
        static const FString ProductDescription(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_DESCRIPTION).Get());

        return *ProductDescription;
    }

    static FORCEINLINE const TCHAR* GetProductCopyrightNotice()
    {
        static FString ProductCopyrightNotice;

        if (ProductCopyrightNotice == TEXT(""))
        {
            int Year;
            char Month[3];
            int Day;

#if !defined ( _WIN32 ) && !defined ( _WIN64 )
            sscanf(StringCast<ANSICHAR>(GBuildInfo::GetProductBuildDate()).Get(),
                   "%s %d %d",
                   Month, &Day, &Year);
#else
            sscanf_s(StringCast<ANSICHAR>(GBuildInfo::GetProductBuildDate()).Get(),
                     "%s %d %d",
                     Month, static_cast<unsigned int>(sizeof(Month)),
                     &Day, &Year);
#endif  /* !defined ( _WIN32 ) && !defined ( _WIN64 ) */

            ProductCopyrightNotice = FString::Printf(
                        TEXT("(C) %d %s. All Rights Reserved."),
                        Year,
                        StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_COMPANY_NAME).Get()
                        );
        }

        return *ProductCopyrightNotice;
    }

    static FORCEINLINE const uint8 GetProductMajorVersion()
    {
        static const uint8 ProductMajorVersion =
                static_cast<uint8>(GOD_BUILD_INFO_PRODUCT_MAJOR_VERSION);

        return ProductMajorVersion;
    }

    static FORCEINLINE const uint8 GetProductMinorVersion()
    {
        static const uint8 ProductMinorVersion =
                    static_cast<uint8>(GOD_BUILD_INFO_PRODUCT_MINOR_VERSION);

        return ProductMinorVersion;
    }

    static FORCEINLINE const uint8 GetProductPatchVersion()
    {
        static const uint8 ProductPatchVersion =
                    static_cast<uint8>(GOD_BUILD_INFO_PRODUCT_PATCH_VERSION);

        return ProductPatchVersion;
    }

    static FORCEINLINE const TCHAR* GetProductBranchName()
    {
        static const FString ProductBranchName(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_BRANCH_NAME).Get());

        return *ProductBranchName;
    }

    static FORCEINLINE const TCHAR* GetProductShortRevisionHash()
    {
        static const FString ProductShortRevisionHash(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_SHORT_REVISION_HASH).Get());

        return *ProductShortRevisionHash;
    }

    static FORCEINLINE const TCHAR* GetProductVersion()
    {
        static const FString ProductVersion(
                    StringCast<TCHAR>(
                        BOOST_PP_STRINGIZE(GOD_BUILD_INFO_PRODUCT_MAJOR_VERSION)
                        "."
                        BOOST_PP_STRINGIZE(GOD_BUILD_INFO_PRODUCT_MINOR_VERSION)
                        "."
                        BOOST_PP_STRINGIZE(GOD_BUILD_INFO_PRODUCT_PATCH_VERSION)).Get());

        return *ProductVersion;
    }

    static FORCEINLINE const TCHAR* GetProductRevision()
    {
        static const FString ProductRevision(
                    StringCast<TCHAR>(
                        GOD_BUILD_INFO_PRODUCT_BRANCH_NAME
                        "-"
                        GOD_BUILD_INFO_PRODUCT_SHORT_REVISION_HASH).Get());

        return *ProductRevision;
    }

    static FORCEINLINE const TCHAR* GetProductBuildDate()
    {
        static const FString ProductBuildDate(StringCast<TCHAR>(__DATE__).Get());

        return *ProductBuildDate;
    }

    static FORCEINLINE const TCHAR* GetProductBuildTime()
    {
        static const FString ProductBuildTime(StringCast<TCHAR>(__TIME__).Get());

        return *ProductBuildTime;
    }

    static FORCEINLINE const TCHAR* GetProductBuildHost()
    {
        static const FString ProductBuildHost(
                    StringCast<TCHAR>(GOD_BUILD_INFO_PRODUCT_BUILD_HOST).Get());

        return *ProductBuildHost;
    }
};
