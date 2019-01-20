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
 * SQL connectivity layer with support for SQLite3
 */

#define  GDATABASE_USE_CONNECTION_POOLING       0

#include "GDatabase.h"

#include <string>
#include <unordered_map>
#include <cstddef>

#include <Containers/StringConv.h>
#include <Misc/AssertionMacros.h>

THIRD_PARTY_INCLUDES_START
#include <cppdb/backend.h>
#include <cppdb/driver_manager.h>
#if GDATABASE_USE_CONNECTION_POOLING
THIRD_PARTY_INCLUDES_START
#include <cppdb/pool.h>
THIRD_PARTY_INCLUDES_END
#endif  /* GDATABASE_USE_CONNECTION_POOLING */
#include <cppdb/utils.h>
#include <fmt/format.h>
#include <sqlite3.h>
THIRD_PARTY_INCLUDES_END

#include <GHacks/GInclude_Windows.h>
#include <GUtilsImpl/GStringUtilsImpl.h>

#define  GDATABASE_ERROR_DIALOG_TITLE                 "Database Error"
#define  GDATABASE_UNKNOWN_ERROR                      "GDatabase: unknown error!"
#define  GDATABASE_CONNECTION_NOT_OPENED_ERROR        "GDatabase: database connection has not been opened!"
#define  GDATABASE_CONNECTION_ALREADY_OPENED_ERROR    "GDatabase: database connection is opened alreay!"
#define  GDATABASE_CONNECTION_OPEN_FAILED_ERROR       "GDatabase: failed to open database connection!"
#define  GDATABASE_CONNECTION_ALREADY_CLOSED_ERROR    "GDatabase: database connection is closed alreay!"
#define  GDATABASE_CONNECTION_CLOSE_FAILED_ERROR      "GDatabase: failed to close database connection!"

extern "C"
{
    cppdb::backend::connection* cppdb_sqlite3_get_connection(
                cppdb::connection_info const&);
}

struct Config
{
    bool bWALMode;

    void operator()(cppdb::session& Sql) const
    {
        if (bWALMode) {
            Sql << "PRAGMA journal_mode=WAL;" << cppdb::exec;
        }
    }

    Config(bool bInWALMode) : bWALMode(bInWALMode)
    {

    }
};

GDatabaseImpl::SessionGuard::SessionGuard(
        GDatabaseImpl& InInstance)
    : Instance(InInstance)
{

}

GDatabaseImpl::SessionGuard::~SessionGuard()
{
    if (Instance.IsSessionOpen())
    {
        Instance.CloseSession();
    }
}

struct GDatabaseImpl::Impl
{
public:
    typedef std::unordered_map<FString, FString,
        GStringUtilsImpl::FStringKeyHasher, GStringUtilsImpl::FStringKeyEqual>
        TableNamesHashTable;

    typedef std::unordered_map<FString, FString,
        GStringUtilsImpl::FStringKeyHasher, GStringUtilsImpl::FStringKeyEqual>
        TableFieldsHashTable;

    Impl(const FString& databasePath, bool bWALMode);
    ~Impl();

public:
    cppdb::connection_info Connection;

#if GDATABASE_USE_CONNECTION_POOLING
    cppdb::pool::pointer Pool;
#endif  /* GDATABASE_USE_CONNECTION_POOLING */

    cppdb::session Sql;

    TableNamesHashTable TableNames;
    TableFieldsHashTable TableFields;
};

bool GDatabaseImpl::bSqlite3DriverLoaded = false;

