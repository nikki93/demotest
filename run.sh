#!/bin/sh

if [[ $# == 1 ]]
then
    if [[ $1 == "debug" ]]
    then
        ./bin/debug/demotest_d
        exit
    fi
fi
./bin/release/demotest
