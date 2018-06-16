#!/usr/bin/env bash

#  (The MIT License)
#
#  Copyright (c) 2018 Mohammad S. Babaei
#  Copyright (c) 2018 Khavaran67
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.


function cleanUp()
{
    echo ""
    echo "WARNING: RUNNING THIS SCRIPT HAS DESTRUCTIVE EFFECTS"
    echo "ON THIS REPO AND ITS SUBMODULES!"
    echo ""
    echo "MAKE A BACKUP FIRST, BEFORE YOU PROCEED ANY FURTHER!"
    echo ""
    echo "This script runs the following set of commands inside the root of this repoistory:"
    echo ""
    echo "    $ git reset --hard"
    echo "    $ git submodule foreach --recursive git reset --hard"
    echo "    $ git clean -dfx"
    echo "    $ git submodule foreach --recursive git clean -dfx"
    echo "    $ git submodule update --init --recursive"
    echo ""

    read -p "Are you sure? " -n 1 -r

    echo ""
    echo ""

    if [[ ! $REPLY =~ ^[Yy]$ ]] ;
    then
        echo "Aborted!"

        [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1
    fi

    echo "Running ==>  git reset --hard"
    echo ""
    git reset --hard
    echo ""

    echo "Running ==>  git submodule foreach --recursive git reset --hard"
    echo ""
    git submodule foreach --recursive git reset --hard
    echo ""

    echo "Running ==>  git clean -dfx"
    echo ""
    git clean -dfx
    echo ""

    echo "Running ==>  git submodule foreach --recursive git clean -dfx"
    echo ""
    git submodule foreach --recursive git clean -dfx
    echo ""

    echo "Running ==>  git submodule update --init --recursive"
    echo ""
    git submodule update --init --recursive
    echo ""

    echo "Done!"
    echo ""
}

PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`

cd "${PROJECT_DIRECTORY}" \
    && cleanUp
