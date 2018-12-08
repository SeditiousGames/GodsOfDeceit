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
 * Provides a low-level implementation for an abstraction layer on top of the
 * cryptography API.
 */


#include "GCryptoImpl.h"

#include <algorithm>
#include <vector>

#include <cstdlib>

#include <Containers/StringConv.h>

#include <GHacks/GUndef_check.h>

THIRD_PARTY_INCLUDES_START

#include <boost/algorithm/string.hpp>

THIRD_PARTY_INCLUDES_END

#include <GHacks/GRestore_check.h>

THIRD_PARTY_INCLUDES_START

#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/hmac.h>
#include <cryptopp/sha.h>

THIRD_PARTY_INCLUDES_END

THIRD_PARTY_INCLUDES_START

#include <fmt/format.h>
#include <fmt/ostream.h>

THIRD_PARTY_INCLUDES_END

#define     GCRYPTO_ERROR_DIALOG_TITLE          "Cryptography Error"
#define     GCRYPTO_UNKNOWN_ERROR_MESSAGE       "GCrypto: unknown error!"

struct GCryptoImpl::Impl
{
public:
    GCryptoByte* SignKey;
    uint64 SignKeySize;

public:
    Impl();
    ~Impl();
};

bool GCryptoImpl::BytesArrayToString(const GCryptoByte* Array,
                                     const uint64 Length,
                                     FString& Out_String,
                                     FString& Out_Error)
{
    try
    {
        Out_String = FString();

        fmt::memory_buffer MemoryBuffer;

        for (size_t Index = 0; Index < Length; ++Index)
        {
            fmt::format_to(MemoryBuffer, "{i}", fmt::arg("i", Array[Index]));
        }

        Out_String = StringCast<TCHAR>(
                    fmt::to_string(MemoryBuffer).c_str()).Get();

        return true;
    }

    catch (const std::exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (...)
    {
        Out_Error = StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GCRYPTO_UNKNOWN_ERROR_MESSAGE,
                    GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get());
    }

    return false;
}

bool GCryptoImpl::BytesArrayToString(const GCryptoByte* Array,
                                     const uint64 Length,
                                     FString& Out_String)
{
    FString OutError;
    return GCryptoImpl::BytesArrayToString(Array, Length, Out_String,
                                           OutError);
}

FString GCryptoImpl::BytesArrayToString(const GCryptoByte* Array,
                                        const uint64 Length)
{
    FString Result;
    FString OutError;
    (void)GCryptoImpl::BytesArrayToString(Array, Length, Result, OutError);
    return Result;
}

bool GCryptoImpl::HexStringToString(const FString& HexString,
                                    FString& Out_String,
                                    FString& Out_Error)
{
    try {
        Out_String = FString();

        std::vector<std::string> Bytes;
        std::string HexString_(StringCast<ANSICHAR>(*HexString).Get());

        boost::algorithm::iter_split(
                    Bytes, HexString_,
                    boost::algorithm::first_finder(":"));

        fmt::memory_buffer MemoryBuffer;

        for (std::vector<std::string>::iterator Iterator = Bytes.begin();
             Iterator != Bytes.end(); ++Iterator)
        {
            fmt::format_to(MemoryBuffer, "{c}",
                           fmt::arg("c",
                                    static_cast<char>(
                                        std::strtol(
                                            Iterator->c_str(),
                                            nullptr, 16))));
        }

        Out_String = StringCast<TCHAR>(
                    fmt::to_string(MemoryBuffer).c_str()).Get();

        return true;
    }

    catch (const std::exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (...)
    {
        Out_Error = StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GCRYPTO_UNKNOWN_ERROR_MESSAGE,
                    GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get());
    }

    return false;
}

bool GCryptoImpl::HexStringToString(const FString& HexString,
                                    FString& Out_String)
{
    FString OutError;
    return GCryptoImpl::HexStringToString(HexString, Out_String, OutError);
}

FString GCryptoImpl::HexStringToString(const FString& HexString)
{
    FString Result;
    FString OutError;
    (void)GCryptoImpl::HexStringToString(HexString, Result, OutError);
    return Result;
}

