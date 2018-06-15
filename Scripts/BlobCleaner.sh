#!/usr/bin/env bash

SCRIPTS_DIRECTORY=$(dirname $(realpath "$0"))
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
REMOTE_REPOSITORY="git@gitlab.com:Khavaran67/GodsOfDeceit_Content_ThirdParty.git"
BACKUP_REPOSITORY="/home/babaei/dev/GodsOfDeceit-bare-repo.git"
BACKUP_DIRECTORY=$(dirname "${BACKUP_REPOSITORY}")

wget -q --no-check-certificate http://repo1.maven.org/maven2/com/madgag/bfg/1.13.0/bfg-1.13.0.jar -O ${SCRIPTS_DIRECTORY}/bfg.jar

mkdir -p ${BACKUP_DIRECTORY} \
    && git clone --mirror ${REMOTE_REPOSITORY} ${BACKUP_REPOSITORY} \
    && java -jar ${SCRIPTS_DIRECTORY}/bfg.jar --strip-blobs-bigger-than 1M --protect-blobs-from master ${PROJECT_DIRECTORY} \
    && cd ${PROJECT_DIRECTORY} \
    && git reflog expire --expire=now --all && git gc --prune=now --aggressive \
    && git push --force --all
