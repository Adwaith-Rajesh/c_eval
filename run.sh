#/bin/bash
cc -o nobuild nobuild.c
./nobuild
exec env LD_LIBRARY_PATH=./build/lib/ ./build/bin/c_eval "$1"