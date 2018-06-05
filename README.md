# Gods of Deceit

First-person shooter game written and developed in C++ and Unreal Engine 4

## Importat note about this repository

Unfortunately, due to licensing restrictions you won't be able to build and run the game from this project, as part of the game assets and plugins are not included in this repository. The main reason for this is our usage of third-party assets and plugins from UE4 Marketplace.

Since we believe in the spirit of free/libre open-source software we provide everything we own the copyright for under MIT license in this repository. You should be able to build the game if you pay for the third-party plugins from the marketplace. Nonetheless, you probably won't be able to run the game since you have to reproduce the levels and art assets on your own using the assets from the marketplace. Still, feel free to build a new game using the provided source code with your own art assets.

At the moment we don't have any artists in our time, once this gets addressed this issue will go away over time.

This project is brought to you by Khavaran67.

## How to check this repository out?

Since this repository is using nested git submodules it has to be checked out using the following commands:

For HTTPS checkouts:

```
git clone --recursive --jobs 16 https://gitlab.com/Khavaran67/GodsOfDeceit.git
```

For SSH checkouts:

```
git clone --recursive --jobs 16 git@gitlab.com:Khavaran67/GodsOfDeceit.git
```

## Submodule Structure

```
GodsOfDeceit
  │
  ├── Content (public repo)
  │     │
  │     └── ThirdParty (private repo, includes UE4 marketplace assets)
  │
  ├── Plugins (public repo)
  │     │
  │     └── UFSM (private repo, UE4 marketplace plugin)
  │
  └── ThirdParty (public repo)
```

# License

MIT License

Copyright (c) 2018 Khavaran67

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
