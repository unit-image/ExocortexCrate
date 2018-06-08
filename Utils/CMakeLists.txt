cmake_minimum_required(VERSION 3.7)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~ EXOCORTEX-CRATE-UTILS ~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

message("")
message("${EXOCORTEX_CRATE_UTILS_PROJECT_NAME}: BUILD ENABLE")
message("${EXOCORTEX_CRATE_UTILS_PROJECT_NAME}: Library:(STATIC)")

project(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} CXX)

# Sets Exocortex-Crate-Utils configuration
add_definitions(-DPROFILING_OFF)

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles *.cpp)
file(GLOB_RECURSE HFiles *.h)

# Compiles Exocortex-Crate-Utils as static library
add_library(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} STATIC ${CppFiles} ${HFiles})

# Creates install target
install(TARGETS ${EXOCORTEX_CRATE_UTILS_PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static)
install(DIRECTORY "${EXOCORTEX_CRATE_UTILS_DIR}" DESTINATION "${EXOCORTEX_CRATE_PATH}/build_install" FILES_MATCHING PATTERN "*.h")

# Links Alembic target to Exocortex-Crate-Utils
target_link_libraries(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} "${ALEMBIC_LIBRARIES}")
target_include_directories(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} PUBLIC "${ALEMBIC_INCLUDE_DIR}")

# Links Boost target to Exocortex-Crate-Utils
target_link_libraries(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} "${BOOST_LIBRARIES}")
target_include_directories(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} PUBLIC "${BOOST_INCLUDE_DIR}")

# Links IlmBase target to Exocortex-Crate-Utils
target_link_libraries(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} "${ILMBASE_LIBRARIES}")
target_include_directories(${EXOCORTEX_CRATE_UTILS_PROJECT_NAME} PUBLIC "${ILMBASE_INCLUDE_DIR}")