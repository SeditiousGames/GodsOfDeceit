#!/usr/bin/env bash

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
