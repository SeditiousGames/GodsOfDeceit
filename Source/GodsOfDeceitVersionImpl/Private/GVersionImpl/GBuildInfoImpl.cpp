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
 * Provides low-level implementation for product's build information such
 * as version, copyright, etc.
 */


#include "GBuildInfoImpl.h"

#include <exception>
#include <string>
#include <sstream>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <boost/exception/diagnostic_information.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

THIRD_PARTY_INCLUDES_START
#include <cereal/access.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/details/helpers.hpp>
#include <cereal/types/common.hpp>
#include <cereal/types/string.hpp>
THIRD_PARTY_INCLUDES_END

#include <GHacks/GInclude_Windows.h>

#define     BUILD_INFO_SERIALIZATION_ERROR_DIALOG_TITLE                 "Serialization Error"
#define     BUILD_INFO_UNKNOWN_SERIALIZATION_ERROR_MESSAGE              "GBuildInfoImpl: unknown serialization error!"

struct BuildInfo
{
public:
    std::string ProductCompanyName;
    std::string ProductName;
    std::string ProductInternalName;
    std::string ProductDescription;
    std::string ProductCopyrightNotice;
    uint8 ProductMajorVersion;
    uint8 ProductMinorVersion;
    uint8 ProductPatchVersion;
    std::string ProductBranchName;
    std::string ProductShortRevisionHash;
    std::string ProductVersion;
    std::string ProductRevision;
    std::string ProductBuildHost;
    std::string ProductBuildDate;
    std::string ProductBuildTime;

public:
    BuildInfo()
        : ProductCompanyName(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductCompanyName()).Get()),
          ProductName(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductName()).Get()),
          ProductInternalName(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductInternalName()).Get()),
          ProductDescription(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductDescription()).Get()),
          ProductCopyrightNotice(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductCopyrightNotice()).Get()),
          ProductMajorVersion(GBuildInfoImpl::GetProductVersionNumbers().Major),
          ProductMinorVersion(GBuildInfoImpl::GetProductVersionNumbers().Minor),
          ProductPatchVersion(GBuildInfoImpl::GetProductVersionNumbers().Patch),
          ProductShortRevisionHash(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductShortRevisionHash()).Get()),
          ProductVersion(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductVersion()).Get()),
          ProductRevision(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductRevision()).Get()),
          ProductBuildHost(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductBuildHost()).Get()),
          ProductBuildDate(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductBuildDate()).Get()),
          ProductBuildTime(StringCast<ANSICHAR>(*GBuildInfoImpl::GetProductBuildTime()).Get())
    {

    }

private:
    friend class cereal::access;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(ProductCompanyName),
                CEREAL_NVP(ProductName),
                CEREAL_NVP(ProductInternalName),
                CEREAL_NVP(ProductDescription),
                CEREAL_NVP(ProductCopyrightNotice),
                CEREAL_NVP(ProductMajorVersion),
                CEREAL_NVP(ProductMinorVersion),
                CEREAL_NVP(ProductPatchVersion),
                CEREAL_NVP(ProductShortRevisionHash),
                CEREAL_NVP(ProductVersion),
                CEREAL_NVP(ProductRevision),
                CEREAL_NVP(ProductBuildHost),
                CEREAL_NVP(ProductBuildDate),
                CEREAL_NVP(ProductBuildTime)
                );
    }
};

bool GBuildInfoImpl::ToJson(FString& Out_Json, const bool bPretty)
{
    static FString Json;

    if (!Out_Json.IsEmpty()) {
        Out_Json.Empty();
    }

    try
    {
        if (Json.IsEmpty())
        {
            BuildInfo BuildInformation;

            std::stringstream StringStream;

            /// NOTE
            /// According to http://uscilab.github.io/cereal/quickstart.html
            /// The curly braces are mandatory!
            /// "Archives are designed to be used in an RAII manner
            /// and are guaranteed to flush their contents only
            /// on destruction..."
            {
                cereal::JSONOutputArchive archive(StringStream);
                archive(BuildInformation);
            }

            boost::property_tree::ptree PropertyTree;
            boost::property_tree::read_json(StringStream, PropertyTree);

            if (PropertyTree.get_child_optional("value0"))
            {
                PropertyTree.add_child(
                            "BuildInformation",
                            PropertyTree.get_child("value0"));
                PropertyTree.erase("value0");
            }

            /// NOTE
            /// Clear StringStream before any re-use
            StringStream.str(std::string());
            StringStream.clear();

            boost::property_tree::write_json(
                        StringStream, PropertyTree, bPretty);

            Json.Append(StringCast<TCHAR>(StringStream.str().c_str()).Get(),
                            StringStream.str().size());
            Json.TrimToNullTerminator();
        }

        Out_Json = Json.GetCharArray().GetData();

        return true;
    }

    catch (const cereal::Exception& ex)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, boost::diagnostic_information(ex).c_str(),
                    BUILD_INFO_SERIALIZATION_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */

        checkf(false, TEXT("%s"),
               UTF8_TO_TCHAR(boost::diagnostic_information(ex).c_str()));
    }

    catch (const boost::exception& ex)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, boost::diagnostic_information(ex).c_str(),
                    BUILD_INFO_SERIALIZATION_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */

        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(
                   boost::diagnostic_information(ex).c_str()).Get());
    }

    catch (const std::exception& ex)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, ex.what(),
                    BUILD_INFO_SERIALIZATION_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */

        checkf(false, TEXT("%s"), StringCast<TCHAR>(ex.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, BUILD_INFO_UNKNOWN_SERIALIZATION_ERROR_MESSAGE,
                    BUILD_INFO_SERIALIZATION_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */

        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(
                   BUILD_INFO_UNKNOWN_SERIALIZATION_ERROR_MESSAGE).Get());
    }

    return false;
}
