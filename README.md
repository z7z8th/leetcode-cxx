# leetcode-cxx
* Solve leetcode problems in C++.
* Feature test of C++.

### Build
* `./compile.sh path/to/filename.cxx`
* or  
	Open this directory in `Visual Studio Code`,  
	open a cxx file,  
	and press `Ctrl+Shift+B` to build,  
	or build by menu `Terminal` -> `Run tasks` -> `Select tasks begin with g++, g++.exe or cl.exe`.  
	(See [NOTE](#note) for detail) 

### Run
The built executable is outputed to `./objs/`.
* `Run` the built executable by `./objs/filename`
* or `Debug` with gdb on command line
* or `Debug` in Visual Studio Code

### NOTE
* `Build` or `Debug` in VSCode on Linux
  * Build: `g++`
  * Debug: `gdb`
* `Build` or `Debug` in VSCode on Windows
  * Build: `g++.exe` from `MSYS2(MINGW64)` or `cl.exe` from `Visual Studio`
    * Tips for build with `g++.exe` from MSYS2:
        ```shell
        pacman -Syu
        pacman -Sy mingw64/mingw-w64-x86_64-gcc
        pacman -Sy mingw64/mingw-w64-x86_64-gdb
        ```
        Then add `C:\msys64\mingw64\usr\bin\` to System `PATH`
  * Debug: `gdb.exe`, `Visual Studio CPP Debug` or `windbg`
* **Try solving it by yourself first!**
