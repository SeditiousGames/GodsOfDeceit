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
 * Provides a low-level implementation for an abstraction layer on top of the
 * compression API.
 */


#include "GCompressionImpl/GCompressionImpl.h"

#include <ios>

#include <Containers/StringConv.h>
#include <Misc/AssertionMacros.h>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <boost/exception/diagnostic_information.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
/// NOTE
/// We won't support bzip2 or gzip in the foreseeable future
//#include <boost/iostreams/filter/bzip2.hpp>
//#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

#include <GHacks/GInclude_Windows.h>
#include <GTypes/GCompressionTypes.h>

#define GCOMPRESSION_COMPRESS_ERROR_DIALOG_TITLE    "Compression Error"
#define GCOMPRESSION_DECOMPRESS_ERROR_DIALOG_TITLE  "Decompression Error"
#define GGCOMPRESSION_UNKNOWN_ERROR_MESSAGE         "GCompression: unknown error!"

void GCompressionImpl::Compress(const GCompressionByte* DataArray,
                                const uint64 Length,
                                GCompressionBuffer& Out_CompressedBuffer,
                                const EGCompressionAlgorithm& Algorithm)
{
    try
    {
        Out_CompressedBuffer.clear();
        boost::iostreams::filtering_streambuf<boost::iostreams::output> Output;

        switch(Algorithm) {
        case EGCompressionAlgorithm::Zlib:
            Output.push(boost::iostreams::zlib_compressor());
            break;
        case EGCompressionAlgorithm::Gzip:
            ///Output.push(boost::iostreams::gzip_compressor());
            checkf(false, TEXT("FATAL: Gzip compression algorithm is not"
                               " supported! Use Zlib instead!"));
            break;
        case EGCompressionAlgorithm::Bzip2:
            ///Output.push(boost::iostreams::bzip2_compressor());
            checkf(false, TEXT("FATAL: Bzip2 compression algorithm is not"
                               " supported! Use Zlib instead!"));
            break;
        }

        Output.push(boost::iostreams::back_inserter(Out_CompressedBuffer));
        boost::iostreams::write(Output, DataArray,
                                static_cast<std::streamsize>(Length));
    }

    catch (const boost::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, boost::diagnostic_information(Exception).c_str(),
                    GCOMPRESSION_DECOMPRESS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false,
               TEXT("%s"),
               StringCast<WIDECHAR>(
                   boost::diagnostic_information(Exception).c_str()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(),
                    GCOMPRESSION_DECOMPRESS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GGCOMPRESSION_UNKNOWN_ERROR_MESSAGE,
                    GCOMPRESSION_COMPRESS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false,
               TEXT("%s"),
               StringCast<WIDECHAR>(
                   GGCOMPRESSION_UNKNOWN_ERROR_MESSAGE).Get());
    }
}

void GCompressionImpl::Compress(const FString& DataString,
                                GCompressionBuffer& Out_CompressedBuffer,
                                const EGCompressionAlgorithm& Algorithm)
{
    GCompressionImpl::Compress(StringCast<ANSICHAR>(*DataString).Get(),
                               static_cast<uint64>(DataString.Len()),
                               Out_CompressedBuffer, Algorithm);
}

void GCompressionImpl::Compress(const std::string& DataString,
                                GCompressionBuffer& Out_CompressedBuffer,
                                const EGCompressionAlgorithm& Algorithm)
{
    GCompressionImpl::Compress(DataString.c_str(), DataString.size(),
                               Out_CompressedBuffer, Algorithm);
}

void GCompressionImpl::Compress(const GCompressionBuffer& DataBuffer,
                                GCompressionBuffer& Out_CompressedBuffer,
                                const EGCompressionAlgorithm& Algorithm)
{
    GCompressionImpl::Compress(&DataBuffer[0], DataBuffer.size(),
            Out_CompressedBuffer, Algorithm);
}

