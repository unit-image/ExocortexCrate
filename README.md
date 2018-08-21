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

# How to build ExocortexCrate ?

To build ExocortexCrate you need to install some dependencies:
  - CMake 3.7
  - Visual studio 2015
  - Exocortex-Crate-WindowsDeps

These dependencies must be in your system environment path, except ```Exocortex-Crate-WindowsDeps``` that must be located in the ```deps``` folder.

When dependencies are installed, open a ```VS2015 x64 Native Tools``` command prompt and type ```compile.bat```.
A new folder named ```build_install``` will be created with the libraries and includes files.

# How to install ExocortexCrate ?

To install ExocortexCrate, You need to download:
  - The latest release of ExocortexCrate (the release contains the ```build_install``` folder).
  - The Exocortex-Crate-WindowsDeps repository.
  
Then,

  1. Copy the ExocortexCrate dlu from ```build_install\bin``` to ```YOUR_3DS_MAX_FOLDER\Plugins``` folder.
  2. Copy the 3DS Max scripts from ```build_install\3DSMax\MaxScripts``` to ```YOUR_3DS_MAX_FOLDER\scripts``` folder.
  3. Copy the dependencies (Alembic' and ilmbase' dlls) in your ```YOUR_3DS_MAX_FOLDER``` folder.