bool GCryptoImpl::Base64Decode(const GCryptoByte* EncodedBuffer,
                               const uint64 EncodedBufferSize,
                               std::string& Out_Decoded,
                               FString& Out_Error)
{
    try
    {
        Out_Decoded.clear();
        Out_Error = TEXT("");

        CryptoPP::StringSource StringSource(
                    EncodedBuffer, static_cast<std::size_t>(EncodedBufferSize),
                    true,
                    new CryptoPP::Base64Decoder(
                        new CryptoPP::StringSink(Out_Decoded)
                        )
                    );
        (void)StringSource;

        return true;
    }

    catch (const CryptoPP::Exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),  StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (...)
    {
        Out_Error = StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GCRYPTO_UNKNOWN_ERROR_MESSAGE,
                    GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get());
    }

    return false;
}

bool GCryptoImpl::Base64Decode(const GCryptoByte* EncodedBuffer,
                               const uint64 EncodedBufferSize,
                               GCryptoBuffer& Out_Decoded,
                               FString& Out_Error)
{
    Out_Decoded.clear();
    std::string Decoded;

    bool bSucceed = GCryptoImpl::Base64Decode(
                &EncodedBuffer[0], EncodedBufferSize, Decoded, Out_Error);

    if (bSucceed)
    {
        Out_Decoded.assign(Decoded.begin(), Decoded.end());
    }

    return bSucceed;
}

bool GCryptoImpl::Base64Decode(const GCryptoByte* EncodedBuffer,
                               const uint64 EncodedBufferSize,
                               FString& Out_Decoded,
                               FString& Out_Error)
{
    Out_Decoded = TEXT("");
    std::string Decoded;

    bool bSucceed = GCryptoImpl::Base64Decode(
                &EncodedBuffer[0], EncodedBufferSize, Decoded, Out_Error);

    if (bSucceed)
    {
        Out_Decoded.Append(StringCast<TCHAR>(Decoded.c_str()).Get(),
                           Decoded.size());
        Out_Decoded.TrimToNullTerminator();
    }

    return bSucceed;
}

bool GCryptoImpl::Base64Decode(const GCryptoBuffer& EncodedBuffer,
                               FString& Out_Decoded,
                               FString& Out_Error)
{
    Out_Decoded = TEXT("");
    std::string Decoded;

    bool bSucceed = GCryptoImpl::Base64Decode(&EncodedBuffer[0],
            static_cast<uint64>(EncodedBuffer.size()), Decoded, Out_Error);

    if (bSucceed)
    {
        Out_Decoded.Append(StringCast<TCHAR>(Decoded.c_str()).Get(),
                           Decoded.size());
        Out_Decoded.TrimToNullTerminator();
    }

    return bSucceed;
}

bool GCryptoImpl::Base64Decode(const FString& EncodedBuffer,
                               FString& Out_Decoded,
                               FString& Out_Error)
{
    Out_Decoded = TEXT("");
    std::string Decoded;

    bool bSucceed = GCryptoImpl::Base64Decode(
                reinterpret_cast<const GCryptoByte*>(
                    StringCast<ANSICHAR>(*EncodedBuffer).Get()),
                EncodedBuffer.Len(), Decoded, Out_Error);

    if (bSucceed)
    {
        Out_Decoded.Append(StringCast<TCHAR>(Decoded.c_str()).Get(),
                           Decoded.size());
        Out_Decoded.TrimToNullTerminator();
    }

    return bSucceed;
}

bool GCryptoImpl::Base64Decode(const GCryptoByte* EncodedBuffer,
                               const uint64 EncodedBufferSize,
                               std::string& Out_Decoded)
{
    FString OutError;
    return GCryptoImpl::Base64Decode(EncodedBuffer, EncodedBufferSize,
                                     Out_Decoded, OutError);
}

bool GCryptoImpl::Base64Decode(const GCryptoByte* EncodedBuffer,
                               const uint64 EncodedBufferSize,
                               GCryptoBuffer& Out_Decoded)
{
    FString OutError;
    return GCryptoImpl::Base64Decode(EncodedBuffer, EncodedBufferSize,
                                     Out_Decoded, OutError);
}

bool GCryptoImpl::Base64Decode(const GCryptoByte* EncodedBuffer,
                               const uint64 EncodedBufferSize,
                               FString& Out_Decoded)
{
    FString OutError;
    return GCryptoImpl::Base64Decode(EncodedBuffer, EncodedBufferSize,
                                     Out_Decoded, OutError);
}

bool GCryptoImpl::Base64Decode(const GCryptoBuffer& EncodedBuffer,
                               FString& Out_Decoded)
{
    FString OutError;
    return GCryptoImpl::Base64Decode(EncodedBuffer, Out_Decoded, OutError);
}

