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
 * A class for generating random numbers, characters, and uuids.
 */


#pragma once

#include <Containers/UnrealString.h>
#include <CoreTypes.h>

#include <GTypes/GRandomTypes.h>

class GODSOFDECEITRANDOM_API GRandom
{
public:
    static void Characters(const EGRandomCharacterSet& CharacterSet,
                           const uint64 Length,
                           FString& Out_RandomCharacters);

    static FORCEINLINE FString Characters(
            const EGRandomCharacterSet& CharacterSet,
            const uint64 Length)
    {
        FString RandomCharacters;
        Characters(CharacterSet, Length, RandomCharacters);
        return RandomCharacters;
    }

    static int8 Number(const int8 LowerBound, const int8 UpperBound);
    static int16 Number(const int16 LowerBound, const int16 UpperBound);
    static int32 Number(const int32 LowerBound, const int32 UpperBound);
    static int64 Number(const int64 LowerBound, const int64 UpperBound);
    static uint8 Number(const uint8 LowerBound, const uint8 UpperBound);
    static uint16 Number(const uint16 LowerBound, const uint16 UpperBound);
    static uint32 Number(const uint32 LowerBound, const uint32 UpperBound);
    static uint64 Number(const uint64 LowerBound, const uint64 UpperBound);

    static void Uuid(FString& Out_RandomUuid);

    static FORCEINLINE FString Uuid()
    {
        FString RandomUuid;
        Uuid(RandomUuid);
        return RandomUuid;
    }
};
