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
 * Provides a thin C-compatible wrapper around the compression module's low-level
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

#include <GTypes/GCompressionTypes.h>

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

#if defined ( GOD_BUILDING_COMPRESSION_IMPL_MODULE )

DLLEXPORT void GCompression_Compress_From_GCompressionByteArray_To_GCompressionBuffer(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLEXPORT void GCompression_Compress_From_FString_To_GCompressionBuffer(
        const void* DataString,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLEXPORT void GCompression_Compress_From_StdString_To_GCompressionBuffer(
        const void* DataString,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLEXPORT void GCompression_Compress_From_GCompressionBuffer_To_GCompressionBuffer(
        const void* DataBuffer,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLEXPORT void GCompression_Decompress_From_GCompressionByteArray_To_GCompressionBuffer(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedBuffer,
        const void* Algorithm);

DLLEXPORT void GCompression_Decompress_From_GCompressionByteArray_To_FString(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedString,
        const void* Algorithm);

DLLEXPORT void GCompression_Decompress_From_GCompressionByteArray_To_StdString(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedString,
        const void* Algorithm);

DLLEXPORT void GCompression_Decompress_From_GCompressionBuffer_To_GCompressionBuffer(
        const void* DataBuffer,
        void* Out_UncompressedBuffer,
        const void* Algorithm);

DLLEXPORT void GCompression_Decompress_From_GCompressionBuffer_To_FString(
        const void* DataBuffer,
        void* Out_UncompressedString,
        const void* Algorithm);

DLLEXPORT void GCompression_Decompress_From_GCompressionBuffer_To_StdString(
        const void* DataBuffer,
        void* Out_UncompressedString,
        const void* Algorithm);

#else

DLLIMPORT void GCompression_Compress_From_GCompressionByteArray_To_GCompressionBuffer(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLIMPORT void GCompression_Compress_From_FString_To_GCompressionBuffer(
        const void* DataString,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLIMPORT void GCompression_Compress_From_StdString_To_GCompressionBuffer(
        const void* DataString,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLIMPORT void GCompression_Compress_From_GCompressionBuffer_To_GCompressionBuffer(
        const void* DataBuffer,
        void* Out_CompressedBuffer,
        const void* Algorithm);

DLLIMPORT void GCompression_Decompress_From_GCompressionByteArray_To_GCompressionBuffer(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedBuffer,
        const void* Algorithm);

DLLIMPORT void GCompression_Decompress_From_GCompressionByteArray_To_FString(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedString,
        const void* Algorithm);

DLLIMPORT void GCompression_Decompress_From_GCompressionByteArray_To_StdString(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedString,
        const void* Algorithm);

DLLIMPORT void GCompression_Decompress_From_GCompressionBuffer_To_GCompressionBuffer(
        const void* DataBuffer,
        void* Out_UncompressedBuffer,
        const void* Algorithm);

DLLIMPORT void GCompression_Decompress_From_GCompressionBuffer_To_FString(
        const void* DataBuffer,
        void* Out_UncompressedString,
        const void* Algorithm);

DLLIMPORT void GCompression_Decompress_From_GCompressionBuffer_To_StdString(
        const void* DataBuffer,
        void* Out_UncompressedString,
        const void* Algorithm);

#endif  /* defined ( GOD_BUILDING_CRYPTO_IMPL_MODULE ) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
