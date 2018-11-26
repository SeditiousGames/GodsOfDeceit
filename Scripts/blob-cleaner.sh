#!/usr/bin/env bash

#  (The MIT License)
#
#  Copyright (c) 2018 Mohammad S. Babaei
#  Copyright (c) 2018 Seditious Games Studio
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
REMOTE_REPOSITORY="git@gitlab.com:Seditious Games Studio/GodsOfDeceit_Content_ThirdParty.git"
BACKUP_REPOSITORY="/home/babaei/dev/GodsOfDeceit-bare-repo.git"
BACKUP_DIRECTORY=$(dirname "${BACKUP_REPOSITORY}")

wget -q --no-check-certificate http://repo1.maven.org/maven2/com/madgag/bfg/1.13.0/bfg-1.13.0.jar -O ${SCRIPTS_DIRECTORY}/bfg.jar

mkdir -p ${BACKUP_DIRECTORY} \
    && git clone --mirror ${REMOTE_REPOSITORY} ${BACKUP_REPOSITORY} \
    && java -jar ${SCRIPTS_DIRECTORY}/bfg.jar --strip-blobs-bigger-than 1M --protect-blobs-from master ${PROJECT_DIRECTORY} \
    && cd ${PROJECT_DIRECTORY} \
    && git reflog expire --expire=now --all && git gc --prune=now --aggressive \
    && git push --force --all