void GCompressionImpl::Decompress(const GCompressionByte* DataArray,
                                  const uint64 Length,
                                  GCompressionBuffer& Out_UncompressedBuffer,
                                  const EGCompressionAlgorithm& Algorithm)
{
    try
    {
        Out_UncompressedBuffer.clear();
        boost::iostreams::filtering_streambuf<boost::iostreams::output> Output;

        switch(Algorithm) {
        case EGCompressionAlgorithm::Zlib:
            Output.push(boost::iostreams::zlib_decompressor());
            break;
        case EGCompressionAlgorithm::Gzip:
            ///Output.push(boost::iostreams::gzip_decompressor());
            checkf(false, TEXT("FATAL: Gzip compression algorithm is not"
                               " supported! Use Zlib instead!"));
            break;
        case EGCompressionAlgorithm::Bzip2:
            ///Output.push(boost::iostreams::bzip2_decompressor());
            checkf(false, TEXT("FATAL: Bzip2 compression algorithm is not"
                               " supported! Use Zlib instead!"));
            break;
        }

        Output.push(boost::iostreams::back_inserter(Out_UncompressedBuffer));
        boost::iostreams::write(Output, DataArray,
                                static_cast<std::streamsize>(Length));
    }

    catch (const boost::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, boost::diagnostic_information(Exception).c_str(),
                    GCOMPRESSION_COMPRESS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false,
               TEXT("%s"),
               StringCast<WIDECHAR>(
                   boost::diagnostic_information(Exception).c_str()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(),
                    GCOMPRESSION_COMPRESS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GGCOMPRESSION_UNKNOWN_ERROR_MESSAGE,
                    GCOMPRESSION_COMPRESS_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false,
               TEXT("%s"),
               StringCast<WIDECHAR>(
                   GGCOMPRESSION_UNKNOWN_ERROR_MESSAGE).Get());
    }
}

void GCompressionImpl::Decompress(const GCompressionByte* DataArray,
                                  const uint64 Length,
                                  FString& Out_UncompressedString,
                                  const EGCompressionAlgorithm& Algorithm)
{
    Out_UncompressedString = TEXT("");
    GCompressionBuffer Buffer;

    GCompressionImpl::Decompress(
                DataArray, Length, Buffer, Algorithm);

    Out_UncompressedString.Append(StringCast<WIDECHAR>(&Buffer[0]).Get(),
            static_cast<int32>(Buffer.size()));
    Out_UncompressedString.TrimToNullTerminator();
}

void GCompressionImpl::Decompress(const GCompressionByte* DataArray,
                                  const uint64 Length,
                                  std::string& Out_UncompressedString,
                                  const EGCompressionAlgorithm& Algorithm)
{
    Out_UncompressedString.clear();
    GCompressionBuffer Buffer;

    GCompressionImpl::Decompress(
                DataArray, Length, Buffer, Algorithm);

    Out_UncompressedString.assign(&Buffer[0], Buffer.size());
}

void GCompressionImpl::Decompress(const GCompressionBuffer& DataBuffer,
                                  GCompressionBuffer& Out_UncompressedBuffer,
                                  const EGCompressionAlgorithm& Algorithm)
{
    return GCompressionImpl::Decompress(&DataBuffer[0], DataBuffer.size(),
            Out_UncompressedBuffer, Algorithm);
}

void GCompressionImpl::Decompress(const GCompressionBuffer& DataBuffer,
                                  FString& Out_UncompressedString,
                                  const EGCompressionAlgorithm& Algorithm)
{
    Out_UncompressedString = TEXT("");

    GCompressionBuffer Buffer;

    GCompressionImpl::Decompress(
                &DataBuffer[0], DataBuffer.size(), Buffer, Algorithm);

    Out_UncompressedString.Append(StringCast<WIDECHAR>(&Buffer[0]).Get(),
            static_cast<int32>(Buffer.size()));
    Out_UncompressedString.TrimToNullTerminator();
}

void GCompressionImpl::Decompress(const GCompressionBuffer& DataBuffer,
                                  std::string& Out_UncompressedString,
                                  const EGCompressionAlgorithm& Algorithm)
{
    Out_UncompressedString.clear();

    GCompressionBuffer Buffer;

    GCompressionImpl::Decompress(
                &DataBuffer[0], DataBuffer.size(), Buffer, Algorithm);

    Out_UncompressedString.assign(&DataBuffer[0], DataBuffer.size());
}
