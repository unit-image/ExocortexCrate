# Exocortex Crate

The professional grade, battle tested and feature filled Alembic suite.  
**This repository compiles ExocortexCrate for 3DSMax 2018 only.**

# Binary Downloads

See the release page of this repository.

# License

This software is open source software.  Please consult LICENSE.txt for details.

# Requirements

We use automatically generated projects from a canonical set of CMakeList files.
Thus to create the project files for your platform you will have to install
CMake.

In order to build on Windows platforms, you will require the correct Microsoft C++
for the plugins you require.

# External Libraries

To build the plugins you will require the external libraries. They are located in this repository:
	https://github.com/unit-image/Exocortex-Crate-WindowsDeps

You must clone this repository in the ```deps``` folder [Create it if it isn't exists].

# Building

To build ExocortexCrate you'll need to install some dependencies:
	- CMake 3.7
	- Visual studio 2015
	- Exocortex-Crate-WindowsDeps

These dependencies must be in your system environment path, except ```Exocortex-Crate-WindowsDeps``` that must be located in the ```deps``` folder.

When dependencies are installed, open a ```VS2015 x64 Native Tools``` command prompt and type ```compile.bat```.
A new folder named ```build_install``` will be created with the libraries and includes files.