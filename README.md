### Configuration & Run
1. Install [VSCode](https://code.visualstudio.com/).
2. Follow the guide [CMake Tools for Visual Studio Code](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/README.md).
   1. Install C/C++ extension for VS Code. 
   2. Install CMake Tool extension for VS Code.
   3. Install [MinGW-w64] via [MSYS2](https://www.msys2.org/) follow the [guide](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain)
      1. Download MSYS2 and install.
      2. Open MSYS2 terminal and install MinGW-w64 toolchain by running
          
          ``` pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain ```
      3. Add the path MinGW-w64 folder to System PATH.
   4. install [CMake](https://cmake.org/download/) and add CMake into System PATH.
3. Open project in VS Code. 
4. From the command palette in VS Code, run the **CMake: Configure command**.
5. From the command palette, run the **CMake: Select a Kit**.
6. From the command palette, run the **CMake: Run** or click **Run** button from the status bar.