bool GCryptoImpl::Base64Decode(const FString& EncodedBuffer,
                               FString& Out_Decoded)
{
    FString OutError;
    return GCryptoImpl::Base64Decode(EncodedBuffer, Out_Decoded, OutError);
}

bool GCryptoImpl::Base64Encode(const GCryptoByte* RawBuffer,
                               const uint64 RawBufferSize,
                               FString& Out_Encoded,
                               FString& Out_Error)
{
    try
    {
        Out_Encoded = TEXT("");
        Out_Error = TEXT("");

        std::string Encoded;

        CryptoPP::StringSource StringSource(
                    RawBuffer, static_cast<std::size_t>(RawBufferSize), true,
                    new CryptoPP::Base64Encoder(
                        new CryptoPP::StringSink(Encoded)));
        (void)StringSource;

        Out_Encoded.Append(StringCast<TCHAR>(
                               Encoded.c_str()).Get(), Encoded.size());
        Out_Encoded.TrimToNullTerminator();

        return true;
    }

    catch (const CryptoPP::Exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (...)
    {
        Out_Error = StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GCRYPTO_UNKNOWN_ERROR_MESSAGE,
                    GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get());
    }

    return false;
}

bool GCryptoImpl::Base64Encode(const GCryptoBuffer& RawBuffer,
                               FString& Out_Encoded,
                               FString& Out_Error)
{
    return GCryptoImpl::Base64Encode(
                &RawBuffer[0],
            static_cast<uint64>(RawBuffer.size()),
            Out_Encoded, Out_Error);
}

bool GCryptoImpl::Base64Encode(const std::string& RawBuffer,
                               FString& Out_Encoded,
                               FString& Out_Error)
{
    return GCryptoImpl::Base64Encode(
                reinterpret_cast<const GCryptoByte*>(RawBuffer.c_str()),
                static_cast<uint64>(RawBuffer.size()),
                Out_Encoded, Out_Error);
}

bool GCryptoImpl::Base64Encode(const FString& RawBuffer,
                               FString& Out_Encoded,
                               FString& Out_Error)
{
    return GCryptoImpl::Base64Encode(
                reinterpret_cast<const GCryptoByte*>(
                    StringCast<ANSICHAR>(*RawBuffer).Get()),
                RawBuffer.Len(),
                Out_Encoded, Out_Error);
}

bool GCryptoImpl::Base64Encode(const GCryptoByte* RawBuffer,
                               const uint64 RawBufferSize,
                               FString& Out_Encoded)
{
    FString OutError;
    return GCryptoImpl::Base64Encode(RawBuffer, RawBufferSize,
                                     Out_Encoded, OutError);
}

bool GCryptoImpl::Base64Encode(const GCryptoBuffer& RawBuffer,
                               FString& Out_Encoded)
{
    return GCryptoImpl::Base64Encode(&RawBuffer[0],
            static_cast<uint64>(RawBuffer.size()),
            Out_Encoded);
}

bool GCryptoImpl::Base64Encode(const std::string& RawBuffer,
                               FString& Out_Encoded)
{
    return GCryptoImpl::Base64Encode(
                reinterpret_cast<const GCryptoByte*>(RawBuffer.c_str()),
                static_cast<uint64>(RawBuffer.size()),
                Out_Encoded);
}

