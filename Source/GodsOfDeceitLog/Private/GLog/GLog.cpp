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


#include "GLog.h"

#include <Containers/Map.h>
#include <Engine/Engine.h>
#include <Logging/LogMacros.h>

DEFINE_LOG_CATEGORY ( Log_AI )
DEFINE_LOG_CATEGORY ( Log_Animation )
DEFINE_LOG_CATEGORY ( Log_Blueprints )
DEFINE_LOG_CATEGORY ( Log_Editor )
DEFINE_LOG_CATEGORY ( Log_Generic )
DEFINE_LOG_CATEGORY ( Log_Input )
DEFINE_LOG_CATEGORY ( Log_Player )
DEFINE_LOG_CATEGORY ( Log_SQL )
DEFINE_LOG_CATEGORY ( Log_Weapon )

static constexpr float ON_SCREEN_LOG_DURATION = 8.0f;

struct GLogCore::StaticImpl
{
public:
    struct VerbosityMapper
    {
        FString Tag;
        FColor Color;

        VerbosityMapper(const FString& tag,
                        const FColor& color);
    };

public:
    TMap<GLogCore::EVerbosity, VerbosityMapper> VerbosityMap;

    bool bInitialized;

public:
    StaticImpl();
};

struct GLogCore::Impl
{
public:
    GLogCore::EVerbosity Verbosity;
    GLogCore::ECategory Category;
    uint64 Key;
    FString File;
    FString Function;
    FString Line;
};

GLogCore::StaticImplDeleter GLogCore::SPimplDeleter;
std::unique_ptr<GLogCore::StaticImpl, GLogCore::StaticImplDeleter> GLogCore::SPimpl =
        std::unique_ptr<GLogCore::StaticImpl, GLogCore::StaticImplDeleter>(
        new GLogCore::StaticImpl{}, GLogCore::SPimplDeleter);

GLogCore::GLogCore(const EVerbosity& Verbosity,
                   const ECategory& Category,
                   const uint64 Key,
                   const std::string& File,
                   const std::string& Function,
                   const int32 Line)
    : Pimpl(std::unique_ptr<Impl, ImplDeleter>(new Impl{}, PimplDeleter)),
      bAnyEntries(false)
{
#if defined ( GOD_LOGGING )
    if (!SPimpl->bInitialized)
    {
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::Fatal,
                    StaticImpl::VerbosityMapper(TEXT("FATAL"), FColor::White));
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::Error,
                    StaticImpl::VerbosityMapper(TEXT("ERROR"), FColor::Red));
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::Warning,
                    StaticImpl::VerbosityMapper(TEXT("WARNING"), FColor::Yellow));
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::Display,
                    StaticImpl::VerbosityMapper(TEXT("DISPLAY"), FColor::Green));
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::Log,
                    StaticImpl::VerbosityMapper(TEXT("LOG"), FColor::Silver));
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::Verbose,
                    StaticImpl::VerbosityMapper(TEXT("VERBOSE"), FColor::Purple));
        SPimpl->VerbosityMap.Add(
                    GLogCore::EVerbosity::VeryVerbose,
                    StaticImpl::VerbosityMapper(TEXT("VERY_VERBOSE"), FColor::Magenta));

        SPimpl->bInitialized = true;
    }

    Pimpl->Verbosity = Verbosity;
    Pimpl->Category = Category;
    Pimpl->Key = Key;
    Pimpl->File = FString(StringCast<TCHAR>(File.c_str()).Get());
    Pimpl->Function = FString(StringCast<TCHAR>(Function.c_str()).Get());
    Pimpl->Line = FString::FromInt(Line);
#endif  /* defined ( GOD_LOGGING ) */
}

