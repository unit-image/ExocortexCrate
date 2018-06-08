cmake_minimum_required(VERSION 3.7)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~ Exocortex-Crate ~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(EXOCORTEX_CRATE_PROJECT_NAME "Exocortex-Crate")

message("")
message("${EXOCORTEX_CRATE_PROJECT_NAME}: BUILD ENABLE")
message("${EXOCORTEX_CRATE_PROJECT_NAME}: Library:(SHARED)")

project(${EXOCORTEX_CRATE_PROJECT_NAME})

# Sets Exocortex-Crate's sources directory
set(EXOCORTEX_CRATE_PATH "${${EXOCORTEX_CRATE_PROJECT_NAME}_SOURCE_DIR}")

# Exocortex-Crate configuration
add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)
add_definitions(-D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Sets Exocortex-Crate compiler flags
set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )

foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MT" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

# Sets custom directories for both shared and static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Sets Exocortex-Crate version
set(crate_MAJOR_VERSION "1")
set(crate_MINOR_VERSION "1")
set(crate_BUILD_VERSION "151")
set(crate_VERSION "${crate_MAJOR_VERSION}.${crate_MINOR_VERSION}")
set(crate_FULLVERSION "${crate_MAJOR_VERSION}.${crate_MINOR_VERSION}.${crate_BUILD_VERSION}")

add_definitions("-Dcrate_MAJOR_VERSION=${crate_MAJOR_VERSION}")
add_definitions("-Dcrate_MINOR_VERSION=${crate_MINOR_VERSION}")
add_definitions("-Dcrate_BUILD_VERSION=${crate_BUILD_VERSION}")
add_definitions(-Dcrate_ver=crate-${crate_FULLVERSION})

# Sets install target directory
set(CMAKE_INSTALL_PREFIX "${EXOCORTEX_CRATE_PATH}/build_install" CACHE PATH "Install target directory" FORCE)

# ~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~ Dependencies ~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~

# Sets dependencies path
set(EXOCORTEX_CRATE_DEPS "${EXOCORTEX_CRATE_PATH}/deps/Exocortex-Crate-WindowsDeps")


# ~~~~~~~~~~~~~~~~~
# ~~~~~ Boost ~~~~~
# ~~~~~~~~~~~~~~~~~

message("")

# Sets boost's libraries
set(BOOST_LIBRARY_DIR "${EXOCORTEX_CRATE_DEPS}/libs/boost-1.61.0")
file(GLOB BOOST_LIBRARIES "${BOOST_LIBRARY_DIR}/*.lib")

message("boost: Libraries:")
foreach(LIB ${BOOST_LIBRARIES})
	message("boost: Release/library:(${LIB})")
endforeach(LIB)

# Sets boost's includes
set(BOOST_INCLUDE_DIR "${EXOCORTEX_CRATE_DEPS}/includes/boost-1.61.0")
message("boost: include_dir:(${BOOST_INCLUDE_DIR})")


# ~~~~~~~~~~~~~~~~
# ~~~~~ hdf5 ~~~~~
# ~~~~~~~~~~~~~~~~

message("")

# Sets hdf5 version
add_definitions(-Dhdf_ver=1.8.20)

# hdf5 configuration
add_definitions(-DH5_HAVE_THREADSAFE)

# Sets hdf5's libraries
set(HDF5_LIBRARY_DIR "${EXOCORTEX_CRATE_DEPS}/libs/hdf5-1.8.20")
set(HDF5_LIBRARIES "${HDF5_LIBRARY_DIR}/libhdf5.lib" "${HDF5_LIBRARY_DIR}/libhdf5_hl.lib")

message("hdf5: Libraries:")
foreach(LIB ${HDF5_LIBRARIES})
	message("hdf5: Release/library:(${LIB})")
endforeach(LIB)

# Sets hdf5's includes
set(HDF5_INCLUDE_DIR "${EXOCORTEX_CRATE_DEPS}/includes/hdf5-1.8.20")
message("hdf5: include_dir:(${HDF5_INCLUDE_DIR})")


