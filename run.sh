#/bin/bash
exec env LD_LIBRARY_PATH=./build/lib/ ./build/bin/c_eval "$1"
