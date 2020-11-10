#!/bin/bash
set -e
overload() {
    printf "Overloading serv\n";
    for i in {1..20}
    do
        time ( ./client 5000 "Request $i $1" )
    done
}

rm -rf output
make compile-client
(overload 1 & overload 2 & overload 3 & overload 4 & overload 5) 
