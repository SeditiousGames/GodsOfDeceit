#!/usr/bin/env bash

#  (The MIT License)
#
#  Copyright (c) 2018 - 2019 Mohammad S. Babaei
#  Copyright (c) 2018 - 2019 Seditious Games Studio
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


SCRIPTS_DIRECTORY=$(dirname $(realpath "$0"))
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`

BFG_DOWNLOAD_URL="http://repo1.maven.org/maven2/com/madgag/bfg/1.13.0/bfg-1.13.0.jar"

PROJECT_TAG="GodsOfDeceit"
REMOTE_URL_BASE="git@gitlab.com:SeditiousGames/${PROJECT_TAG}"
BACKUP_REPOSITORY_BASE="/home/mamadou/git-backup/${PROJECT_TAG}"
BARE_REPOSITORY_TAG="Bare-Repo"
TEMP_DIRECTORY=$(mktemp --directory)

function clean() {
    local tag="${1}"
    local strip_blobs_bigger_than="${2}"
    local protect_blobs_from="${3}"

    local local_repository="${TEMP_DIRECTORY}/${PROJECT_TAG}_${tag}"
    local remote_repository="${REMOTE_URL_BASE}_${tag}.git"
    local backup_repository="${BACKUP_REPOSITORY_BASE}-${tag}-${BARE_REPOSITORY_TAG}.git"
    local backup_directory=$(dirname "${backup_repository}")

    mkdir -p "${backup_directory}" \
        && git clone --mirror ${remote_repository} "${backup_repository}" --jobs 8 \
        && git clone ${remote_repository} "${local_repository}" --jobs 8 \
        && cd "${local_repository}" \
        && \
            for branch in `git branch -a | grep remotes | grep -v HEAD | grep -v master ` ; \
            do \
                git branch --track ${branch#remotes/origin/} ${branch}; \
            done \
        && java -jar ${TEMP_DIRECTORY}/bfg.jar \
            --strip-blobs-bigger-than ${strip_blobs_bigger_than} \
            --protect-blobs-from ${protect_blobs_from} "${local_repository}" \
        && git reflog expire --expire=now --all && git gc --prune=now --aggressive \
        && git push --force --all
}

function downloadBfg() {
    wget -q --no-check-certificate ${BFG_DOWNLOAD_URL} -O "${TEMP_DIRECTORY}/bfg.jar"

    local rc=$?
    if [[ ${rc} -ne 0 ]] ;
    then
        exit 1
    fi
}

mkdir -p "${TEMP_DIRECTORY}"
trap "{ rm -rf ${TEMP_DIRECTORY}; }" EXIT

downloadBfg

clean "ThirdParty" "1K" "master"
