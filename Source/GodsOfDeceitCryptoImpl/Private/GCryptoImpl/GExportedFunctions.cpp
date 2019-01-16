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
 * Provides a thin C-compatible wrapper around the crypto module's low-level
 * implementation.
 */


#include "GCryptoImpl/GExportedFunctions.h"

#include <GInterop/GIC_FString.h>
#include <GInterop/GIC_GCryptoBuffer.h>
#include <GInterop/GIC_std_string.h>

#include "GCryptoImpl/GCryptoImpl.h"

void GCrypto_ByteArrayToString(
        const GCryptoByte* const Array,
        const uint64 Length,
        void* Out_String)
{
    GCryptoImpl::ByteArrayToString(
                Array, Length,
                static_cast<GIC_FString*>(Out_String)->String);
}

void GCrypto_HexStringToString(
        const void* const HexString,
        void* Out_String)
{
    GCryptoImpl::HexStringToString(
                static_cast<const GIC_FString*>(HexString)->String,
                static_cast<GIC_FString*>(Out_String)->String);
}

void GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded)
{
    GCryptoImpl::Base64Decode(
                EncodedBuffer, EncodedBufferSize,
                static_cast<GIC_std_string*>(Out_Decoded)->String);
}

void GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded)
{
    GCryptoImpl::Base64Decode(
                EncodedBuffer, EncodedBufferSize,
                static_cast<GIC_GCryptoBuffer*>(Out_Decoded)->Buffer);
}

void GCrypto_Base64Decode_From_GCryptoByteArray_To_FString(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded)
{
    GCryptoImpl::Base64Decode(
                EncodedBuffer, EncodedBufferSize,
                static_cast<GIC_FString*>(Out_Decoded)->String);
}

void GCrypto_Base64Decode_From_GCryptoBuffer_To_FString(
        const void* const EncodedBuffer,
        void* Out_Decoded)
{
    GCryptoImpl::Base64Decode(
                static_cast<const GIC_GCryptoBuffer*>(EncodedBuffer)->Buffer,
                static_cast<GIC_FString*>(Out_Decoded)->String);
}

void GCrypto_Base64Decode_From_FString_To_FString(
        const void* const EncodedBuffer,
        void* Out_Decoded)
{
    GCryptoImpl::Base64Decode(
                static_cast<const GIC_FString*>(EncodedBuffer)->String,
                static_cast<GIC_FString*>(Out_Decoded)->String);
}

void GCrypto_Base64Encode_GCryptoByteArray(
        const GCryptoByte* const RawBuffer,
        const uint64 RawBufferSize,
        void* Out_Encoded)
{
    GCryptoImpl::Base64Encode(
                RawBuffer, RawBufferSize,
                static_cast<GIC_FString*>(Out_Encoded)->String);
}

void GCrypto_Base64Encode_GCryptoBuffer(
        const void* const RawBuffer,
        void* Out_Encoded)
{
    GCryptoImpl::Base64Encode(
                static_cast<const GIC_GCryptoBuffer*>(RawBuffer)->Buffer,
                static_cast<GIC_FString*>(Out_Encoded)->String);
}

void GCrypto_Base64Encode_StdString(
        const void* const RawBuffer,
        void* Out_Encoded)
{
    GCryptoImpl::Base64Encode(
                static_cast<const GIC_std_string*>(RawBuffer)->String,
                static_cast<GIC_FString*>(Out_Encoded)->String);
}

void GCrypto_Base64Encode_FString(
        const void* const RawBuffer,
        void* Out_Encoded)
{
    GCryptoImpl::Base64Encode(
                static_cast<const GIC_FString*>(RawBuffer)->String,
                static_cast<GIC_FString*>(Out_Encoded)->String);
}

void GCrypto_Sign_GCryptoByteArray(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const GCryptoByte* const PlainBuffer,
        const uint64 PlainBufferSize,
        void* Out_MAC)
{
    GCryptoImpl::Sign(
                Key, KeySize, PlainBuffer, PlainBufferSize,
                static_cast<GIC_FString*>(Out_MAC)->String);
}

void GCrypto_Sign_GCryptoBuffer(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainBuffer,
        void* Out_MAC)
{
    GCryptoImpl::Sign(
                Key, KeySize,
                static_cast<const GIC_GCryptoBuffer*>(PlainBuffer)->Buffer,
                static_cast<GIC_FString*>(Out_MAC)->String);
}

void GCrypto_Sign_StdString(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC)
{
    GCryptoImpl::Sign(
                Key, KeySize,
                static_cast<const GIC_std_string*>(PlainString)->String,
                static_cast<GIC_FString*>(Out_MAC)->String);
}

void GCrypto_Sign_FString(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC)
{
    GCryptoImpl::Sign(
                Key, KeySize,
                static_cast<const GIC_FString*>(PlainString)->String,
                static_cast<GIC_FString*>(Out_MAC)->String);
}
