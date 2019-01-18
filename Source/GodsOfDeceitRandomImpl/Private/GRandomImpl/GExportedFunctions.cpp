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
 * Provides a thin C-compatible wrapper around the random module's low-level
 * implementation.
 */


#include "GRandomImpl/GExportedFunctions.h"

#include <GInterop/GIC_EGRandomCharacterSet.h>
#include <GInterop/GIC_FString.h>
#include <GTypes/GRandomTypes.h>

#include "GRandomImpl/GRandomImpl.h"

void GRandom_Characters(
        const void* CharacterSet,
        const uint64 Length,
        void* Out_RandomCharacters)
{
    GRandomImpl::Characters(
                static_cast<const GIC_EGRandomCharacterSet*>(
                    CharacterSet)->CharacterSet,
                Length,
                static_cast<GIC_FString*>(Out_RandomCharacters)->String);
}

int8 GRandom_Number_int8(
        const int8 LowerBound,
        const int8 UpperBound)
{
    return GRandomImpl::Number<int8>(LowerBound, UpperBound);
}

int16 GRandom_Number_int16(
        const int16 LowerBound,
        const int16 UpperBound)
{
    return GRandomImpl::Number<int16>(LowerBound, UpperBound);
}

int32 GRandom_Number_int32(
        const int32 LowerBound,
        const int32 UpperBound)
{
    return GRandomImpl::Number<int32>(LowerBound, UpperBound);
}

int64 GRandom_Number_int64(
        const int64 LowerBound,
        const int64 UpperBound)
{
    return GRandomImpl::Number<int64>(LowerBound, UpperBound);
}

uint8 GRandom_Number_uint8(
        const uint8 LowerBound,
        const uint8 UpperBound)
{
    return GRandomImpl::Number<uint8>(LowerBound, UpperBound);
}

uint16 GRandom_Number_uint16(
        const uint16 LowerBound,
        const uint16 UpperBound)
{
    return GRandomImpl::Number<uint16>(LowerBound, UpperBound);
}

uint32 GRandom_Number_uint32(
        const uint32 LowerBound,
        const uint32 UpperBound)
{
    return GRandomImpl::Number<uint32>(LowerBound, UpperBound);
}

uint64 GRandom_Number_uint64(
        const uint64 LowerBound,
        const uint64 UpperBound)
{
    return GRandomImpl::Number<uint64>(LowerBound, UpperBound);
}

void GRandom_Uuid(
        void* Out_RandomUuid)
{
    GRandomImpl::Uuid(static_cast<GIC_FString*>(Out_RandomUuid)->String);
}
