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
 * A class for generating random numbers, characters, and uuids
 */


#include "GRandom/GRandom.h"

#include <GInterop/GIC_EGRandomCharacterSet.h>
#include <GInterop/GIC_FString.h>
#include <GRandomImpl/GExportedFunctions.h>

void GRandom::Characters(const EGRandomCharacterSet& CharacterSet,
                         const uint64 Length,
                         FString& Out_RandomCharacters)
{
    GIC_FString Out_RandomCharactersInteropContainer;

    const GIC_EGRandomCharacterSet CharacterSetInteropContainer
    {
        CharacterSet
    };

    GRandom_Characters(&CharacterSetInteropContainer,
                       Length,
                       &Out_RandomCharactersInteropContainer);

    Out_RandomCharacters =
            std::move(Out_RandomCharactersInteropContainer.String);

}

int8 GRandom::Number(const int8 LowerBound, const int8 UpperBound)
{
    return GRandom_Number_int8(LowerBound, UpperBound);
}

int16 GRandom::Number(const int16 LowerBound, const int16 UpperBound)
{
    return GRandom_Number_int16(LowerBound, UpperBound);
}

int32 GRandom::Number(const int32 LowerBound, const int32 UpperBound)
{
    return GRandom_Number_int32(LowerBound, UpperBound);
}

int64 GRandom::Number(const int64 LowerBound, const int64 UpperBound)
{
    return GRandom_Number_int64(LowerBound, UpperBound);
}

uint8 GRandom::Number(const uint8 LowerBound, const uint8 UpperBound)
{
    return GRandom_Number_uint8(LowerBound, UpperBound);
}

uint16 GRandom::Number(const uint16 LowerBound, const uint16 UpperBound)
{
    return GRandom_Number_uint16(LowerBound, UpperBound);
}

uint32 GRandom::Number(const uint32 LowerBound, const uint32 UpperBound)
{
    return GRandom_Number_uint32(LowerBound, UpperBound);
}

uint64 GRandom::Number(const uint64 LowerBound, const uint64 UpperBound)
{
    return GRandom_Number_uint64(LowerBound, UpperBound);
}

void GRandom::Uuid(FString& Out_RandomUuid)
{
    GIC_FString Out_RandomUuidInteropContainer;

    GRandom_Uuid(&Out_RandomUuidInteropContainer);

    Out_RandomUuid = std::move(Out_RandomUuidInteropContainer.String);
}
