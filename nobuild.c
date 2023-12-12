#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#define CC "g++"
#define CFLAGS "-Wall", "-Wextra", "-pedantic", "-std=c++11"
#define SRC_DIR "src/"
#define SRC SRC_DIR "raylib_game.cpp"
#define BUILD_DIR "build/"
#define TARGET BUILD_DIR "Paint"
#define LDFLAGS "-lraylib", "-lm"

void build(void) {
  CMD("mkdir", "-p", BUILD_DIR);
  CMD(CC, CFLAGS, SRC, "-o", TARGET, LDFLAGS);
}

void run(void) { CMD(TARGET); }

int main(int argc, char **argv) {
  GO_REBUILD_URSELF(argc, argv);

  build();
  run();

  return 0;
}
