/**
 * @file
 * @author  Mamadou Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mamadou Babaei
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
 * Provides low-level implementation for product's build information such
 * as version, copyright, etc.
 */


#pragma once

#include <cstdio>
#include <ctime>

#include <Containers/StringConv.h>
#include <Containers/UnrealString.h>
#include <CoreTypes.h>

#include <GHacks/GUndef_check.h>

THIRD_PARTY_INCLUDES_START
#include <boost/preprocessor/stringize.hpp>
THIRD_PARTY_INCLUDES_END

#include <GHacks/GRestore_check.h>

#include <GTypes/GVersionTypes.h>

class GODSOFDECEITVERSIONIMPL_API GBuildInfoImpl
{
public:
    static FORCEINLINE const FString& GetProductCompanyName()
    {
        static const FString ProductCompanyName(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_COMPANY_NAME).Get());

        return ProductCompanyName;
    }

    static FORCEINLINE const FString& GetProductName()
    {
        static const FString ProductName(
                    StringCast<WIDECHAR>(GOD_BUILD_INFO_PRODUCT_NAME).Get());

        return ProductName;
    }

    static FORCEINLINE const FString& GetProductInternalName()
    {
        static const FString ProductInternalName(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_INTERNAL_NAME).Get());

        return ProductInternalName;
    }

    static FORCEINLINE const FString& GetProductDescription()
    {
        static const FString ProductDescription(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_DESCRIPTION).Get());

        return ProductDescription;
    }

    static FORCEINLINE const FString& GetProductCopyrightHolder()
    {
        static const FString ProductCopyrightHolder(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_COPYRIGHT_HOLDER).Get());

        return ProductCopyrightHolder;
    }

    static FORCEINLINE const FString& GetProductCopyrightNotice()
    {
        static FString ProductCopyrightNotice;

        if (ProductCopyrightNotice.IsEmpty())
        {
            int Year;
            char Month[3];
            int Day;

#if !defined ( _WIN32 ) && !defined ( _WIN64 )
            sscanf(StringCast<ANSICHAR>(
                       *GBuildInfoImpl::GetProductBuildDate()).Get(),
                   "%s %d %d",
                   Month, &Day, &Year);
#else
            sscanf_s(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductBuildDate()).Get(),
                     "%s %d %d",
                     Month, static_cast<unsigned int>(sizeof(Month)),
                     &Day, &Year);
#endif  /* !defined ( _WIN32 ) && !defined ( _WIN64 ) */

            ProductCopyrightNotice = FString::Printf(
                        TEXT("(C) %d %s. All Rights Reserved."),
                        Year,
                        StringCast<WIDECHAR>(
                            GOD_BUILD_INFO_PRODUCT_COPYRIGHT_HOLDER).Get()
                        );
        }

        return ProductCopyrightNotice;
    }

    static FORCEINLINE const FGProductVersionNumbers& GetProductVersionNumbers()
    {
        static const FGProductVersionNumbers ProductVersionNumbers
        {
            static_cast<uint8>(GOD_BUILD_INFO_PRODUCT_MAJOR_VERSION),
            static_cast<uint8>(GOD_BUILD_INFO_PRODUCT_MINOR_VERSION),
            static_cast<uint8>(GOD_BUILD_INFO_PRODUCT_PATCH_VERSION)
        };

        return ProductVersionNumbers;
    }

    static FORCEINLINE const FString& GetProductBranchName()
    {
        static const FString ProductBranchName(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_BRANCH_NAME).Get());

        return ProductBranchName;
    }

    static FORCEINLINE const FString& GetProductShortRevisionHash()
    {
        static const FString ProductShortRevisionHash(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_SHORT_REVISION_HASH).Get());

        return ProductShortRevisionHash;
    }

    static FORCEINLINE const FString& GetProductVersion()
    {
        static const FString ProductVersion(
                    StringCast<WIDECHAR>(
                        BOOST_PP_STRINGIZE(GOD_BUILD_INFO_PRODUCT_MAJOR_VERSION)
                        "."
                        BOOST_PP_STRINGIZE(GOD_BUILD_INFO_PRODUCT_MINOR_VERSION)
                        "."
                        BOOST_PP_STRINGIZE(GOD_BUILD_INFO_PRODUCT_PATCH_VERSION)
                        ).Get());

        return ProductVersion;
    }

    static FORCEINLINE const FString& GetProductRevision()
    {
        static const FString ProductRevision(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_BRANCH_NAME
                        "-"
                        GOD_BUILD_INFO_PRODUCT_SHORT_REVISION_HASH).Get());

        return ProductRevision;
    }

    static FORCEINLINE const FString& GetProductBuildDate()
    {
        static const FString ProductBuildDate(
                    StringCast<WIDECHAR>(__DATE__).Get());

        return ProductBuildDate;
    }

    static FORCEINLINE const FString& GetProductBuildTime()
    {
        static const FString ProductBuildTime(
                    StringCast<WIDECHAR>(__TIME__).Get());

        return ProductBuildTime;
    }

    static FORCEINLINE const FString& GetProductBuildHost()
    {
        static const FString ProductBuildHost(
                    StringCast<WIDECHAR>(
                        GOD_BUILD_INFO_PRODUCT_BUILD_HOST).Get());

        return ProductBuildHost;
    }

    static FString ToJson(const bool bPretty = false);
};
