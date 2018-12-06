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
 * Copyright (c) 2018 Seditious Games Studio
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
 * Provides an abstraction layer on top of platform-specific API.
 */


#include "GSystem.h"

#include <GInterop/GIC_EGSystemDirectory.h>
#include <GInterop/GIC_FString.h>
#include <GPlatformImpl/GExportedFunctions.h>

FString GSystem::GetDirectorySeparatorChar()
{
    GIC_FString InteropContainer;

    System_GetDirectorySeparatorChar(&InteropContainer);

    return InteropContainer.String;
}

FString GSystem::GetExecutablePath()
{
    GIC_FString InteropContainer;

    System_GetExecutablePath(&InteropContainer);

    return InteropContainer.String;
}

FString GSystem::GetCurrentPath()
{
    GIC_FString InteropContainer;

    System_GetCurrentPath(&InteropContainer);

    return InteropContainer.String;
}

FString GSystem::GetSystemDirectoryPath(
        const EGSystemDirectory Directory)
{
    GIC_EGSystemDirectory DirectoryInteropContainer;
    DirectoryInteropContainer.Directory = Directory;

    GIC_FString PathInteropContainer;

    System_GetSystemDirectoryPath(&DirectoryInteropContainer, &PathInteropContainer);

    return PathInteropContainer.String;
}
