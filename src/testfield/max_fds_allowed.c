#include <sys/resource.h>
#include <stdio.h>

int main(void) {
    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE, &rl);
    printf("soft: %llu\n", (unsigned long long)rl.rlim_cur);
    printf("hard: %llu\n", (unsigned long long)rl.rlim_max);
    return 0;
}
