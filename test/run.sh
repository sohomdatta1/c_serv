#!/bin/bash

test_success() {
    if pgrep -x 'serv' > /dev/null
    then
        printf "run.sh -- Test successful! -- Program ran!"
        true
    else
        printf "run.sh -- Test Failed -- Program failed to run!"
        false
    fi
}

set -e
( make clean > /dev/null && make -j4 > /dev/null ) &&
(./serv 1>/dev/null 2>/dev/null & ) &&
test_success &&
kill -SIGINT $(pgrep -x 'serv')