# ~~~~~~~~~~~~~~~~
# ~~~~~ ZLIB ~~~~~
# ~~~~~~~~~~~~~~~~

message("")

# Sets zlib's libraries
set(ZLIB_LIBRARY_DIR "${EXOCORTEX_CRATE_DEPS}/libs/hdf5-1.8.20")
set(ZLIB_LIBRARIES "${ZLIB_LIBRARY_DIR}/libzlib.lib")

message("zlib: Library:")
message("zlib: Release/library:(${ZLIB_LIBRARIES})")

# Sets zlib's includes
set(ZLIB_INCLUDE_DIR "${EXOCORTEX_CRATE_DEPS}/includes/hdf5-1.8.20")
message("zlib: include_dir:(${HDF5_INCLUDE_DIR})")


# ~~~~~~~~~~~~~~~~~~~
# ~~~~~ IlmBase ~~~~~
# ~~~~~~~~~~~~~~~~~~~

message("")

# Sets ilmbase's libraries
set(ILMBASE_LIBRARY_DIR "${EXOCORTEX_CRATE_DEPS}/libs/ilmbase-2.2.0")
file(GLOB ILMBASE_LIBRARIES "${ILMBASE_LIBRARY_DIR}/*.lib")

message("ilmbase: Libraries:")
foreach(LIB ${ILMBASE_LIBRARIES})
	message("ilmbase: Release/library:(${LIB})")
endforeach(LIB)

# Sets ilmbase's includes
set(ILMBASE_INCLUDE_DIR "${EXOCORTEX_CRATE_DEPS}/includes/ilmbase-2.2.0/OpenEXR")
message("ilmbase: include_dir:(${ILMBASE_INCLUDE_DIR})")


# ~~~~~~~~~~~~~~~~~~~
# ~~~~~ Alembic ~~~~~
# ~~~~~~~~~~~~~~~~~~~

message("")

# Sets Alembic version
add_definitions(-Dalembic_ver=1.7.8)

# Sets Alembic configuration
add_definitions(-DNOMINMAX)
add_definitions(-D_WINSOCKAPI_)
add_definitions(-D_WINSOCKAPI2_)

# Sets alembic's libraries
set(ALEMBIC_LIBRARY_DIR "${EXOCORTEX_CRATE_DEPS}/libs/alembic-1.7.8")
set(ALEMBIC_LIBRARIES "${ALEMBIC_LIBRARY_DIR}/Alembic.lib")

message("alembic: Library:")
message("alembic: Release/library:(${ALEMBIC_LIBRARIES})")

# Sets alembic's includes
set(ALEMBIC_INCLUDE_DIR "${EXOCORTEX_CRATE_DEPS}/includes/alembic-1.7.8" "${EXOCORTEX_CRATE_DEPS}/includes/alembic-1.7.8/Alembic")
foreach(DIR ${ALEMBIC_INCLUDE_DIR})
	message("alembic: include_dir:(${DIR})")
endforeach(DIR)


# ~~~~~~~~~~~~~~~~~
# ~~~~~ Utils ~~~~~
# ~~~~~~~~~~~~~~~~~

set(EXOCORTEX_CRATE_UTILS_PROJECT_NAME "Exocortex-Crate-Utils")
set(EXOCORTEX_CRATE_UTILS_DIR "${EXOCORTEX_CRATE_PATH}/Utils")
add_subdirectory("${EXOCORTEX_CRATE_PATH}/Utils")


# ~~~~~~~~~~~~~~~
# ~~~~~ DCC ~~~~~
# ~~~~~~~~~~~~~~~

set(EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME "Exocortex-Crate-3dsMax")
set(EXOCORTEX_CRATE_3DSMAX_DIR "${EXOCORTEX_CRATE_PATH}/3DSMax")
add_subdirectory("3DSMax")
