Solutions to K&R2 tasks


This is a collection of my solutions to K&R2 tasks, scripts for running them
and some other related stuff. Solutions are named like this: "ex210.c" for
Exercise 2-10 in book. Files named "n-smth.c" are code samples related to
chapters.


Some tests are AI generated because it's a fairly simple and not very important
task to do, but I try to review them all, so don't worry about them being
faulty, though some might make little sense or be repetitive.


To run a solution you have a few options:

  1. Use `run.sh`
    - by default, compiles and runs the latest changed C file in src, or the
      file you pass as the first argument to the script
      - if a test is present in "tests" folder for the active bin file (checked
        by comparing file stems), then run the test
    - redirects content of `fileinput.txt` to stdin of the binary
    - redirects stdout of the binary to the `fileoutput.txt`
    - logs the start and finish time of the binary

  2. Use `concom.sh` (most useful)
    - watches for any new files and for changes to existing files and executes
      `run.sh` on every change
    - provides the timestamps for each line of output, which is useful to debug
      the performance, kind of (just don't forget to flush the output)

  3. Manually compile and run the solution with a compiler of your preference


Dependencies you might need to use scripts in the repo:

  - ts
  - entr
  - gcc
  - libbsd  (don't ask me, I just like their utils)


Files structure:
  - src/ : directory with all source files
    - lib/ : directory with general purpose utils
    - testfield/ : directory with experiment programs
      - general.c : standalone unit (a bag of all kinds of different stuff)
      - <name>.c : standalone unit (a specific experiment)
    - <name>.c : standalone unit (solution or sample)
    - <name>/ : a more complex unit (if one file is not enough or custom
                compilation process is required)
      - Makefile : describes how to compile this unit into one executable
      - main : executable compiled by Makefile that's copied to /.bin/<name>
  - tests/ : directory with all tests
    - common.bash : common lib for every test
    - <name> : a test for .bin/<name> executable
    - <name>/ : a directory containing a more complicated test for .bin/<name>
                (ex: such, that needs input and output file samples to test on)
      - main : an entry point to the test in the directory
  - .bin/ : directory with all compiled executables
    - lib/: directory containing libs' object and archive files
    - <name> : an executable (most likely produced by run.sh)


Notes on specific exercises:

  4-3 - 4-9:
    These exercises are iterative in a way, so just treat the one with the
    higher number as the version that contains the solutions for each of them.
    4-10 on the other hand asks for modifications, so the solutions for it is
    on its own. Also the testing process for any 4-3 - 4-10 task is kinda
    loose, so if the testing breaks for some solution, try using the
    "fileinput.txt" version from the commit, where the solution was introduced.
