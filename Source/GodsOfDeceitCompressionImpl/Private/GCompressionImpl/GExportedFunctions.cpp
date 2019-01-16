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
 * Provides a thin C-compatible wrapper around the compression module's low-level
 * implementation.
 */


#include "GCompressionImpl/GExportedFunctions.h"

#include <GInterop/GIC_EGCompressionAlgorithm.h>
#include <GInterop/GIC_FString.h>
#include <GInterop/GIC_GCompressionBuffer.h>
#include <GInterop/GIC_std_string.h>

#include "GCompressionImpl/GCompressionImpl.h"

bool GCompression_Compress_From_GCompressionByteArray_To_GCompressionBuffer(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_CompressedBuffer,
        const void* Algorithm)
{
    return GCompressionImpl::Compress(
                DataArray, Length,
                static_cast<GIC_GCompressionBuffer*>(Out_CompressedBuffer)->Buffer,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Compress_From_FString_To_GCompressionBuffer(
        const void* DataString,
        void* Out_CompressedBuffer,
        const void* Algorithm)
{
    return GCompressionImpl::Compress(
                static_cast<const GIC_FString*>(DataString)->String,
                static_cast<GIC_GCompressionBuffer*>(Out_CompressedBuffer)->Buffer,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Compress_From_StdString_To_GCompressionBuffer(
        const void* DataString,
        void* Out_CompressedBuffer,
        const void* Algorithm)
{
    return GCompressionImpl::Compress(
                static_cast<const GIC_std_string*>(DataString)->String,
                static_cast<GIC_GCompressionBuffer*>(Out_CompressedBuffer)->Buffer,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Compress_From_GCompressionBuffer_To_GCompressionBuffer(
        const void* DataBuffer,
        void* Out_CompressedBuffer,
        const void* Algorithm)
{
    return GCompressionImpl::Compress(
                static_cast<const GIC_GCompressionBuffer*>(DataBuffer)->Buffer,
                static_cast<GIC_GCompressionBuffer*>(Out_CompressedBuffer)->Buffer,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Decompress_From_GCompressionByteArray_To_GCompressionBuffer(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedBuffer,
        const void* Algorithm)
{
    return GCompressionImpl::Decompress(
                DataArray, Length,
                static_cast<GIC_GCompressionBuffer*>(Out_UncompressedBuffer)->Buffer,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Decompress_From_GCompressionByteArray_To_FString(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedString,
        const void* Algorithm)
{
    return GCompressionImpl::Decompress(
                DataArray, Length,
                static_cast<GIC_FString*>(Out_UncompressedString)->String,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Decompress_From_GCompressionByteArray_To_StdString(
        const GCompressionByte* DataArray,
        const uint64 Length,
        void* Out_UncompressedString,
        const void* Algorithm)
{
    return GCompressionImpl::Decompress(
                DataArray, Length,
                static_cast<GIC_std_string*>(Out_UncompressedString)->String,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Decompress_From_GCompressionBuffer_To_GCompressionBuffer(
        const void* DataBuffer,
        void* Out_UncompressedBuffer,
        const void* Algorithm)
{
    return GCompressionImpl::Decompress(
                static_cast<const GIC_GCompressionBuffer*>(DataBuffer)->Buffer,
                static_cast<GIC_GCompressionBuffer*>(Out_UncompressedBuffer)->Buffer,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Decompress_From_GCompressionBuffer_To_FString(
        const void* DataBuffer,
        void* Out_UncompressedString,
        const void* Algorithm)
{
    return GCompressionImpl::Decompress(
                static_cast<const GIC_GCompressionBuffer*>(DataBuffer)->Buffer,
                static_cast<GIC_FString*>(Out_UncompressedString)->String,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}

bool GCompression_Decompress_From_GCompressionBuffer_To_StdString(
        const void* DataBuffer,
        void* Out_UncompressedString,
        const void* Algorithm)
{
    return GCompressionImpl::Decompress(
                static_cast<const GIC_GCompressionBuffer*>(DataBuffer)->Buffer,
                static_cast<GIC_std_string*>(Out_UncompressedString)->String,
                static_cast<const GIC_EGCompressionAlgorithm*>(Algorithm)->Algorithm);
}