bool GCryptoImpl::Base64Encode(const FString& RawBuffer,
                               FString& Out_Encoded)
{
    return GCryptoImpl::Base64Encode(
                reinterpret_cast<const GCryptoByte*>(
                    StringCast<ANSICHAR>(*RawBuffer).Get()),
                RawBuffer.Len(),
                Out_Encoded);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const GCryptoByte* PlainBuffer, uint64 PlainBufferSize,
                       FString& Out_MAC, FString& Out_Error)
{
    try
    {
        Out_MAC = FString();
        Out_Error = FString();

        CryptoPP::HMAC<CryptoPP::SHA512> HMAC(Key, KeySize);

        std::string MAC;
        CryptoPP::StringSource(
                    PlainBuffer, static_cast<std::size_t>(PlainBufferSize),
                    true, new CryptoPP::HashFilter(
                        HMAC, new CryptoPP::StringSink(MAC)));

        std::string Encoded;
        CryptoPP::StringSource(MAC, true, new CryptoPP::Base64Encoder(
                                   new CryptoPP::StringSink(Encoded)));

        Out_MAC = StringCast<TCHAR>(Encoded.c_str()).Get();

        return true;
    }

    catch (const CryptoPP::Exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
        Out_Error = StringCast<TCHAR>(Exception.what()).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"), StringCast<TCHAR>(Exception.what()).Get());
    }

    catch (...)
    {
        Out_Error = StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get();
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GCRYPTO_UNKNOWN_ERROR_MESSAGE, GCRYPTO_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<TCHAR>(GCRYPTO_UNKNOWN_ERROR_MESSAGE).Get());
    }

    return false;
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                       FString& Out_Error)
{
    return GCryptoImpl::Sign(
                Key, KeySize,
                &PlainBuffer[0], static_cast<uint64>(PlainBuffer.size()),
            Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const std::string& PlainString, FString& Out_MAC,
                       FString& Out_Error)
{
    return GCryptoImpl::Sign(
                Key, KeySize,
                reinterpret_cast<const GCryptoByte*>(PlainString.c_str()),
                static_cast<uint64>(PlainString.size()),
                Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const FString& PlainString, FString& Out_MAC,
                       FString& Out_Error)
{
    return GCryptoImpl::Sign(
                Key, KeySize,
                reinterpret_cast<const GCryptoByte*>(
                    StringCast<ANSICHAR>(*PlainString).Get()),
                static_cast<uint64>(PlainString.Len()),
                Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const GCryptoByte* PlainBuffer, uint64 PlainBufferSize,
                       FString& Out_MAC)
{
    FString OutError;
    return GCryptoImpl::Sign(Key, KeySize, PlainBuffer, PlainBufferSize,
                             Out_MAC, OutError);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const GCryptoBuffer& PlainBuffer, FString& Out_MAC)
{
    FString OutError;
    return GCryptoImpl::Sign(Key, KeySize, PlainBuffer, Out_MAC, OutError);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const std::string& PlainString, FString& Out_MAC)
{
    FString OutError;
    return GCryptoImpl::Sign(Key, KeySize, PlainString, Out_MAC, OutError);
}

bool GCryptoImpl::Sign(const GCryptoByte* Key, const uint64 KeySize,
                       const FString& PlainString, FString& Out_MAC)
{
    FString OutError;
    return GCryptoImpl::Sign(Key, KeySize, PlainString, Out_MAC, OutError);
}

GCryptoImpl::GCryptoImpl(const GCryptoByte* SignKey, const uint64 SignKeySize)
    : Pimpl(std::make_unique<GCryptoImpl::Impl>())
{
    Pimpl->SignKey = new GCryptoByte[SignKeySize];
    Pimpl->SignKeySize = SignKeySize;
    std::copy(SignKey, SignKey + SignKeySize, Pimpl->SignKey);
}

GCryptoImpl::GCryptoImpl(const GCryptoBuffer& SignKey)
    : GCryptoImpl(&SignKey[0], static_cast<uint64>(SignKey.size()))
{

}

GCryptoImpl::~GCryptoImpl()
{

}

bool GCryptoImpl::Sign(const GCryptoByte* PlainBuffer, const uint64 PlainBufferSize,
                       FString& Out_MAC, FString& Out_Error) const
{
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainBuffer, PlainBufferSize, Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                       FString& Out_Error) const
{
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainBuffer, Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const std::string& PlainString, FString& Out_MAC,
                       FString& Out_Error) const
{
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainString, Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const FString& PlainString, FString& Out_MAC,
                       FString& Out_Error) const
{
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainString, Out_MAC, Out_Error);
}

bool GCryptoImpl::Sign(const GCryptoByte* PlainBuffer, const uint64 PlainBufferSize,
                       FString& Out_MAC) const
{
    FString OutError;
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainBuffer, PlainBufferSize, Out_MAC, OutError);
}

bool GCryptoImpl::Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC) const
{
    FString OutError;
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainBuffer, Out_MAC, OutError);
}

bool GCryptoImpl::Sign(const std::string& PlainString, FString& Out_MAC) const
{
    FString OutError;
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainString, Out_MAC, OutError);
}

bool GCryptoImpl::Sign(const FString& PlainString, FString& Out_MAC) const
{
    FString OutError;
    return GCryptoImpl::Sign(Pimpl->SignKey, Pimpl->SignKeySize,
                             PlainString, Out_MAC, OutError);
}

GCryptoImpl::Impl::Impl()
{

}

GCryptoImpl::Impl::~Impl()
{
    delete SignKey;
    SignKey = nullptr;
}