GLogCore::~GLogCore()
{
#if defined ( GOD_LOGGING )
    const EVerbosity& Verbosity = Pimpl->Verbosity;
    const ECategory& Category = Pimpl->Category;
    const StaticImpl::VerbosityMapper& VerbosityMapper = SPimpl->VerbosityMap[Verbosity];
    const FString &Tag = VerbosityMapper.Tag;
    const FColor &Color = VerbosityMapper.Color;

    const FString Message(FString::Printf(TEXT("[%s %s %s %s] %s"),
                                          Tag.GetCharArray().GetData(),
                                          Pimpl->File.GetCharArray().GetData(),
                                          Pimpl->Function.GetCharArray().GetData(),
                                          Pimpl->Line.GetCharArray().GetData(),
                                          Buffer.GetCharArray().GetData()));

    /// Generic
    if (Category == ECategory::Generic)
    {
        switch(Verbosity)
        {

        case EVerbosity::Display:
        {
            UE_LOG(Log_Generic, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Generic, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Generic, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Generic, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Generic, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Generic, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Generic, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    /// AI
    if (Category == ECategory::AI)
    {
        switch(Verbosity)
        {
        case EVerbosity::Display:
        {
            UE_LOG(Log_AI, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_AI, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_AI, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_AI, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_AI, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_AI, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_AI, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    /// Animation
    if (Category == ECategory::Animation)
    {
        switch(Verbosity)
        {
        case EVerbosity::Display:
        {
            UE_LOG(Log_Animation, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Animation, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Animation, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Animation, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Animation, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Animation, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Animation, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    /// Blueprints
    if (Category == ECategory::Blueprints)
    {
        switch(Verbosity)
        {
        case EVerbosity::Display:
        {
            UE_LOG(Log_Blueprints, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Blueprints, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Blueprints, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Blueprints, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Blueprints, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Blueprints, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Blueprints, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;
        }

    }

    /// Editor
    if (Category == ECategory::Editor)
    {
        switch(Verbosity)
        {
        case EVerbosity::Display:
        {
            UE_LOG(Log_Editor, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Editor, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Editor, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Editor, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Editor, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Editor, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Editor, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;
        }

    }

    /// Input
    if (Category == ECategory::Input)
    {
        switch(Verbosity)
        {

        case EVerbosity::Display:
        {
            UE_LOG(Log_Input, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Input, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Input, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Input, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Input, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Input, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Input, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    /// Player
    if (Category == ECategory::Player)
    {
        switch(Verbosity)
        {
        case EVerbosity::Display:
        {
            UE_LOG(Log_Player, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Player, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Player, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Player, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Player, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Player, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Player, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    /// SQL
    if (Category == ECategory::SQL)
    {
        switch(Verbosity)
        {

        case EVerbosity::Display:
        {
            UE_LOG(Log_SQL, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_SQL, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_SQL, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_SQL, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_SQL, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_SQL, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_SQL, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    /// Weapon
    if (Category == ECategory::Weapon)
    {
        switch(Verbosity)
        {
        case EVerbosity::Display:
        {
            UE_LOG(Log_Weapon, Display, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Error:
        {
            UE_LOG(Log_Weapon, Error, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Fatal:
        {
            UE_LOG(Log_Weapon, Fatal, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Log:
        {
            UE_LOG(Log_Weapon, Log, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Verbose:
        {
            UE_LOG(Log_Weapon, Verbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::VeryVerbose:
        {
            UE_LOG(Log_Weapon, VeryVerbose, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        case EVerbosity::Warning:
        {
            UE_LOG(Log_Weapon, Warning, TEXT("%s"), Message.GetCharArray().GetData());
        }
            break;

        }
    }

    if (GEngine)
    {
        const FString OnScreenMessage(FString::Printf(TEXT("[%s %s %s] %s"),
                                                      Tag.GetCharArray().GetData(),
                                                      Pimpl->Function.GetCharArray().GetData(),
                                                      Pimpl->Line.GetCharArray().GetData(),
                                                      Buffer.GetCharArray().GetData()));

        GEngine->AddOnScreenDebugMessage(Pimpl->Key, ON_SCREEN_LOG_DURATION, Color, OnScreenMessage);
    }

#endif  /* defined ( GOD_LOGGING ) */
}

GLogCore::StaticImpl::StaticImpl()
    : bInitialized(false)
{

}

GLogCore::StaticImpl::VerbosityMapper::VerbosityMapper(
        const FString& tag,
        const FColor& color)
    : Tag(tag),
      Color(color)
{

}

void GLogCore::StaticImplDeleter::operator()(GLogCore::StaticImpl* Pointer)
{
    delete Pointer;
}

void GLogCore::ImplDeleter::operator()(GLogCore::Impl* Pointer)
{
    delete Pointer;
}
