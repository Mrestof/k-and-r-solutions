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
    - compiles and runs the latest changed C file in src, or the file you pass
      as the first argument to the script
    - redirects content of `fileinput.txt` to stdin of the binary
    - redirects stdout of the binary to the `fileoutput.txt`
    - logs the start and finish time of the binary

  2. Use `concom.sh`
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
