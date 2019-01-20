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
 * Provides a low-level implementation for an abstraction layer on top of the
 * compression API.
 */


#pragma once

#include <string>

#include <Containers/UnrealString.h>
#include <CoreTypes.h>

#include <GTypes/GCompressionTypes.h>

class GODSOFDECEITCOMPRESSIONIMPL_API GCompressionImpl
{
public:
    static void Compress(const GCompressionByte* DataArray,
                         const uint64 Length,
                         GCompressionBuffer& Out_CompressedBuffer,
                         const EGCompressionAlgorithm& Algorithm);
    static void Compress(const FString& DataString,
                         GCompressionBuffer& Out_CompressedBuffer,
                         const EGCompressionAlgorithm& Algorithm);
    static void Compress(const std::string& DataString,
                         GCompressionBuffer& Out_CompressedBuffer,
                         const EGCompressionAlgorithm& Algorithm);
    static void Compress(const GCompressionBuffer& DataBuffer,
                         GCompressionBuffer& Out_CompressedBuffer,
                         const EGCompressionAlgorithm& Algorithm);

    static void Decompress(const GCompressionByte* DataArray,
                           const uint64 Length,
                           GCompressionBuffer& Out_UncompressedBuffer,
                           const EGCompressionAlgorithm& Algorithm);
    static void Decompress(const GCompressionByte* DataArray,
                           const uint64 Length,
                           FString& Out_UncompressedString,
                           const EGCompressionAlgorithm& Algorithm);
    static void Decompress(const GCompressionByte* DataArray,
                           const uint64 Length,
                           std::string& Out_UncompressedString,
                           const EGCompressionAlgorithm& Algorithm);
    static void Decompress(const GCompressionBuffer& DataBuffer,
                           GCompressionBuffer& Out_UncompressedBuffer,
                           const EGCompressionAlgorithm& Algorithm);
    static void Decompress(const GCompressionBuffer& DataBuffer,
                           FString& Out_UncompressedString,
                           const EGCompressionAlgorithm& Algorithm);
    static void Decompress(const GCompressionBuffer& DataBuffer,
                           std::string& Out_UncompressedString,
                           const EGCompressionAlgorithm& Algorithm);
};
