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


#pragma once

#include <string>

#include <Containers/UnrealString.h>
#include <CoreTypes.h>

#include <GTypes/GCryptoTypes.h>

class GODSOFDECEITCRYPTOIMPL_API GCrypto
{
public:
    static bool BytesArrayToString(const GCryptoByte* const Array,
                                   const uint64 Length,
                                   FString& Out_String,
                                   FString& Out_Error);
    static bool BytesArrayToString(const GCryptoByte* const Array,
                                   const uint64 Length,
                                   FString& Out_String);
    static FString BytesArrayToString(const GCryptoByte* const Array,
                                      const uint64 Length);

    static bool HexStringToString(const FString& HexString,
                                  FString& Out_String,
                                  FString& Out_Error);
    static bool HexStringToString(const FString& HexString,
                                  FString& Out_String);
    static FString HexStringToString(const FString& HexString);

    static bool Base64Decode(const GCryptoByte* const EncodedBuffer,
                             const uint64 EncodedBufferSize,
                             std::string& Out_Decoded,
                             FString& Out_Error);
    static bool Base64Decode(const GCryptoByte* const EncodedBuffer,
                             const uint64 EncodedBufferSize,
                             GCryptoBuffer& Out_Decoded,
                             FString& Out_Error);
    static bool Base64Decode(const GCryptoByte* const EncodedBuffer,
                             const uint64 EncodedBufferSize,
                             FString& Out_Decoded,
                             FString& Out_Error);
    static bool Base64Decode(const GCryptoBuffer& EncodedBuffer,
                             FString& Out_Decoded,
                             FString& Out_Error);
    static bool Base64Decode(const FString& EncodedBuffer,
                             FString& Out_Decoded,
                             FString& Out_Error);

    static bool Base64Decode(const GCryptoByte* const EncodedBuffer,
                             const uint64 EncodedBufferSize,
                             std::string& Out_Decoded);
    static bool Base64Decode(const GCryptoByte* const EncodedBuffer,
                             const uint64 EncodedBufferSize,
                             GCryptoBuffer& Out_Decoded);
    static bool Base64Decode(const GCryptoByte* const EncodedBuffer,
                             const uint64 EncodedBufferSize,
                             FString& Out_Decoded);
    static bool Base64Decode(const GCryptoBuffer& EncodedBuffer,
                             FString& Out_Decoded);
    static bool Base64Decode(const FString& EncodedBuffer,
                             FString& Out_Decoded);

    static bool Base64Encode(const GCryptoByte* const RawBuffer,
                             const uint64 RawBufferSize,
                             FString& Out_Encoded,
                             FString& Out_Error);
    static bool Base64Encode(const GCryptoBuffer& RawBuffer,
                             FString& Out_Encoded,
                             FString& Out_Error);
    static bool Base64Encode(const std::string& RawBuffer,
                             FString& Out_Encoded,
                             FString& Out_Error);
    static bool Base64Encode(const FString& RawBuffer,
                             FString& Out_Encoded,
                             FString& Out_Error);

    static bool Base64Encode(const GCryptoByte* const RawBuffer,
                             const uint64 RawBufferSize,
                             FString& Out_Encoded);
    static bool Base64Encode(const GCryptoBuffer& RawBuffer,
                             FString& Out_Encoded);
    static bool Base64Encode(const std::string& RawBuffer,
                             FString& Out_Encoded);
    static bool Base64Encode(const FString& RawBuffer,
                             FString& Out_Encoded);

    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const GCryptoByte* const PlainBuffer, uint64 PlainBufferSize,
                     FString& Out_MAC, FString& Out_Error);
    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
                     FString& Out_Error);
    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const std::string& PlainString, FString& Out_MAC,
                     FString& Out_Error);
    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const FString& PlainString, FString& Out_MAC,
                     FString& Out_Error);

    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const GCryptoByte* const PlainBuffer, uint64 PlainBufferSize,
                     FString& Out_MAC);
    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const GCryptoBuffer& PlainBuffer, FString& Out_MAC);
    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const std::string& PlainString, FString& Out_MAC);
    static bool Sign(const GCryptoByte* const Key, const uint64 KeySize,
                     const FString& PlainString, FString& Out_MAC);

public:
    GCrypto(const GCryptoByte* const SignKey, const uint64 SignKeySize);
    GCrypto(const GCryptoBuffer& SignKey);
    virtual ~GCrypto();

    bool Sign(const GCryptoByte* const PlainBuffer, const uint64 PlainBufferSize,
              FString& Out_MAC, FString& Out_Error) const;
    bool Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC,
              FString& Out_Error) const;
    bool Sign(const std::string& PlainString, FString& Out_MAC,
              FString& Out_Error) const;
    bool Sign(const FString& PlainString, FString& Out_MAC,
              FString& Out_Error) const;

    bool Sign(const GCryptoByte* const PlainBuffer, const uint64 PlainBufferSize,
              FString& Out_MAC) const;
    bool Sign(const GCryptoBuffer& PlainBuffer, FString& Out_MAC) const;
    bool Sign(const std::string& PlainString, FString& Out_MAC) const;
    bool Sign(const FString& PlainString, FString& Out_MAC) const;
};
