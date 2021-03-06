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
 * Due to conflicting macro definitions between Unreal Engine 4, Microsoft
 * Windows, and included third-party libraries, Windows headers should not be
 * included directely. Instead of including those headers this file must be
 * included where it is required.
 */


#pragma once

#if defined ( _WIN32 ) || defined ( _WIN64 )

#include <GHacks/GUndef_TEXT.h>

THIRD_PARTY_INCLUDES_START

#include <Shlobj.h>
#include <Windows.h>
#include <Winuser.h>

THIRD_PARTY_INCLUDES_END

#undef CopyFile
#undef CreateDirectory
#undef DeleteFile
#undef DrawText
#undef GetObject
#undef InterlockedAdd
#undef InterlockedDecrement
#undef InterlockedExchange
#undef InterlockedIncrement
#undef MoveFile
#undef TEXT
#undef UpdateResource

#include <GHacks/GRestore_TEXT.h>

#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */
