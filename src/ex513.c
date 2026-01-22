#include <stddef.h>
#include <string.h>

#define MEMSIZE 1000

char buf[MEMSIZE];
char* bp = buf;

char* alloc(int size) {
  if ((bp + size) - buf >= MEMSIZE)
    return NULL;
  char* p = bp;
  bp += size;
  return p;
}

void dealloc(char* ptr) {
  if (ptr >= buf && ptr < buf + MEMSIZE)
    bp = ptr;
}

int main() {
}
