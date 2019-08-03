# leetcode-cxx
* Solve leetcode problems in C++.
* Feature test of C++.

### Compile
* `./compile.sh path/to/filename.cxx`
* or Open this directory in `Visual Studio Code`, open a cxx file, and press `Ctrl+Shift+B` to build.

### Run
The built executable is outputed to `./objs/`.
* Run the built executable by `./objs/filename`
* or Debug with gdb on command line
* or Debug in Visual Studio Code

### NOTE
* VSCode has been configured to support `Build` on both Linux and Windows
  * Linux: `g++`
  * Windows: need `cl.exe` from Visual Studio or `g++.exe` from `MSYS2/Cygwin`
* VSCode has been configured to support `Debug` on both Linux and Windows
  * Linux: `gdb`
  * Windows: `Visual Studio CPP Debug` or `windbg`
