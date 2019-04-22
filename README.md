# Gods of Deceit

First-person shooter game written and developed in C++ and Unreal Engine 4

## Important note about this repository

Unfortunately, due to licensing restrictions you won't be able to build and run the game from this project, as part of the game assets and plugins are not included in this repository. The main reason for this is our usage of third-party assets and plugins from UE4 Marketplace.

Since we believe in the spirit of free/libre open-source software we provide everything we own the copyright for under MIT license in this repository. You should be able to build the game if you pay for the third-party plugins from the marketplace. Nonetheless, you probably won't be able to run the game since you have to also buy the third-party assets from the Unreal Engine marketplace. If you do so, you have to place each purchased item in its own directory inside Content/ThirdParty/${ASSET} according to the Submodule Structure below.

At the moment we don't have any artists in our team, once this gets addressed this issue will go away over time.

This project is brought to you by Seditious Games Studio.

## How to check this repository out?

Since this repository is using nested git submodules it has to be checked out using the following commands:

For HTTPS checkouts:

```
git clone --recursive --jobs 16 https://gitlab.com/SeditiousGames/GodsOfDeceit.git
```

For SSH checkouts:

```
git clone --recursive --jobs 16 git@gitlab.com:SeditiousGames/GodsOfDeceit.git
```

## Submodules Structure

```
GodsOfDeceit
  │
  ├── Content (public repo, hosted at GitLab)
  │     │
  │     └── ThirdParty (private repo, includes UE4 marketplace assets)
  │           │
  │           │── AnimStarterPack (private repo, UE4 marketplace assets)
  │           │── GenericNPCAnimPack (private repo, UE4 marketplace assets)
  │           │── SimpleCity (private repo, UE4 marketplace assets)
  │           │── SimpleFarm (private repo, UE4 marketplace assets)
  │           │── SimpleHouseInteriors (private repo, UE4 marketplace assets)
  │           │── SimpleMilitary (private repo, UE4 marketplace assets)
  │           │── SimpleOffice (private repo, UE4 marketplace assets)
  │           │── SimplePeople (private repo, UE4 marketplace assets)
  │           │── SimplePort (private repo, UE4 marketplace assets)
  │           │── SimplePropsItemsIcons (private repo, UE4 marketplace assets)
  │           │── SimpleRacer (private repo, UE4 marketplace assets)
  │           │── SimpleShopsInterior (private repo, UE4 marketplace assets)
  │           │── SimpleTown (private repo, UE4 marketplace assets)
  │           └── SimpleTrains (private repo, UE4 marketplace assets)
  │
  ├── Plugins (public repo, hosted at GitLab)
  │     │
  │     │── UFSM (private repo, UE4 marketplace plugin)
  │     │
  │     └── VlcMedia (public repo, hosted at GitLab)
  │
  └── ThirdParty (public repo, hosted at GitLab)
```

## Supported Platforms

Intended target platforms for Gods of Deceit are as follows:

* Microsoft Windows 32-bit
* Microsoft Windows 64-bit
* Any 64-bit GNU/Linux distro

Theoretically, it's possible to run Gods of Deceit on the following platforms:

* macOS: Sorry, I don't have any Mac. The only barrier to build it for macOS is the third-party dependencies. If someone with a Mac builds those dependencies -- which is not hard at all -- and modify the build system a bit, it shoud be build and run on any Mac without source code modification. A guide on how to build those dependencies for GNU/Linux resides inside ThirdParty/docs which should be a good starting point for a macOS build.

* Android: In addition to cross-compiling the dependencies (I've done this for Android before and it's not that much complex to figure it out; refer to what I said about macOS), at least the input system requires a rewrite to make it work on Android.

* iOS: Same as Android.

# Third-Party C/C++ Libraries

Gods of Deceit relies on various open-source C/C++ libraries including:

