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
 * SQL connectivity layer with support for SQLite3
 */


#pragma once

#include <memory>

#include <Containers/UnrealString.h>
#include <CoreTypes.h>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <cppdb/frontend.h>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

namespace cppdb
{
    class session;
}

class GODSOFDECEITPERSISTENTDATAIMPL_API GDatabaseImpl
{
public:
    class SessionGuard
    {
    private:
        GDatabaseImpl& Instance;

    public:
        SessionGuard(GDatabaseImpl& InInstance);
        ~SessionGuard();
    };

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

private:
    static bool bSqlite3DriverLoaded;

public:
    static inline bool IsSqlite3DriverLoaded()
    {
        return bSqlite3DriverLoaded;
    }

    static void LoadSqlite3Driver();

    static bool Sqlite3Vacuum(const FString& DatabasePath);

public:
    explicit GDatabaseImpl(const FString& DatabasePath,
                           bool bWALMode = false);
    virtual ~GDatabaseImpl();

public:
    bool IsSessionOpen();
    bool OpenSession();
    bool CloseSession();

    bool Initialize();

    void RegisterTable(const FString& Id,
                       const FString& Name,
                       const FString& Fields);
    FString GetTableName(const FString& Id) const;
    FString GetTableFields(const FString& Id) const;
    void SetTableName(const FString& Id, const FString& NewName);
    void SetTableFields(const FString& Id, const FString& Fields);

    cppdb::session& Sql();

    void CreateTable(const FString& Id);
    void DropTable(const FString& Id);
    void RenameTable(const FString& Id, const FString& NewName);

    void Insert(const FString& Id,
                const FString& Fields,
                const std::initializer_list<FString>& Args);
    void Update(const FString& Id,
                const FString& Where,
                const FString& Value,
                const FString& Set,
                const std::initializer_list<FString>& Args);
    void Delete(const FString& Id,
                const FString& Where,
                const FString& Value);
};
