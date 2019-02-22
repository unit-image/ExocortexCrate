@echo off

REM Info:
REM To build the project you'll need to install some dependencies:
REM		- CMake 3.7
REM		- Visual studio 2015
REM		- Exocortex-Crate-WindowsDeps
REM
REM These dependencies must be in your system environment path

SET "VISUAL_VERSION=Visual Studio 14 2015 Win64"
SET "MAX_VERSION=2018"

REM Remove the old build directory
rmdir build /s /q
rmdir build_install /s /q

REM Create a new build directory and move to it
mkdir build
mkdir build_install


echo [1/1] Building ExocortexCrate ...
echo.

REM Generate the visual studio 2015 solution
cmake -B build -G"%VISUAL_VERSION%" -DMAX_VERSION=%MAX_VERSION%

echo.
echo compiling ...

REM Build the project
devenv.exe build/Exocortex-Crate.sln /build release /project INSTALL

echo.
echo Done.

@echo on