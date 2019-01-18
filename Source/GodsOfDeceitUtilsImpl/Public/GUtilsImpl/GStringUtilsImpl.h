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
 * copies of the Softwrrare, and to permit persons to whom the Software is
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
 * Provides extra string functionalities in order to facilitate FString usage
 */


#pragma once

#include <unordered_map>
#include <cstddef>

#include <Containers/UnrealString.h>
#include <CoreTypes.h>

class GODSOFDECEITUTILSIMPL_API GStringUtilsImpl
{
public:
public:
    template <typename TYPE>
    struct Hasher
    {
        std::size_t operator()(const TYPE& Type) const
        {
            return std::hash<uint8>()(static_cast<uint8>(Type));
        }
    };

    struct FStringKeyHasher
    {
        std::size_t operator()(const FString& Key) const
        {
            std::size_t Hash = 0;

            for(int32 i = 0; i < Key.Len(); ++i) {
                Hash += (71 * Hash + Key[i]) % 5;
            }

            return Hash;
        }
    };

    struct FStringKeyEqual
    {
        bool operator()(const FString& LeftHandSide,
                        const FString& RightHandSide) const
        {
            return !(LeftHandSide.Compare(RightHandSide));
        }
    };

    template <typename TYPE>
    struct HashMapper
    {
        typedef std::unordered_map<TYPE, std::string, Hasher<TYPE>> HashToString;
        typedef std::unordered_map<std::string, TYPE> HashToEnumClass;
    };

    template <typename TYPE>
    static constexpr typename std::underlying_type<TYPE>::type ToUnderlyingType(
            const TYPE Enum) {
        return static_cast<typename std::underlying_type<TYPE>::type>(Enum);
    }

    static constexpr bool StringsEqual(const char* String1,
                                       const char* String2)
    {
        /* C++11 */
        return *String1 == *String2
                && (*String1 == '\0'
                    || StringsEqual(String1 + 1, String2 + 1));

        /* C++14/17
        while (*String1 || *String2) {
            if (*String1++ != *String2++) {
                return false;
            }
        }
        return true;
        */
    }
};
