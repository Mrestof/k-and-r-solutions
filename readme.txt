Solutions to K&R2 tasks


This is a collection of my solutions to K&R2 tasks, scripts for running them
and some other related stuff.


To run a solution you have a few options:

  1. Use `run.sh`. You can either pass a file name to compile and run,
    measuring the time it takes, or execute the script without arguments, so it
    finds the latest changed C file in src and compiles and runs it.

  2. Use `concom.sh`. It automatically watches for any new files and changes to
    existing files and executes `run.sh` on every change. It also provides the
    timestamps for each line of output, which is useful to debug the
    performance, kind of (just don't forget to flush the output.

  3. Manually compile and run the solution with a compiler of your preference.


Dependencies you might need to use scripts in the repo:

  - ts
  - entr
  - gcc
  - libbsd  (don't ask me, I just like their utils)
