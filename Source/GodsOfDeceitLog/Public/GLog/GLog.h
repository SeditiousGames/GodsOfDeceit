/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 Mohammad S. Babaei
 * Copyright (c) 2018 Khavaran67
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
 * A generic logging utility.
 */


#pragma once

#include <memory>
#include <string>

#include <cstddef>
#include <cstdio>

#include <Containers/StringConv.h>
#include <Containers/UnrealString.h>
#include <CoreTypes.h>
#include <GameFramework/Actor.h>
#include <Logging/LogVerbosity.h>
#include <Math/Rotator.h>
#include <Math/Vector.h>
#include <UObject/NameTypes.h>
#include <UObject/ObjectMacros.h>

DECLARE_LOG_CATEGORY_EXTERN ( Log_AI, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Animation, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Blueprints, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Editor, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Generic, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Input, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Player, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_SQL, All, All );
DECLARE_LOG_CATEGORY_EXTERN ( Log_Weapon, All, All );

static constexpr uint64 GLOG_KEY_INFINITE = static_cast<uint64>(-1);
static constexpr uint64 GLOG_KEY_AI = static_cast<uint64>(800);
static constexpr uint64 GLOG_KEY_ANIMATION = static_cast<uint64>(500);
static constexpr uint64 GLOG_KEY_BLUEPRINTS = static_cast<uint64>(600);
static constexpr uint64 GLOG_KEY_EDITOR = static_cast<uint64>(200);
static constexpr uint64 GLOG_KEY_GENERIC = static_cast<uint64>(100);
static constexpr uint64 GLOG_KEY_INPUT = static_cast<uint64>(400);
static constexpr uint64 GLOG_KEY_PLAYER = static_cast<uint64>(700);
static constexpr uint64 GLOG_KEY_SQL = static_cast<uint64>(300);
static constexpr uint64 GLOG_KEY_WEAPON = static_cast<uint64>(600);

template<typename TYPE>
struct GLogString
{
    TYPE T1;
    FString T2;
    static_assert(std::is_same<decltype(T1), decltype(T2)>::value,
                  "Error: you are missing a template specialization!");
};

template<typename TYPE, size_t LENGTH>
struct GLogString<TYPE[LENGTH]>
{
    TYPE T1;
    FString T2;
    static_assert(std::is_same<decltype(T1), decltype(T2)>::value,
                  "Error: you are missing a template specialization!");
};

template <>
struct GLogString<const AActor*>
{
    static void Format(const AActor* Actor, FString& Out_String)
    {
        checkf(Actor, TEXT("FATAL: cannot log NULL actor object!"));

        Out_String = FString::Printf(TEXT("%s"), Actor->GetName().GetCharArray().GetData());
    }
};

template <>
struct GLogString<AActor*>
{
    static void Format(const AActor* Actor, FString& Out_String)
    {
        checkf(Actor, TEXT("FATAL: cannot log NULL actor object!"));

        Out_String = FString::Printf(TEXT("%s"), Actor->GetName().GetCharArray().GetData());
    }
};

template <>
struct GLogString<const bool>
{
    static void Format(const bool Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), (Value ? TEXT("True") : TEXT("False")));
    }
};

template <>
struct GLogString<bool>
{
    static void Format(const bool Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), (Value ? TEXT("True") : TEXT("False")));
    }
};

