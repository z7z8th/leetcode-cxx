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
  * Windows: `g++.exe` from `MSYS2(MINGW64)` or `cl.exe` from `Visual Studio`
    * MSYS2:
        ```shell
        pacman -Syu
        pacman -Sy mingw64/mingw-w64-x86_64-gcc
        pacman -Sy mingw64/mingw-w64-x86_64-gdb
        ```
        Then add `C:\msys64\mingw64\usr\bin\` to System `PATH`
* VSCode has been configured to support `Debug` on both Linux and Windows
  * Linux: `gdb`
  * Windows: `gdb.exe`, `Visual Studio CPP Debug` or `windbg`
