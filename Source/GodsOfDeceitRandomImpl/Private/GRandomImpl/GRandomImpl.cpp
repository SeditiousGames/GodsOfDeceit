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
 * Provides the low-level implementation for the random module
 */


#include "GRandomImpl/GRandomImpl.h"

#include <Containers/Map.h>
#include <Containers/StringConv.h>
#include <Containers/UnrealString.h>
#include <Templates/Tuple.h>

THIRD_PARTY_INCLUDES_START
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
THIRD_PARTY_INCLUDES_END

struct GRandomImpl::Impl
{
public:
    typedef TMap<EGRandomCharacterSet, FString> CharacterSetMap;
    typedef TTuple<EGRandomCharacterSet, FString> CharacterSetTuple;

public:
    static CharacterSetMap &GetLookupTable();
};

void GRandomImpl::Characters(const EGRandomCharacterSet& CharacterSet,
                             const uint64 Length,
                             FString& Out_RandomCharacters)
{
    boost::lock_guard<boost::mutex> LockGuard(GetLock());
    (void)LockGuard;

    boost::random::uniform_int_distribution<> IndexDistribution(
                0, static_cast<int32>(
                    Impl::GetLookupTable()[CharacterSet].Len()) - 1);

    Out_RandomCharacters = FString();

    for (uint64 i = 0; i < Length; ++i)
    {
        Out_RandomCharacters +=
                Impl::GetLookupTable()[CharacterSet][static_cast<int32>(
                    IndexDistribution(GRandomImpl::GetEngine()))];
    }
}

void GRandomImpl::Uuid(FString& Out_RandomUuid)
{
    static boost::uuids::basic_random_generator<boost::random::mt19937>
            Generator(&GetEngine());
    boost::uuids::uuid Uuid = Generator();
    Out_RandomUuid = StringCast<WIDECHAR>(
                boost::uuids::to_string(Uuid).c_str()).Get();
}

GRandomImpl::Impl::CharacterSetMap& GRandomImpl::Impl::GetLookupTable()
{
    static CharacterSetMap LookupTable;

    if (LookupTable.Num() <= 0) {
        LookupTable.Add(EGRandomCharacterSet::Alphabetic,
                        TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"));
        LookupTable.Add(EGRandomCharacterSet::Alphanumeric,
                        TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"));
        LookupTable.Add(EGRandomCharacterSet::Blank,
                        TEXT("\t "));
        LookupTable.Add(EGRandomCharacterSet::Control,
                        TEXT("0123456789"));
        LookupTable.Add(EGRandomCharacterSet::Digits,
                        TEXT("0123456789"));
        LookupTable.Add(EGRandomCharacterSet::Graphical,
                        TEXT("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"));
        LookupTable.Add(EGRandomCharacterSet::Hexadecimal,
                        TEXT("0123456789ABCDEFabcdef"));
        LookupTable.Add(EGRandomCharacterSet::Lower,
                        TEXT("abcdefghijklmnopqrstuvwxyz"));
        LookupTable.Add(EGRandomCharacterSet::Printable,
                        TEXT(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"));
        LookupTable.Add(EGRandomCharacterSet::Punctuation,
                        TEXT("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"));
        LookupTable.Add(EGRandomCharacterSet::Space,
                        TEXT("\t\n\v\f\r "));
        LookupTable.Add(EGRandomCharacterSet::Upper,
                        TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    }

    return LookupTable;
}
