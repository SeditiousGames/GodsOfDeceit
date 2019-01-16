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
 * Provides a high level compression API.
 */

#include "GCompression/GCompression.h"

#include <GCompressionImpl/GExportedFunctions.h>
#include <GInterop/GIC_EGCompressionAlgorithm.h>
#include <GInterop/GIC_FString.h>
#include <GInterop/GIC_GCompressionBuffer.h>
#include <GInterop/GIC_std_string.h>

void GCompression::Compress(const GCompressionByte* DataArray,
                            const uint64 Length,
                            GCompressionBuffer& Out_CompressedBuffer,
                            const EGCompressionAlgorithm& Algorithm)
{
    GIC_GCompressionBuffer Out_CompressedBufferInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Compress_From_GCompressionByteArray_To_GCompressionBuffer(
                DataArray, Length,
                &Out_CompressedBufferInteropContainer,
                &AlgorithmInteropContainer);

    Out_CompressedBuffer =
            std::move(Out_CompressedBufferInteropContainer.Buffer);
}

void GCompression::Compress(const FString& DataString,
                            GCompressionBuffer& Out_CompressedBuffer,
                            const EGCompressionAlgorithm& Algorithm)
{
    const GIC_FString DataStringInteropContainer
    {
        DataString
    };

    GIC_GCompressionBuffer Out_CompressedBufferInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Compress_From_FString_To_GCompressionBuffer(
                &DataStringInteropContainer,
                &Out_CompressedBufferInteropContainer,
                &AlgorithmInteropContainer);

    Out_CompressedBuffer =
            std::move(Out_CompressedBufferInteropContainer.Buffer);
}

void GCompression::Compress(const std::string& DataString,
                            GCompressionBuffer& Out_CompressedBuffer,
                            const EGCompressionAlgorithm& Algorithm)
{
    const GIC_std_string DataStringInteropContainer
    {
        DataString
    };

    GIC_GCompressionBuffer Out_CompressedBufferInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Compress_From_StdString_To_GCompressionBuffer(
                &DataStringInteropContainer,
                &Out_CompressedBufferInteropContainer,
                &AlgorithmInteropContainer);

    Out_CompressedBuffer =
            std::move(Out_CompressedBufferInteropContainer.Buffer);
}

void GCompression::Compress(const GCompressionBuffer& DataBuffer,
                            GCompressionBuffer& Out_CompressedBuffer,
                            const EGCompressionAlgorithm& Algorithm)
{
    const GIC_GCompressionBuffer DataBufferInteropContainer
    {
        DataBuffer
    };

    GIC_GCompressionBuffer Out_CompressedBufferInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Compress_From_GCompressionBuffer_To_GCompressionBuffer(
                &DataBufferInteropContainer,
                &Out_CompressedBufferInteropContainer,
                &AlgorithmInteropContainer);

    Out_CompressedBuffer =
            std::move(Out_CompressedBufferInteropContainer.Buffer);
}

void GCompression::Decompress(const GCompressionByte* DataArray,
                              const uint64 Length,
                              GCompressionBuffer& Out_UncompressedBuffer,
                              const EGCompressionAlgorithm& Algorithm)
{
    GIC_GCompressionBuffer Out_UncompressedBufferInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Decompress_From_GCompressionByteArray_To_GCompressionBuffer(
                DataArray, Length,
                &Out_UncompressedBufferInteropContainer,
                &AlgorithmInteropContainer);

    Out_UncompressedBuffer =
            std::move(Out_UncompressedBufferInteropContainer.Buffer);
}

void GCompression::Decompress(const GCompressionByte* DataArray,
                              const uint64 Length,
                              FString& Out_UncompressedString,
                              const EGCompressionAlgorithm& Algorithm)
{
    GIC_FString Out_UncompressedStringInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Decompress_From_GCompressionByteArray_To_FString(
                DataArray, Length,
                &Out_UncompressedStringInteropContainer,
                &AlgorithmInteropContainer);

    Out_UncompressedString =
            std::move(Out_UncompressedStringInteropContainer.String);
}

void GCompression::Decompress(const GCompressionByte* DataArray,
                              const uint64 Length,
                              std::string& Out_UncompressedString,
                              const EGCompressionAlgorithm& Algorithm)
{
    GIC_std_string Out_UncompressedStringInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Decompress_From_GCompressionByteArray_To_StdString(
                DataArray, Length,
                &Out_UncompressedStringInteropContainer,
                &AlgorithmInteropContainer);

    Out_UncompressedString =
            std::move(Out_UncompressedStringInteropContainer.String);
}

void GCompression::Decompress(const GCompressionBuffer& DataBuffer,
                              GCompressionBuffer& Out_UncompressedBuffer,
                              const EGCompressionAlgorithm& Algorithm)
{
    const GIC_GCompressionBuffer DataBufferInteropContainer
    {
        DataBuffer
    };

    GIC_GCompressionBuffer Out_UncompressedBufferInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Decompress_From_GCompressionBuffer_To_GCompressionBuffer(
                &DataBufferInteropContainer,
                &Out_UncompressedBufferInteropContainer,
                &AlgorithmInteropContainer);

    Out_UncompressedBuffer =
            std::move(Out_UncompressedBufferInteropContainer.Buffer);
}

void GCompression::Decompress(const GCompressionBuffer& DataBuffer,
                              FString& Out_UncompressedString,
                              const EGCompressionAlgorithm& Algorithm)
{
    const GIC_GCompressionBuffer DataBufferInteropContainer
    {
        DataBuffer
    };

    GIC_FString Out_UncompressedStringInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Decompress_From_GCompressionBuffer_To_FString(
                &DataBufferInteropContainer,
                &Out_UncompressedStringInteropContainer,
                &AlgorithmInteropContainer);

    Out_UncompressedString =
            std::move(Out_UncompressedStringInteropContainer.String);
}

void GCompression::Decompress(const GCompressionBuffer& DataBuffer,
                              std::string& Out_UncompressedString,
                              const EGCompressionAlgorithm& Algorithm)
{
    const GIC_GCompressionBuffer DataBufferInteropContainer
    {
        DataBuffer
    };

    GIC_std_string Out_UncompressedStringInteropContainer;

    const GIC_EGCompressionAlgorithm AlgorithmInteropContainer
    {
        Algorithm
    };

    GCompression_Decompress_From_GCompressionBuffer_To_StdString(
                &DataBufferInteropContainer,
                &Out_UncompressedStringInteropContainer,
                &AlgorithmInteropContainer);

    Out_UncompressedString.assign(
                std::move(Out_UncompressedStringInteropContainer.String));
}
