REM mingw32-make clean
REM   NO! BAD!
REM   this deletes the raylib (engine) lib too, LOL
REM   Not sure why it does that,especially considering that
REM   this Makefile doesn't automatically make raylib for you... wtf
del *.o
cd states
del *.o