template< std::size_t LENGTH>
struct GLogString<const char[LENGTH]>
{
    static void Format(const char* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

template< std::size_t LENGTH>
struct GLogString<char[LENGTH]>
{
    static void Format(const char* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

template <>
struct GLogString<const char*>
{
    static void Format(const char* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

template <>
struct GLogString<char*>
{
    static void Format(const char* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

#if defined ( __linux__ )

template< std::size_t LENGTH>
struct GLogString<const char16_t[LENGTH]>
{
    static void Format(const char16_t* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

template< std::size_t LENGTH>
struct GLogString<char16_t[LENGTH]>
{
    static void Format(const char16_t* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

template <>
struct GLogString<const char16_t*>
{
    static void Format(const char16_t* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

template <>
struct GLogString<char16_t*>
{
    static void Format(const char16_t* Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value).Get());
    }
};

#endif  /* defined ( __linux__ ) */

template <>
struct GLogString<const double>
{
    static void Format(const double Value, FString& Out_String)
    {
        char Buffer[100];
        std::snprintf(Buffer, sizeof(Buffer), "%f", Value);

        std::string String(Buffer);

        Out_String = FString(StringCast<TCHAR>(String.c_str()).Get());
    }
};

template <>
struct GLogString<double>
{
    static void Format(const double Value, FString& Out_String)
    {
        char Buffer[100];
        std::snprintf(Buffer, sizeof(Buffer), "%f", Value);

        std::string String(Buffer);

        Out_String = FString(StringCast<TCHAR>(String.c_str()).Get());
    }
};

template <>
struct GLogString<const float>
{
    static void Format(const float Value, FString& Out_String)
    {
        Out_String = FString::SanitizeFloat(static_cast<double>(Value), 1);
    }
};

template <>
struct GLogString<float> {
    static void Format(const float Value, FString& Out_String)
    {
        Out_String = FString::SanitizeFloat(static_cast<double>(Value), 1);
    }
};

template <>
struct GLogString<const FName>
{
    static void Format(const FName& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.ToString().GetCharArray().GetData());
    }
};

template <>
struct GLogString<FName>
{
    static void Format(const FName& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.ToString().GetCharArray().GetData());
    }
};

template <>
struct GLogString<const FRotator>
{
    static void Format(const FRotator& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.ToString().GetCharArray().GetData());
    }
};

template <>
struct GLogString<FRotator>
{
    static void Format(const FRotator& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.ToString().GetCharArray().GetData());
    }
};

template <>
struct GLogString<const FString>
{
    static void Format(const FString& Value, FString& Out_String)
    {
        Out_String = Value;
    }
};

template <>
struct GLogString<FString>
{
    static void Format(const FString& Value, FString& Out_String)
    {
        Out_String = Value;
    }
};

template <>
struct GLogString<const FVector>
{
    static void Format(const FVector& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.ToString().GetCharArray().GetData());
    }
};

template <>
struct GLogString<FVector>
{
    static void Format(const FVector& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.ToString().GetCharArray().GetData());
    }
};

template <>
struct GLogString<const int8>
{
    static void Format(const int8 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<int8>
{
    static void Format(const int8 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const int16>
{
    static void Format(const int16 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<int16>
{
    static void Format(const int16 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const int32>
{
    static void Format(const int32 Value, FString& Out_String)
    {
        Out_String = FString::FromInt(Value);
    }
};

template <>
struct GLogString<int32>
{
    static void Format(const int32 Value, FString& Out_String)
    {
        Out_String = FString::FromInt(Value);
    }
};

template <>
struct GLogString<const int64>
{
    static void Format(const int64 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<int64>
{
    static void Format(const int64 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const long double>
{
    static void Format(const long double Value, FString& Out_String)
    {
        char Buffer[100];
        std::snprintf(Buffer, sizeof(Buffer), "%Lf", Value);

        std::string String(Buffer);

        Out_String = FString(StringCast<TCHAR>(String.c_str()).Get());
    }
};

template <>
struct GLogString<long double>
{
    static void Format(const long double Value, FString& Out_String)
    {
        char Buffer[100];
        std::snprintf(Buffer, sizeof(Buffer), "%Lf", Value);

        std::string String(Buffer);

        Out_String = FString(StringCast<TCHAR>(String.c_str()).Get());
    }
};

#if defined ( __linux__ )
template <>
struct GLogString<const std::size_t>
{
    static void Format(const std::size_t Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};
#endif  /* defined ( __linux__ ) */

#if defined ( __linux__ )
template <>
struct GLogString<std::size_t>
{
    static void Format(const std::size_t Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};
#endif  /* defined ( __linux__ ) */

template <>
struct GLogString<const uint8>
{
    static void Format(const int8 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<uint8>
{
    static void Format(const int8 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const uint16>
{
    static void Format(const int16 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<uint16>
{
    static void Format(const int16 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const uint32>
{
    static void Format(const int32 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<uint32>
{
    static void Format(const int32 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const uint64>
{
    static void Format(const int64 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<uint64>
{
    static void Format(const int64 Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%d"), Value);
    }
};

template <>
struct GLogString<const std::string>
{
    static void Format(const std::string& Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value.c_str()).Get());
    }
};

template <>
struct GLogString<std::string>
{
    static void Format(const std::string& Value, FString& Out_String)
    {
        Out_String = FString(StringCast<TCHAR>(Value.c_str()).Get());
    }
};

template<std::size_t LENGTH>
struct GLogString<const wchar_t[LENGTH]>
{
    static void Format(const wchar_t* Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value);
    }
};

template<std::size_t LENGTH>
struct GLogString<wchar_t[LENGTH]>
{
    static void Format(const wchar_t* Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value);
    }
};

template <>
struct GLogString<const wchar_t*>
{
    static void Format(const wchar_t* Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value);
    }
};

template <>
struct GLogString<wchar_t*>
{
    static void Format(const wchar_t* Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value);
    }
};

template <>
struct GLogString<const std::wstring>
{
    static void Format(const std::wstring& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.c_str());
    }
};

template <>
struct GLogString<std::wstring>
{
    static void Format(const std::wstring& Value, FString& Out_String)
    {
        Out_String = FString::Printf(TEXT("%s"), Value.c_str());
    }
};

class GODSOFDECEITLOG_API GLogCore
{
public:
    enum class EVerbosity : uint8
    {
        /** Always prints s fatal error to console (and log file) and crashes (even if logging is disabled) */
        Fatal,

        /**
         * Prints an error to console (and log file).
         * Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
         */
        Error,

        /**
         * Prints a warning to console (and log file).
         * Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
         */
        Warning,

        /** Prints a message to console (and log file) */
        Display,

        /** Prints a message to a log file (does not print to console) */
        Log,

        /**
         * Prints a verbose message to a log file (if Verbose logging is enabled for the given category,
         * usually used for detailed logging)
         */
        Verbose,

        /**
         * Prints a verbose message to a log file (if VeryVerbose logging is enabled,
         * usually used for detailed logging that would otherwise spam output)
         */
        VeryVerbose,
    };

    enum class ECategory
    {
        AI,
        Animation,
        Blueprints,
        Editor,
        Generic,
        Input,
        Player,
        SQL,
        Weapon
    };

private:
    struct StaticImpl;
    struct StaticImplDeleter
    {
        void operator()(StaticImpl* Pointer);
    };
    static std::unique_ptr<StaticImpl, StaticImplDeleter> SPimpl;
    static StaticImplDeleter SPimplDeleter;

    struct Impl;
    struct ImplDeleter
    {
        void operator()(Impl* Pointer);
    };
    std::unique_ptr<Impl, ImplDeleter> Pimpl;
    ImplDeleter PimplDeleter;

private:
    FString Buffer;
    bool bAnyEntries;

public:
    GLogCore(const EVerbosity& Verbosity,
         const ECategory& Category,
         const uint64 Key,
         const std::string& File,
         const std::string& Function,
         const int32 Line);
    virtual ~GLogCore();

public:
    template <typename TYPE>
    GLogCore& operator,(const TYPE& Argument)
    {
        if (bAnyEntries)
        {
            Buffer += FString(TEXT(" • "));
        }

        FString FormattedArgument;
        GLogString<TYPE>::Format(Argument, FormattedArgument);
        Buffer += FormattedArgument;
        bAnyEntries = true;

        return *this;
    }
};

/* Generic */

#define GLOG_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::Generic, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Generic, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* AI */

#define GLOG_AI_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::AI, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_AI( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::AI, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* Animatoin */

#define GLOG_ANIMATION_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::Animation, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_ANIMATION( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Animation, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* Blueprints */

#define GLOG_BLUEPRINTS_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::Blueprints, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::Blueprints, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::Blueprints, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::Blueprints, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Blueprints, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::Blueprint, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::Blueprints, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_BLUEPRINTS( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Blueprints, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* Editor */

#define GLOG_EDITOR_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::Editor, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_EDITOR( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Editor, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* Input */

#define GLOG_INPUT_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::Input, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_INPUT( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Input, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* SQL */

#define GLOG_SQL_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::SQL, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_SQL( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::SQL, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

/* Weapon */

#define GLOG_WEAPON_FATAL( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Fatal, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON_ERROR( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Error, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON_WARNING( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Warning, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON_DISPLAY( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Display, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON_LOG( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::Verbose, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON_VERY_VERBOSE( Key, ... )  \
    (GLogCore(GLogCore::EVerbosity::VeryVerbose, GLogCore::ECategory::Weapon, Key, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define GLOG_WEAPON( ... )  \
    (GLogCore(GLogCore::EVerbosity::Log, GLogCore::ECategory::Weapon, GLOG_KEY_INFINITE, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;
