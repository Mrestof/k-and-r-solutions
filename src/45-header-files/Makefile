gcc_warnings=\
-Wall -Wextra -Wpedantic -Wreturn-type -Wdouble-promotion -Wfloat-conversion
gcc_debug_options=\
-g -ftrivial-auto-var-init=zero -fno-omit-frame-pointer
gcc_includes=\
-L../../.bin/lib -I../lib -lmyutils -lm
gcc_optimizations=\
-O0
gcc_sanitizations=\
-fsanitize=undefined

main: $(wildcard *.c)
	gcc $(gcc_debug_options) -c ../lib/myutils.c -o ../../.bin/lib/myutils.o
	ar rcs ../../.bin/lib/libmyutils.a ../../.bin/lib/myutils.o
	gcc \
		$(gcc_optimizations) \
		$(gcc_sanitizations) \
		$(gcc_debug_options) \
		$(gcc_warnings) \
		-o main *.c \
		$(gcc_includes)
