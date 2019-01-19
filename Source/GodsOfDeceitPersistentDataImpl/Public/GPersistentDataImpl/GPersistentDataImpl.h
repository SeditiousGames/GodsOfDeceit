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
 * Provides the low-level implementation for the persistent data module
 */


#pragma once

#include <memory>
#include <string>

#include <Containers/StringConv.h>
#include <Containers/UnrealString.h>
#include <CoreTypes.h>

THIRD_PARTY_INCLUDES_START
#include <cereal/access.hpp>
#include <cereal/types/common.hpp>
#include <cereal/details/helpers.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
THIRD_PARTY_INCLUDES_END

class UWorld;
class GCryptoImpl;
class GDatabaseImpl;

namespace cereal
{

}

class GODSOFDECEITPERSISTENTDATAIMPL_API GPersistentDataImpl
{
public:
    struct Vector3
    {
    public:
        float X;
        float Y;
        float Z;

    private:
        friend class cereal::access;

        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(CEREAL_NVP(X),
                    CEREAL_NVP(Y),
                    CEREAL_NVP(Z));
        }
    };

    struct Rotator
    {
    public:
        float Pitch;
        float Yaw;
        float Roll;

    private:
        friend class cereal::access;

        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(CEREAL_NVP(Pitch),
                    CEREAL_NVP(Yaw),
                    CEREAL_NVP(Roll));
        }
    };

//    struct RecordBase
//    {
//    public:
//        virtual const TCHAR* GetName() const = 0;
//        virtual const TCHAR* GetTableId() const = 0;
//        virtual const TCHAR* GetTableName() const = 0;
//    };

//    struct GameDataRecord : public RecordBase
//    {
//    public:
//        GameDataRecord();
//        virtual ~GameDataRecord();

//    public:
//        const TCHAR* GetName() const override;
//        const TCHAR* GetTableId() const override;
//        const TCHAR* GetTableName() const override;

//    private:
//        friend class cereal::access;
//    };

public:
    static FORCEINLINE GPersistentDataImpl& GetInstance()
    {
        static GPersistentDataImpl Instance;
        return Instance;
    }

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

private:
    GPersistentDataImpl();

public:
//    GCryptoImpl& GetCryptoInstance();
//    GDatabaseImpl& GetDatabaseInstance();

//    GameDataRecord& GetGameData();
};

//CEREAL_REGISTER_TYPE(GPersistentDataImpl::GameDataRecord)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(GPersistentDataImpl::RecordBase, GPersistentDataImpl::GameDataRecord)
