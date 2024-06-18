#!/bin/bash

function get_all_users {
        echo $(cat /etc/passwd | cut -d ":" -f1)        
}

function get_all_groups {
        echo $(cat /etc/group | grep -E "$1" | cut -d ":" -f1)
}

function find_main_group {
        GID=$(cat /etc/passwd | grep -E "$1" | cut -d ":" -f4)
        echo $(cat /etc/group | grep -E ".*:x:${GID}" | cut -d ":" -f1)
}

USERS=$(get_all_users)
USERNAME="$1"
IS_USER_EXIST=1

MAIN_GROUP=$(find_main_group ${USERNAME})
ALL_GROUP=$(get_all_groups ${USERNAME})

if [ $# -lt 1 ]; then
        echo Usage: >&2
        echo $0 "username" >&2
        exit 1
else
        for u in $USERS; do
                if [ $u = $USERNAME ]; then
                        IS_USER_EXIST=0
                fi
        done
fi

if [ $IS_USER_EXIST -eq 0 ]; then
        echo $MAIN_GROUP $(echo ${ALL_GROUP} | sed "s/${USERNAME}//")
        exit 0
else
        echo $1: user not found >&2
        exit 2
fi
