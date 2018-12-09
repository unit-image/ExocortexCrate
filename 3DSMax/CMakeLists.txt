cmake_minimum_required(VERSION 3.7)

# ~~~~~~~~~~~~~~~~~~
# ~~~~~ 3DSMax ~~~~~
# ~~~~~~~~~~~~~~~~~~

message("")

# Sets max's libraries
set(3DSMAX_LIBRARY_DIR "${EXOCORTEX_CRATE_DEPS}/libs/max-sdk-2019")
file(GLOB 3DSMAX_LIBRARIES "${3DSMAX_LIBRARY_DIR}/*.lib")

message("max: Libraries:")
foreach(LIB ${3DSMAX_LIBRARIES})
	message("max: Release/library:(${LIB})")
endforeach(LIB)

# Sets boost's includes
set(3DSMAX_INCLUDE_DIR "${EXOCORTEX_CRATE_DEPS}/includes/max-sdk-2019")
message("max: include_dir:(${3DSMAX_INCLUDE_DIR})")


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~ EXOCORTEX-CRATE-3DSMAX ~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message("")
message("${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME}: BUILD ENABLE")
message("${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME}: Library:(SHARED)")

# Sets Exocortex-Crate-3dsMax configuration
add_definitions(-Dcrate_Max_Version=2018)

# Sets Exocortex-Crate-3dsMax compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm124")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles *.cpp)
file(GLOB_RECURSE HFiles *.h)
file(GLOB RcFiles resource.rc)

# Compiles Exocortex-Crate-3DSMax
add_library(${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME} SHARED ${CppFiles} ${HFiles} ${RcFiles})

# Set shared library extension
set_target_properties(${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME} PROPERTIES SUFFIX ".dlu")

# Creates install target
install(TARGETS ${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static)
install(DIRECTORY "${EXOCORTEX_CRATE_3DSMAX_DIR}" DESTINATION "${EXOCORTEX_CRATE_PATH}/build_install" FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "${EXOCORTEX_CRATE_3DSMAX_DIR}" DESTINATION "${EXOCORTEX_CRATE_PATH}/build_install" FILES_MATCHING PATTERN "*.mcr")
install(DIRECTORY "${EXOCORTEX_CRATE_3DSMAX_DIR}" DESTINATION "${EXOCORTEX_CRATE_PATH}/build_install" FILES_MATCHING PATTERN "*.ms")

# Links Exocortex-Crate-Utils target to Exocortex-Crate-3DSMax
target_link_libraries(${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME} "${EXOCORTEX_CRATE_UTILS_PROJECT_NAME}")
target_include_directories(${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME} PUBLIC "${EXOCORTEX_CRATE_UTILS_DIR}")

# Links 3DSMax target to Exocortex-Crate-3DSMax
target_link_libraries(${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME} "${3DSMAX_LIBRARIES}")
target_include_directories(${EXOCORTEX_CRATE_3DSMAX_PROJECT_NAME} PUBLIC "${3DSMAX_INCLUDE_DIR}")