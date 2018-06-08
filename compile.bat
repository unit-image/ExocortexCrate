@echo off

REM Info:
REM To build the project you'll need to install some dependencies:
REM		- CMake 3.7
REM		- Visual studio 2015
REM		- Exocortex-Crate-WindowsDeps
REM
REM These dependencies must be in your system environment path

REM Remove the old build directory
rmdir build /s /q
rmdir build_install /s /q

REM Create a new build directory and move to it
mkdir build
mkdir build_install

cd build

echo [1/1] Building ExocortexCrate ...
echo.

REM Generate the visual studio 2015 solution
cmake -G"Visual Studio 14 2015 Win64" ..

REM Build the project
devenv.exe Exocortex-Crate.sln /build release /project INSTALL

echo.
echo Done.

REM Return to the root directory
cd ..

@echo on