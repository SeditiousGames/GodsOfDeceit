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
 * Provides the low-level implementation for the random module.
 */


#pragma once

#include <Containers/UnrealString.h>
#include <CoreTypes.h>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

#include <GTypes/GRandomTypes.h>

class GODSOFDECEITRANDOMIMPL_API GRandomImpl
{
private:
    struct Impl;

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

    template <typename TYPE>
    static TYPE Number(const TYPE LowerBound, const TYPE UpperBound)
    {
        boost::lock_guard<boost::mutex> LockGuard(GetLock());
        (void)LockGuard;

        boost::random::uniform_int_distribution<> Distribution(LowerBound,
                                                               UpperBound);
        return Distribution(GetEngine());
    }

    static void Uuid(FString& Out_RandomUuid);

    static FORCEINLINE FString Uuid()
    {
        FString RandomUuid;
        Uuid(RandomUuid);
        return RandomUuid;
    }

private:
    static FORCEINLINE boost::random::mt19937& GetEngine()
    {
        static boost::random::random_device Device;
        static boost::random::mt19937 Generator(Device);
        return Generator;
    }

    static FORCEINLINE boost::mutex& GetLock()
    {
        static boost::mutex Lock;
        return Lock;
    }
};
