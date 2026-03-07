#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char buf[BUFSIZ];
  int n;
  int fd;

  if (argc == 1) {
    while ((n = read(0, buf, BUFSIZ)) > 0)
      if (write(1, buf, n) != n)
        err(EXIT_FAILURE, "can't write");
    return 0;
  }

  while (*++argv) {
    fd = open(*argv, O_RDONLY);
    if (fd < 0) {
      err(EXIT_FAILURE, "file open issue");
    }
    while ((n = read(fd, buf, BUFSIZ)) > 0)
      if (write(1, buf, n) != n)
        err(EXIT_FAILURE, "can't write");
    close(fd);
  }

  return 0;
}