* [Boost C++ Libraries](https://www.boost.org/)
* [cereal](https://uscilab.github.io/cereal/)
* [CppDB](http://cppcms.com/sql/cppdb/)
* [Crypto++](https://www.cryptopp.com/)
* [fmt](http://fmtlib.net/)
* [SQLite](https://www.sqlite.org/)

These dependencies are regularly getting updated and being built for Microsoft Windows - using latest supported msvc by Unreal Engine - and GNU/Linux - using the latest bundled LLVM/Clang toolchain - which reside in the ThirdParty submodule.

If you ever need to build these dependencies yourself, it can be done in an automated manner using a set of Bash (for GNU/Linux) and PowerShell scripts.

On Microsoft Windows (32 and 64 bits):

```
$ cd \path\to\gods\of\deceit\project\directory
$ .\Scripts\thirdparty-build-boost.ps1
$ .\Scripts\thirdparty-build-cereal.ps1
$ .\Scripts\thirdparty-build-cppdb.ps1
$ .\Scripts\thirdparty-build-cryptopp.ps1
$ .\Scripts\thirdparty-build-fmt.ps1
$ .\Scripts\thirdparty-build-sqlite3.ps1
```

On GNU/Linux (64-bit):

```
$ cd /path/to/gods/of/deceit/project/directory
$ bash ./Scripts/thirdparty-build-boost.sh
$ bash ./Scripts/thirdparty-build-cereal.sh
$ bash ./Scripts/thirdparty-build-cppdb.sh
$ bash ./Scripts/thirdparty-build-cryptopp.sh
$ bash ./Scripts/thirdparty-build-fmt.sh
$ bash ./Scripts/thirdparty-build-sqlite3.sh
```

This should automatically downloads, builds, and updates the dependencies according for your chosen platform. Please not that there are building requires various dependencies and manual tweaks inside the build scripts. On Microsoft Windows, this includes [PowerShell](https://docs.microsoft.com/en-us/powershell/scripting/overview), [7zip command-line executable](https://www.7-zip.org/), [GitBash for Windows](https://git-scm.com/), [CMake](https://cmake.org/), [Microsoft Visual Studio 2019](https://visualstudio.microsoft.com/downloads/). GNU/Linux requires [Bash](https://www.gnu.org/software/bash/), [CMake](https://cmake.org/), [Git](https://git-scm.com/), [Ninja](https://ninja-build.org/), and [UE4 LLVM/Clang bundled toolchain](https://docs.unrealengine.com/en-us/Platforms/Linux/NativeToolchain).

Build tweaks can be done by either modifying the common build scripts <code>Scripts/thirdparty-setup-build-environment.ps1</code> (PowerShell), <code>thirdparty-setup-build-environment.sh</code> (Bash), or the build scripts themselves. e.g.:

```powershell
# Scripts/thirdparty-setup-build-environment.ps1

New-Variable -Name "GOD_7zExecutable" -Value "C:\Program Files\7-Zip\7z.exe"
New-Variable -Name "GOD_CMakeExecutable" -Value "C:\CMake\bin\cmake.exe"
New-Variable -Name "GOD_GitExecutable" -Value "C:\Program Files\Git\bin\git.exe"
New-Variable -Name "GOD_VisualStudioBasePath" `
    -Value "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"
New-Variable -Name "GOD_CmakeGenerator" -Value "Visual Studio 16 2019"
New-Variable -Name "GOD_WindowsTargetPlatformVersion" -Value "10.0"
```

```bash
# Scripts/thirdparty-setup-build-environment.sh

export GOD_ARCHITECTURE_TRIPLE="x86_64-unknown-linux-gnu"
export GOD_TOOLCHAIN_ROOT_DIRECTORY="/opt/UnrealEngine/Engine/Extras/ThirdPartyNotUE/SDKs/HostLinux/Linux_x64/v13_clang-7.0.1-centos7/${GOD_ARCHITECTURE_TRIPLE}"
export GOD_TOOLCHAIN_BIN_DIRECTORY="${GOD_TOOLCHAIN_ROOT_DIRECTORY}/bin"
```

```bash
# Scripts/thirdparty-build-boost.sh

BOOST_GIT_CLONE_URL="https://github.com/boostorg/boost.git"
BOOST_VERSION_MAJOR=1
BOOST_VERSION_MINOR=70
BOOST_VERSION_PATCH=0
BOOST_GIT_TAG_TO_BUILD="boost-${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_PATCH}"

ZLIB_GIT_CLONE_URL="https://github.com/madler/zlib.git"
ZLIB_GIT_TAG_TO_BUILD="v1.2.11"

GIT_CLONE_NUMBER_OF_JOBS=16
BOOST_BUILD_NUMBER_OF_JOBS=17
```

## License

MIT License

Copyright (c) 2018 - 2019 Mamadou Babaei<br />
Copyright (c) 2018 - 2019 Seditious Games Studio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
