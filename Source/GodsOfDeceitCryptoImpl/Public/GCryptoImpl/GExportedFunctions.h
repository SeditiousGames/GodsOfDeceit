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
 * Provides a thin C-compatible wrapper around the crypto module's low-level
 * implementation.
 */


#pragma once

/// NOTE
/// Defines a C++ like static_assert
#ifdef __cplusplus
#include <cassert>
#else
#include <assert.h>
#endif  /* __cplusplus */

/// NOTE
/// Contains __bool_true_false_are_defined macro that can be used in order to
/// check whether boolean type is supported by the compiler or not.
#ifdef __cplusplus
#include <cstdbool>
#else
#include <stdbool.h>
#endif  /* __cplusplus */

#include <CoreTypes.h>

#include <GTypes/GCryptoTypes.h>

/// NOTE
/// Check at compile time whether the C compiler has support for bool, true,
/// and false macros.
static_assert(__bool_true_false_are_defined,
              "Error: bool, true, and false are not defined!");

/// NOTE
/// If C++ is used switch to C mode in order to prevent C++'s name mangling of
/// method names.
#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

#if defined ( GOD_BUILDING_CRYPTO_IMPL_MODULE )

/* BytesArrayToString */

DLLEXPORT bool GCrypto_BytesArrayToString_WithErrorInfo(
        const GCryptoByte* const Array,
        const uint64 Length,
        void* Out_String,
        void* Out_Error);

DLLEXPORT bool GCrypto_BytesArrayToString(
        const GCryptoByte* const Array,
        const uint64 Length,
        void* Out_String);

/* HexStringToString */

DLLEXPORT bool GCrypto_HexStringToString_WithErrorInfo(
        const void* const HexString,
        void* Out_String,
        void* Out_Error);

DLLEXPORT bool GCrypto_HexStringToString(
        const void* const HexString,
        void* Out_String);

/* Base64Decode with error information */

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString_WithErrorInfo(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer_WithErrorInfo(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_FString_WithErrorInfo(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoBuffer_To_FString_WithErrorInfo(
        const void* const EncodedBuffer,
        void* Out_Decoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Decode_From_FString_To_FString_WithErrorInfo(
        const void* const EncodedBuffer,
        void* Out_Decoded,
        void* Out_Error);

/* Base64Decode without error information */

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded);

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded);

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_FString(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded);

DLLEXPORT bool GCrypto_Base64Decode_From_GCryptoBuffer_To_FString(
        const void* const EncodedBuffer,
        void* Out_Decoded);

DLLEXPORT bool GCrypto_Base64Decode_From_FString_To_FString(
        const void* const EncodedBuffer,
        void* Out_Decoded);

/* Base64Encode with error information */

DLLEXPORT bool GCrypto_Base64Encode_GCryptoByteArray_WithErrorInfo(
        const GCryptoByte* const RawBuffer,
        const uint64 RawBufferSize,
        void* Out_Encoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Encode_GCryptoBuffer_WithErrorInfo(
        const void* const RawBuffer,
        void* Out_Encoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Encode_StdString_WithErrorInfo(
        const void* const RawBuffer,
        void* Out_Encoded,
        void* Out_Error);

DLLEXPORT bool GCrypto_Base64Encode_FString_WithErrorInfo(
        const void* const RawBuffer,
        void* Out_Encoded,
        void* Out_Error);

/* Base64Encode without error information */

DLLEXPORT bool GCrypto_Base64Encode_GCryptoByteArray(
        const GCryptoByte* const RawBuffer,
        const uint64 RawBufferSize,
        void* Out_Encoded);

DLLEXPORT bool GCrypto_Base64Encode_GCryptoBuffer(
        const void* const RawBuffer,
        void* Out_Encoded);

DLLEXPORT bool GCrypto_Base64Encode_StdString(
        const void* const RawBuffer,
        void* Out_Encoded);

DLLEXPORT bool GCrypto_Base64Encode_FString(
        const void* const RawBuffer,
        void* Out_Encoded);

/* Sign with error information */

DLLEXPORT bool GCrypto_Sign_GCryptoByteArray_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const GCryptoByte* const PlainBuffer,
        const uint64 PlainBufferSize,
        void* Out_MAC,
        void* Out_Error);

DLLEXPORT bool GCrypto_Sign_GCryptoBuffer_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainBuffer,
        void* Out_MAC,
        void* Out_Error);

DLLEXPORT bool GCrypto_Sign_StdString_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC,
        void* Out_Error);

DLLEXPORT bool GCrypto_Sign_FString_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC,
        void* Out_Error);

/* Sign without error information */

DLLEXPORT bool GCrypto_Sign_GCryptoByteArray(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const GCryptoByte* PlainBuffer,
        const uint64 PlainBufferSize,
        void* Out_MAC);

DLLEXPORT bool GCrypto_Sign_GCryptoBuffer(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainBuffer,
        void* Out_MAC);

DLLEXPORT bool GCrypto_Sign_StdString(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC);

DLLEXPORT bool GCrypto_Sign_FString(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC);

#else

/* BytesArrayToString */

DLLIMPORT bool GCrypto_BytesArrayToString_WithErrorInfo(
        const GCryptoByte* const Array,
        const uint64 Length,
        void* Out_String,
        void* Out_Error);

DLLIMPORT bool GCrypto_BytesArrayToString(
        const GCryptoByte* const Array,
        const uint64 Length,
        void* Out_String);

/* HexStringToString */

DLLIMPORT bool GCrypto_HexStringToString_WithErrorInfo(
        const void* const HexString,
        void* Out_String,
        void* Out_Error);

DLLIMPORT bool GCrypto_HexStringToString(
        const void* const HexString,
        void* Out_String);

/* Base64Decode with error information */

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString_WithErrorInfo(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer_WithErrorInfo(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_FString_WithErrorInfo(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoBuffer_To_FString_WithErrorInfo(
        const void* const EncodedBuffer,
        void* Out_Decoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Decode_From_FString_To_FString_WithErrorInfo(
        const void* const EncodedBuffer,
        void* Out_Decoded,
        void* Out_Error);

/* Base64Decode without error information */

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_StdString(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded);

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_GCryptoBuffer(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded);

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoByteArray_To_FString(
        const GCryptoByte* const EncodedBuffer,
        const uint64 EncodedBufferSize,
        void* Out_Decoded);

DLLIMPORT bool GCrypto_Base64Decode_From_GCryptoBuffer_To_FString(
        const void* const EncodedBuffer,
        void* Out_Decoded);

DLLIMPORT bool GCrypto_Base64Decode_From_FString_To_FString(
        const void* const EncodedBuffer,
        void* Out_Decoded);

/* Base64Encode with error information */

DLLIMPORT bool GCrypto_Base64Encode_GCryptoByteArray_WithErrorInfo(
        const GCryptoByte* const RawBuffer,
        const uint64 RawBufferSize,
        void* Out_Encoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Encode_GCryptoBuffer_WithErrorInfo(
        const void* const RawBuffer,
        void* Out_Encoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Encode_StdString_WithErrorInfo(
        const void* const RawBuffer,
        void* Out_Encoded,
        void* Out_Error);

DLLIMPORT bool GCrypto_Base64Encode_FString_WithErrorInfo(
        const void* const RawBuffer,
        void* Out_Encoded,
        void* Out_Error);

/* Base64Encode without error information */

DLLIMPORT bool GCrypto_Base64Encode_GCryptoByteArray(
        const GCryptoByte* const RawBuffer,
        const uint64 RawBufferSize,
        void* Out_Encoded);

DLLIMPORT bool GCrypto_Base64Encode_GCryptoBuffer(
        const void* const RawBuffer,
        void* Out_Encoded);

DLLIMPORT bool GCrypto_Base64Encode_StdString(
        const void* const RawBuffer,
        void* Out_Encoded);

DLLIMPORT bool GCrypto_Base64Encode_FString(
        const void* const RawBuffer,
        void* Out_Encoded);

/* Sign with error information */

DLLIMPORT bool GCrypto_Sign_GCryptoByteArray_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const GCryptoByte* const PlainBuffer,
        const uint64 PlainBufferSize,
        void* Out_MAC,
        void* Out_Error);

DLLIMPORT bool GCrypto_Sign_GCryptoBuffer_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainBuffer,
        void* Out_MAC,
        void* Out_Error);

DLLIMPORT bool GCrypto_Sign_StdString_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC,
        void* Out_Error);

DLLIMPORT bool GCrypto_Sign_FString_WithErrorInfo(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC,
        void* Out_Error);

/* Sign without error information */

DLLIMPORT bool GCrypto_Sign_GCryptoByteArray(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const GCryptoByte* PlainBuffer,
        const uint64 PlainBufferSize,
        void* Out_MAC);

DLLIMPORT bool GCrypto_Sign_GCryptoBuffer(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainBuffer,
        void* Out_MAC);

DLLIMPORT bool GCrypto_Sign_StdString(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC);

DLLIMPORT bool GCrypto_Sign_FString(
        const GCryptoByte* const Key,
        const uint64 KeySize,
        const void* const PlainString,
        void* Out_MAC);

#endif  /* defined ( GOD_BUILDING_CRYPTO_IMPL_MODULE ) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