void GDatabaseImpl::LoadSqlite3Driver()
{
    try
    {
        if (!GDatabaseImpl::IsSqlite3DriverLoaded())
        {
            GDatabaseImpl::bSqlite3DriverLoaded = true;
            cppdb::driver_manager::instance()
                    .install_driver(
                        "sqlite3",
                        new cppdb::backend::static_driver(
                            cppdb_sqlite3_get_connection));
        }
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

bool GDatabaseImpl::Sqlite3Vacuum(const FString& DatabasePath)
{
    sqlite3* Database;

    int ReturnCode = sqlite3_open(StringCast<ANSICHAR>(*DatabasePath).Get(),
                                  &Database);

    if (!ReturnCode)
    {
        sqlite3_exec(Database, "VACUUM;", 0, 0, 0);
        return true;
    }

    return false;
}

GDatabaseImpl::GDatabaseImpl(const FString& DatabasePath, bool bWALMode)
    : Pimpl(std::make_unique<GDatabaseImpl::Impl>(DatabasePath, bWALMode))
{

}

GDatabaseImpl::~GDatabaseImpl()
{

}

bool GDatabaseImpl::IsSessionOpen()
{
    return Pimpl->Sql.is_open();
}

bool GDatabaseImpl::OpenSession()
{
    try
    {
        if (!Pimpl->Sql.is_open())
        {
            Pimpl->Sql.open(Pimpl->Connection);
        }
        else
        {
#if defined ( _WIN32 ) || defined ( _WIN64 )
            MessageBoxA(0, GDATABASE_CONNECTION_ALREADY_OPENED_ERROR,
                        GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
            checkf(false, TEXT("%s"),
                   StringCast<WIDECHAR>(
                       GDATABASE_CONNECTION_ALREADY_OPENED_ERROR).Get());
        }

        return true;
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }

    return false;
}

bool GDatabaseImpl::CloseSession()
{
    try {
        if (Pimpl->Sql.is_open())
        {
            Pimpl->Sql.close();

            return true;
        }
        else
        {
#if defined ( _WIN32 ) || defined ( _WIN64 )
            MessageBoxA(0, GDATABASE_CONNECTION_ALREADY_CLOSED_ERROR,
                        GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
            checkf(false, TEXT("%s"),
                   StringCast<WIDECHAR>(
                       GDATABASE_CONNECTION_ALREADY_CLOSED_ERROR).Get());
        }
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }

    return false;
}

bool GDatabaseImpl::Initialize()
{
    try {
        GDatabaseImpl::SessionGuard SessionGuard(*this);
        (void)SessionGuard;

        bool bOpened = OpenSession();
        if (!bOpened)
        {
#if defined ( _WIN32 ) || defined ( _WIN64 )
            MessageBoxA(0, GDATABASE_CONNECTION_OPEN_FAILED_ERROR,
                        GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
            checkf(false, TEXT("%s"),
                   StringCast<WIDECHAR>(
                       GDATABASE_CONNECTION_OPEN_FAILED_ERROR).Get());

            return false;
        }

        cppdb::transaction TransactionGuard(Sql());

        for (const auto& TableName : Pimpl->TableNames)
        {
            CreateTable(TableName.first);
        }

        TransactionGuard.commit();

        bool bClosed = CloseSession();
        if (!bClosed)
        {
#if defined ( _WIN32 ) || defined ( _WIN64 )
            MessageBoxA(0, GDATABASE_CONNECTION_CLOSE_FAILED_ERROR,
                        GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
            checkf(false, TEXT("%s"),
                   StringCast<WIDECHAR>(
                       GDATABASE_CONNECTION_CLOSE_FAILED_ERROR).Get());

            return false;
        }

        return true;
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }

    return false;
}

void GDatabaseImpl::RegisterTable(
        const FString& id,
        const FString& name,
        const FString& fields)
{
    Pimpl->TableNames[id] = name;
    Pimpl->TableFields[id] = fields;
}

FString GDatabaseImpl::GetTableName(const FString& Id) const
{
    if (Pimpl->TableNames.find(Id) != Pimpl->TableNames.end())
    {
        return Pimpl->TableNames[Id];
    }

    checkf(false, TEXT("%s"),
           StringCast<WIDECHAR>(
               fmt::format("{0} table has not been registered!",
                           StringCast<ANSICHAR>(*Id).Get()).c_str()).Get());

    return TEXT("{?}");
}

FString GDatabaseImpl::GetTableFields(const FString& Id) const
{
    if (Pimpl->TableFields.find(Id) != Pimpl->TableFields.end())
    {
        return Pimpl->TableFields[Id];
    }

    checkf(false, TEXT("%s"),
           StringCast<WIDECHAR>(
               fmt::format("{0} table fields have not been registered!",
                           StringCast<ANSICHAR>(*Id).Get()).c_str()).Get());

    return TEXT("{?}");
}

void GDatabaseImpl::SetTableName(const FString& Id, const FString& NewName)
{
    auto Iterator = Pimpl->TableNames.find(Id);
    if (Iterator != Pimpl->TableNames.end())
    {
        Iterator->second = NewName;
        return;
    }

    checkf(false, TEXT("%s"),
           StringCast<WIDECHAR>(
               fmt::format("{0} has not been registered!",
                           StringCast<ANSICHAR>(*Id).Get()).c_str()).Get());
}

void GDatabaseImpl::SetTableFields(const FString& Id, const FString& Fields)
{
    auto Iterator = Pimpl->TableFields.find(Id);
    if (Iterator != Pimpl->TableFields.end()) {
        Iterator->second = Fields;
        return;
    }

    checkf(false, TEXT("%s"),
           StringCast<WIDECHAR>(
               fmt::format("{0} has not been registered!",
                           StringCast<ANSICHAR>(*Id).Get()).c_str()).Get());
}

cppdb::session& GDatabaseImpl::Sql()
{
    bool bIsOpen = Pimpl->Sql.is_open();

#if defined ( _WIN32 ) || defined ( _WIN64 )
    if (!bIsOpen)
    {
        MessageBoxA(0, GDATABASE_CONNECTION_NOT_OPENED_ERROR,
                    GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
    }
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
    checkf(bIsOpen, TEXT("%s"),
           StringCast<WIDECHAR>(GDATABASE_CONNECTION_NOT_OPENED_ERROR).Get());

    return Pimpl->Sql;
}

void GDatabaseImpl::CreateTable(const FString& Id)
{
    try
    {
        std::string Query(
                    fmt::format(
                        "CREATE TABLE IF NOT EXISTS [{0}] ( {1} );",
                        StringCast<ANSICHAR>(
                            *GetTableName(Id)).Get(),
                        StringCast<ANSICHAR>(
                            *GetTableFields(Id)).Get()));

        Sql() << Query << cppdb::exec;
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

void GDatabaseImpl::DropTable(const FString& Id)
{
    try
    {
        std::string Query(
                    fmt::format(
                        "DROP TABLE IF EXISTS [{0}];",
                        StringCast<ANSICHAR>(*GetTableName(Id)).Get()));

        Sql() << Query << cppdb::exec;
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

void GDatabaseImpl::RenameTable(const FString& Id, const FString& NewName)
{
    try
    {
        auto Iterator = Pimpl->TableNames.find(Id);
        if (Iterator != Pimpl->TableNames.end())
        {
            std::string Query(
                        fmt::format(
                            "ALTER TABLE [{0}] RENAME TO [{1}];",
                            StringCast<ANSICHAR>(*GetTableName(Id)).Get(),
                            StringCast<ANSICHAR>(*NewName).Get()));

            Sql() << Query << cppdb::exec;

            Iterator->second = NewName;
        }
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...) {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

void GDatabaseImpl::Insert(
        const FString& Id,
        const FString& Fields,
        const std::initializer_list<FString>& Args)
{
    try
    {
        FString PreparedArgs;
        for (std::size_t i = 0; i < Args.size(); ++i)
        {
            if (i != 0) {
                PreparedArgs += TEXT(", ");
            }

            PreparedArgs += TEXT("?");
        }

        std::string Query(
                    fmt::format(
                        "INSERT INTO [{0}] ( {1} ) VALUES ( {2} );",
                        StringCast<ANSICHAR>(*GetTableName(Id)).Get(),
                        StringCast<ANSICHAR>(*Fields).Get(),
                        StringCast<ANSICHAR>(*PreparedArgs).Get()));

        cppdb::statement Statement = Sql() << Query;

        bool bFirstLogStringArg = true;
        FString ArgsLogString;

        for(const FString& Arg : Args)
        {
            Statement.bind(StringCast<ANSICHAR>(*Arg).Get());
        }

        Statement.exec();
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

void GDatabaseImpl::Update(
        const FString& Id,
        const FString& Where,
        const FString& Value,
        const FString& Set,
        const std::initializer_list<FString>& Args)
{
    try
    {
        std::string Query(
                    fmt::format(
                        "UPDATE ONLY [{0}] SET {1} WHERE {2} = ?;",
                        StringCast<ANSICHAR>(*GetTableName(Id)).Get(),
                        StringCast<ANSICHAR>(*Set).Get(),
                        StringCast<ANSICHAR>(*Where).Get()));

        cppdb::statement Statement = Sql() << Query;

        for(const FString& Arg : Args)
        {
            Statement.bind(StringCast<ANSICHAR>(*Arg).Get());
        }

        Statement.exec();
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

void GDatabaseImpl::Delete(
        const FString& Id,
        const FString& Where,
        const FString& Value)
{
    try
    {
        std::string Query(
                    fmt::format(
                        "DELETE FROM ONLY [{0}] WHERE {1} = ?;",
                        StringCast<ANSICHAR>(*GetTableName(Id)).Get(),
                        StringCast<ANSICHAR>(*Where).Get()));

        Sql() << Query
              << StringCast<ANSICHAR>(*Value).Get()
              << cppdb::exec;
    }

    catch (const fmt::v5::format_error& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false,TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

GDatabaseImpl::Impl::Impl(
        const FString& DatabasePath,
        bool bWALMode)
    : Connection(fmt::format(
                     "sqlite3:db={0};",
                     StringCast<ANSICHAR>(*DatabasePath).Get())),
      #if GDATABASE_USE_CONNECTION_POOLING
      Pool(cppdb::pool::create(Connection)),
      #endif  /* GDATABASE_USE_CONNECTION_POOLING */
      Sql(
          #if GDATABASE_USE_CONNECTION_POOLING
          Pool->open(),
          #else
          Connection,
          #endif  /* GDATABASE_USE_CONNECTION_POOLING */
          Config(bWALMode))
{
    try
    {
        if (Sql.is_open())
        {
            Sql.close();
        }
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}

GDatabaseImpl::Impl::~Impl()
{
    try
    {
        if (Sql.is_open())
        {
            Sql.close();
        }
    }

    catch (const std::exception& Exception)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, Exception.what(), GDATABASE_ERROR_DIALOG_TITLE, MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(Exception.what()).Get());
    }

    catch (...)
    {
#if defined ( _WIN32 ) || defined ( _WIN64 )
        MessageBoxA(0, GDATABASE_UNKNOWN_ERROR, GDATABASE_ERROR_DIALOG_TITLE,
                    MB_OK);
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
        checkf(false, TEXT("%s"),
               StringCast<WIDECHAR>(GDATABASE_UNKNOWN_ERROR).Get());
    }
}
