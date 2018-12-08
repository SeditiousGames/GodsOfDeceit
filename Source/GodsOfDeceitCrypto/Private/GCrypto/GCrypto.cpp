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
 * Provides a high level cryptography API.
 */

#include "GCrypto.h"

#include <utility>

#include <GCryptoImpl/GExportedFunctions.h>
#include <GInterop/GIC_FString.h>
#include <GInterop/GIC_GCryptoBuffer.h>
#include <GInterop/GIC_std_string.h>

bool GCrypto::BytesArrayToString(const GCryptoByte* const Array,
                                 const uint64 Length,
                                 FString& Out_String,
                                 FString& Out_Error)
{
    GIC_FString OutStringInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed = GCrypto_BytesArrayToString_WithErrorInfo(
                Array, Length,
                &OutStringInteropContainer, &OutErrorInteropContainer);

    Out_String = std::move(OutStringInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::BytesArrayToString(const GCryptoByte* const Array,
                                 const uint64 Length,
                                 FString& Out_String)
{
    GIC_FString OutStringInteropContainer;

    bool bSucceed = GCrypto_BytesArrayToString(
                Array, Length,
                &OutStringInteropContainer);

    Out_String = std::move(OutStringInteropContainer.String);

    return bSucceed;
}

FString GCrypto::BytesArrayToString(const GCryptoByte* const Array,
                                    const uint64 Length)
{
    GIC_FString OutStringInteropContainer;

    (void)GCrypto_BytesArrayToString(
                Array, Length,
                &OutStringInteropContainer);

    return OutStringInteropContainer.String;
}


bool GCrypto::HexStringToString(const FString& HexString,
                                FString& Out_String,
                                FString& Out_Error)
{
    const GIC_FString HexStringInteropContainer
    {
        HexString
    };

    GIC_FString OutStringInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed = GCrypto_HexStringToString_WithErrorInfo(
                &HexStringInteropContainer, &OutStringInteropContainer,
                &OutErrorInteropContainer);

    Out_String = std::move(OutStringInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::HexStringToString(const FString& HexString,
                                FString& Out_String)
{
    const GIC_FString HexStringInteropContainer
    {
        HexString
    };

    GIC_FString OutStringInteropContainer;

    bool bSucceed = GCrypto_HexStringToString(
                &HexStringInteropContainer, &OutStringInteropContainer);

    Out_String = std::move(OutStringInteropContainer.String);

    return bSucceed;
}

FString GCrypto::HexStringToString(const FString& HexString)
{
    const GIC_FString HexStringInteropContainer
    {
        HexString
    };

    GIC_FString OutStringInteropContainer;

    (void)GCrypto_HexStringToString(
                &HexStringInteropContainer,
                &OutStringInteropContainer);

    return OutStringInteropContainer.String;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           std::string& Out_Decoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           GCryptoBuffer& Out_Decoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           FString& Out_Decoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoBuffer& EncodedBuffer,
                           FString& Out_Decoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Decode(const FString& EncodedBuffer,
                           FString& Out_Decoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           std::string& Out_Decoded)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           GCryptoBuffer& Out_Decoded)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           FString& Out_Decoded)
{
    return false;
}

bool GCrypto::Base64Decode(const GCryptoBuffer& EncodedBuffer,
                           FString& Out_Decoded)
{
    return false;
}

bool GCrypto::Base64Decode(const FString& EncodedBuffer,
                           FString& Out_Decoded)
{
    return false;
}

bool GCrypto::Base64Encode(const GCryptoByte* const RawBuffer,
                           const uint64 RawBufferSize,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Encode(const GCryptoBuffer& RawBuffer,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Encode(const std::string& RawBuffer,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Encode(const FString& RawBuffer,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    return false;
}

bool GCrypto::Base64Encode(const GCryptoByte* const RawBuffer,
                           const uint64 RawBufferSize,
                           FString& Out_Encoded)
{
    return false;
}

bool GCrypto::Base64Encode(const GCryptoBuffer& RawBuffer,
                           FString& Out_Encoded)
{
    return false;
}

bool GCrypto::Base64Encode(const std::string& RawBuffer,
                           FString& Out_Encoded)
{
    return false;
}

bool GCrypto::Base64Encode(const FString& RawBuffer,
                           FString& Out_Encoded)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoByte* const PlainBuffer, uint64 PlainBufferSize,
                   FString& Out_MAC, FString& Out_Error)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                   FString& Out_Error)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const std::string& PlainString, FString& Out_MAC,
                   FString& Out_Error)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const FString& PlainString, FString& Out_MAC,
                   FString& Out_Error)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoByte* const PlainBuffer, uint64 PlainBufferSize,
                   FString& Out_MAC)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoBuffer& PlainBuffer, FString& Out_MAC)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const std::string& PlainString, FString& Out_MAC)
{
    return false;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const FString& PlainString, FString& Out_MAC)
{
    return false;
}

GCrypto::GCrypto(const GCryptoByte* const SignKey, const uint64 SignKeySize)
{

}

GCrypto::GCrypto(const GCryptoBuffer& SignKey)
{

}

GCrypto::~GCrypto()
{

}

bool GCrypto::Sign(
        const GCryptoByte* const PlainBuffer, const uint64 PlainBufferSize,
        FString& Out_MAC, FString& Out_Error) const
{
    return false;
}

bool GCrypto::Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                   FString& Out_Error) const
{
    return false;
}

bool GCrypto::Sign(const std::string& PlainString, FString& Out_MAC,
                   FString& Out_Error) const
{
    return false;
}

bool GCrypto::Sign(const FString& PlainString, FString& Out_MAC,
                   FString& Out_Error) const
{
    return false;
}

bool GCrypto::Sign(
        const GCryptoByte* const PlainBuffer, const uint64 PlainBufferSize,
        FString& Out_MAC) const
{
    return false;
}

bool GCrypto::Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC) const
{
    return false;
}

bool GCrypto::Sign(const std::string& PlainString, FString& Out_MAC) const
{
    return false;
}

bool GCrypto::Sign(const FString& PlainString, FString& Out_MAC) const
{
    return false;
}
