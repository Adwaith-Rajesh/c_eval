#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#define C_FLAGS "-Wall", "-Wextra", "-pedantic", "-std=c11"

void build_linked_list_so() {
    INFO("Building Linked List SO");
    MKDIRS("build", "lib");
    CMD("cc", C_FLAGS, "-shared", "-fPIC",
        PATH("src", "lib", "linked_list.c"),
        "-I./src/lib",
        "-o",
        PATH("build", "lib", "libll.so"));
}

void build_main() {
    INFO("Building c_eval");
    MKDIRS("build", "bin");
    CMD("cc", C_FLAGS, "-o", PATH("build", "bin", "c_eval"),
        "-L./build/lib/",
        "-I./src",
        "-I./src/lib",
        PATH("src", "main.c"),
        "-lll");
}

int main(int argc, char **argv) {
    GO_REBUILD_URSELF(argc, argv);
    build_linked_list_so();
    build_main();
    return 0;
}
