#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#define C_FLAGS "-Wall", "-Wextra", "-pedantic", "-std=c11"

void build_main() {
    INFO("Building c_eval");
    MKDIRS("build", "bin");
    CMD("cc", C_FLAGS, "-o", PATH("build", "bin", "c_eval"),
        PATH("src", "main.c"),
        PATH("src", "linked_list.c"),
        "-I/src");
}

int main(int argc, char **argv) {
    GO_REBUILD_URSELF(argc, argv);
    build_main();
    return 0;
}
