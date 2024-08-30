# Ball
Bounching Ball simulation with mass and gravitational acceleration.

## How to use
Press mouse button on the executable to generate a ball(circle) with random radius
and random color every 150ms. Release mouse button to stop generator.

## Building instruction
Build src/main.cpp by whatever compiler with SDL2 linking.

### Visual Studio
Download
[SDL2-devel-2.30.6-VC.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.30.6/SDL2-devel-2.30.6-VC.zip),
extract somewhere and copy the path of subfolder `cmake`. Example: you extract to `G:\\otherfolder`
and you get a folder named `SDL2-2.30.6` inside, then the path is `G:\\otherfolder\\SDL2-2.30.6\\cmake`
Open CMakeSettings.json in editor, change the value from `G:\\libraries\\sdl2\\cmake` to the path you copy
(there're 2 line to change).

Clone this repo.
Start Visual Studio, goto `File -> Open -> CMake...` and choose CMakeLists.txt from this repo.
Select target to `Ball.exe`.

If you can't run, copy `SDL2.dll` from `G:\\otherfolder\\SDL2-2.30.6\\lib\\x86` to `out\\build\\x86-<build_type>`,
`<build_type>` is Debug or Release you choose from Visual Studio.

### Building with CMake (Windows)
Download
[SDL2-devel-2.30.6-VC.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.30.6/SDL2-devel-2.30.6-VC.zip),
extract somewhere and copy the path of subfolder `cmake`. Example: you extract to `G:\\otherfolder`
and you get a folder named `SDL2-2.30.6` inside, then the path is `G:\\otherfolder\\SDL2-2.30.6\\cmake`

The following command will auto detect compiler in your system. Replace `<path_to_sdl_cmake_path>`
with SDL path.

```batch
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<path_to_sdl_cmake_path>
cmake --build build --config Release
```

Put `-DCMAKE_CXX_COMPILER=<path_to_your_compiler>` after the first command to specific the compiler
to build. Example: `-DCMAKE_CXX_COMPILER=D:\mingw32\bin\g++.exe`

Remember to copy `SDL2.dll` from `G:\\otherfolder\\SDL2-2.30.6\\lib\\x86` to `build` folder if you want
to run it.

### Building with CMake (Linux)
If you use linux and want to build this repo. I think you know how to build it, almost the same as "Windows" way
but use system package manager to install library SDL2 instead of downloading.

## Document
Collision algorithm between 2 circle with mass and velocity vector: [https://www.vobarian.com/collisions/2dcollisions2.pdf]

Midpoint circle algorithm (drawing circle in SDL): [https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C]


## Note
Feel free to copy my code, some of it is not mine.

