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
 * Provides a high level cryptography API.
 */

#include "GCrypto/GCrypto.h"

#include <utility>

#include <GCryptoImpl/GExportedFunctions.h>
#include <GInterop/GIC_FString.h>
#include <GInterop/GIC_GCryptoBuffer.h>
#include <GInterop/GIC_std_string.h>

struct GCrypto::Impl
{
public:
    GCryptoByte* SignKey;
    uint64 SignKeySize;

public:
    Impl();
    ~Impl();
};

bool GCrypto::ByteArrayToString(const GCryptoByte* const Array,
                                const uint64 Length,
                                FString& Out_String,
                                FString& Out_Error)
{
    GIC_FString OutStringInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed = GCrypto_ByteArrayToString_WithErrorInfo(
                Array, Length,
                &OutStringInteropContainer, &OutErrorInteropContainer);

    Out_String = std::move(OutStringInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::ByteArrayToString(const GCryptoByte* const Array,
                                const uint64 Length,
                                FString& Out_String)
{
    GIC_FString OutStringInteropContainer;

    bool bSucceed = GCrypto_ByteArrayToString(
                Array, Length,
                &OutStringInteropContainer);

    Out_String = std::move(OutStringInteropContainer.String);

    return bSucceed;
}

FString GCrypto::ByteArrayToString(const GCryptoByte* const Array,
                                   const uint64 Length)
{
    GIC_FString OutStringInteropContainer;

    (void)GCrypto_ByteArrayToString(
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
    GIC_std_string OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString_WithErrorInfo(
                EncodedBuffer, EncodedBufferSize,
                &OutDecodedInteropContainer, &OutErrorInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           GCryptoBuffer& Out_Decoded,
                           FString& Out_Error)
{
    GIC_GCryptoBuffer OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer_WithErrorInfo(
                EncodedBuffer, EncodedBufferSize,
                &OutDecodedInteropContainer, &OutErrorInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.Buffer);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           FString& Out_Decoded,
                           FString& Out_Error)
{
    GIC_FString OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoByteArray_To_FString_WithErrorInfo(
                EncodedBuffer, EncodedBufferSize,
                &OutDecodedInteropContainer, &OutErrorInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoBuffer& EncodedBuffer,
                           FString& Out_Decoded,
                           FString& Out_Error)
{
    const GIC_GCryptoBuffer EncodedBufferInteropContainer
    {
        EncodedBuffer
    };

    GIC_FString OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoBuffer_To_FString_WithErrorInfo(
                &EncodedBufferInteropContainer, &OutDecodedInteropContainer,
                &OutErrorInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const FString& EncodedBuffer,
                           FString& Out_Decoded,
                           FString& Out_Error)
{
    const GIC_FString EncodedBufferInteropContainer
    {
        EncodedBuffer
    };

    GIC_FString OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_FString_To_FString_WithErrorInfo(
                &EncodedBufferInteropContainer, &OutDecodedInteropContainer,
                &OutErrorInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           std::string& Out_Decoded)
{
    GIC_std_string OutDecodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString(
                EncodedBuffer, EncodedBufferSize,
                &OutDecodedInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           GCryptoBuffer& Out_Decoded)
{
    GIC_GCryptoBuffer OutDecodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer(
                EncodedBuffer, EncodedBufferSize,
                &OutDecodedInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.Buffer);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoByte* const EncodedBuffer,
                           const uint64 EncodedBufferSize,
                           FString& Out_Decoded)
{
    GIC_FString OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoByteArray_To_FString(
                EncodedBuffer, EncodedBufferSize,
                &OutDecodedInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const GCryptoBuffer& EncodedBuffer,
                           FString& Out_Decoded)
{
    const GIC_GCryptoBuffer EncodedBufferInteropContainer
    {
        EncodedBuffer
    };

    GIC_FString OutDecodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_GCryptoBuffer_To_FString(
                &EncodedBufferInteropContainer,
                &OutDecodedInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Decode(const FString& EncodedBuffer,
                           FString& Out_Decoded)
{
    const GIC_FString EncodedBufferInteropContainer
    {
        EncodedBuffer
    };

    GIC_FString OutDecodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Decode_From_FString_To_FString(
                &EncodedBufferInteropContainer, &OutDecodedInteropContainer);

    Out_Decoded = std::move(OutDecodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const GCryptoByte* const RawBuffer,
                           const uint64 RawBufferSize,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    GIC_FString OutEncodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_GCryptoByteArray_WithErrorInfo(
                RawBuffer, RawBufferSize,
                &OutEncodedInteropContainer, &OutErrorInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const GCryptoBuffer& RawBuffer,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    const GIC_GCryptoBuffer RawBufferInteropContainer
    {
        RawBuffer
    };

    GIC_FString OutEncodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_GCryptoBuffer_WithErrorInfo(
                &RawBufferInteropContainer, &OutEncodedInteropContainer,
                &OutErrorInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const std::string& RawBuffer,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    const GIC_std_string RawBufferInteropContainer
    {
        RawBuffer
    };

    GIC_FString OutEncodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_StdString_WithErrorInfo(
                &RawBufferInteropContainer, &OutEncodedInteropContainer,
                &OutErrorInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const FString& RawBuffer,
                           FString& Out_Encoded,
                           FString& Out_Error)
{
    const GIC_FString RawBufferInteropContainer
    {
        RawBuffer
    };

    GIC_FString OutEncodedInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_FString_WithErrorInfo(
                &RawBufferInteropContainer, &OutEncodedInteropContainer,
                &OutErrorInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const GCryptoByte* const RawBuffer,
                           const uint64 RawBufferSize,
                           FString& Out_Encoded)
{
    GIC_FString OutEncodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_GCryptoByteArray(
                RawBuffer, RawBufferSize,
                &OutEncodedInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const GCryptoBuffer& RawBuffer,
                           FString& Out_Encoded)
{
    const GIC_GCryptoBuffer RawBufferInteropContainer
    {
        RawBuffer
    };

    GIC_FString OutEncodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_GCryptoBuffer(
                &RawBufferInteropContainer,
                &OutEncodedInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const std::string& RawBuffer,
                           FString& Out_Encoded)
{
    const GIC_std_string RawBufferInteropContainer
    {
        RawBuffer
    };

    GIC_FString OutEncodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_StdString(
                &RawBufferInteropContainer, &OutEncodedInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Base64Encode(const FString& RawBuffer,
                           FString& Out_Encoded)
{
    const GIC_FString RawBufferInteropContainer
    {
        RawBuffer
    };

    GIC_FString OutEncodedInteropContainer;

    bool bSucceed =
            GCrypto_Base64Encode_FString(
                &RawBufferInteropContainer, &OutEncodedInteropContainer);

    Out_Encoded = std::move(OutEncodedInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoByte* const PlainBuffer, uint64 PlainBufferSize,
                   FString& Out_MAC, FString& Out_Error)
{
    GIC_FString OutMacInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Sign_GCryptoByteArray_WithErrorInfo(
                Key, KeySize, PlainBuffer, PlainBufferSize,
                &OutMacInteropContainer, &OutErrorInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                   FString& Out_Error)
{
    const GIC_GCryptoBuffer PlainBufferInteropContainer
    {
        PlainBuffer
    };

    GIC_FString OutMacInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Sign_GCryptoBuffer_WithErrorInfo(
                Key, KeySize,
                &PlainBufferInteropContainer, &OutMacInteropContainer,
                &OutErrorInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const std::string& PlainString, FString& Out_MAC,
                   FString& Out_Error)
{
    const GIC_std_string PlainStringInteropContainer
    {
        PlainString
    };

    GIC_FString OutMacInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Sign_StdString_WithErrorInfo(
                Key, KeySize,
                &PlainStringInteropContainer, &OutMacInteropContainer,
                &OutErrorInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const FString& PlainString, FString& Out_MAC,
                   FString& Out_Error)
{
    const GIC_FString PlainStringInteropContainer
    {
        PlainString
    };

    GIC_FString OutMacInteropContainer;
    GIC_FString OutErrorInteropContainer;

    bool bSucceed =
            GCrypto_Sign_FString_WithErrorInfo(
                Key, KeySize,
                &PlainStringInteropContainer, &OutMacInteropContainer,
                &OutErrorInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);
    Out_Error = std::move(OutErrorInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoByte* const PlainBuffer, uint64 PlainBufferSize,
                   FString& Out_MAC)
{

    GIC_FString OutMacInteropContainer;

    bool bSucceed =
            GCrypto_Sign_GCryptoByteArray(
                Key, KeySize, PlainBuffer, PlainBufferSize,
                &OutMacInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const GCryptoBuffer& PlainBuffer, FString& Out_MAC)
{
    const GIC_GCryptoBuffer PlainBufferInteropContainer
    {
        PlainBuffer
    };

    GIC_FString OutMacInteropContainer;

    bool bSucceed =
            GCrypto_Sign_GCryptoBuffer(
                Key, KeySize,
                &PlainBufferInteropContainer, &OutMacInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const std::string& PlainString, FString& Out_MAC)
{
    const GIC_std_string PlainStringInteropContainer
    {
        PlainString
    };

    GIC_FString OutMacInteropContainer;

    bool bSucceed =
            GCrypto_Sign_StdString(
                Key, KeySize,
                &PlainStringInteropContainer, &OutMacInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);

    return bSucceed;
}

bool GCrypto::Sign(const GCryptoByte* const Key, const uint64 KeySize,
                   const FString& PlainString, FString& Out_MAC)
{
    const GIC_FString PlainStringInteropContainer
    {
        PlainString
    };

    GIC_FString OutMacInteropContainer;

    bool bSucceed =
            GCrypto_Sign_FString(
                Key, KeySize,
                &PlainStringInteropContainer, &OutMacInteropContainer);

    Out_MAC = std::move(OutMacInteropContainer.String);

    return bSucceed;
}

GCrypto::GCrypto(const GCryptoByte* SignKey, const uint64 SignKeySize)
    : Pimpl(std::make_unique<GCrypto::Impl>())
{
    Pimpl->SignKey = new GCryptoByte[SignKeySize];
    Pimpl->SignKeySize = SignKeySize;
    std::copy(SignKey, SignKey + SignKeySize, Pimpl->SignKey);
}

GCrypto::GCrypto(const GCryptoBuffer& SignKey)
    : GCrypto(&SignKey[0], static_cast<uint64>(SignKey.size()))
{

}

GCrypto::~GCrypto()
{

}

bool GCrypto::Sign(const GCryptoByte* PlainBuffer, const uint64 PlainBufferSize,
                   FString& Out_MAC, FString& Out_Error) const
{
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainBuffer, PlainBufferSize, Out_MAC, Out_Error);
}

bool GCrypto::Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                   FString& Out_Error) const
{
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainBuffer, Out_MAC, Out_Error);
}

bool GCrypto::Sign(const std::string& PlainString, FString& Out_MAC,
                   FString& Out_Error) const
{
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainString, Out_MAC, Out_Error);
}

bool GCrypto::Sign(const FString& PlainString, FString& Out_MAC,
                   FString& Out_Error) const
{
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainString, Out_MAC, Out_Error);
}

bool GCrypto::Sign(const GCryptoByte* PlainBuffer, const uint64 PlainBufferSize,
                   FString& Out_MAC) const
{
    FString OutError;
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainBuffer, PlainBufferSize, Out_MAC, OutError);
}

bool GCrypto::Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC) const
{
    FString OutError;
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainBuffer, Out_MAC, OutError);
}

bool GCrypto::Sign(const std::string& PlainString, FString& Out_MAC) const
{
    FString OutError;
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainString, Out_MAC, OutError);
}

bool GCrypto::Sign(const FString& PlainString, FString& Out_MAC) const
{
    FString OutError;
    return GCrypto::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                         PlainString, Out_MAC, OutError);
}

GCrypto::Impl::Impl()
{

}

GCrypto::Impl::~Impl()
{
    delete SignKey;
    SignKey = nullptr;
}
