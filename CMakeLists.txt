
cmake_minimum_required(VERSION 2.8.12)
project(dagger)

# Parameter Setting
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(PROJECT_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# Get all source file
set(SRC_DIR src net utility)

set(SRC_LIST )

foreach(srcDir ${SRC_DIR})
  aux_source_directory(${srcDir} SRC_DIR_FILES)
  message(STATUS "SCANING DIR : " ${srcDir} " GET FILES : " ${SRC_DIR_FILES})
  set(SRC_LIST ${SRC_LIST} ${SRC_DIR_FILES})
endforeach(srcDir)

# Separate testing file from program source file.
set(TEST_REGEX_ST "^.+_testing\\.(h|H|hcc|HCC|c|C|cc|CC|cpp|CPP)$")
foreach(srcFile ${SRC_LIST})
  if("${srcFile}" MATCHES "${TEST_REGEX_ST}")
    set(TESTING_FILE ${TESTING_FILE} ${srcFile})
    message(STATUS "ADD TESTING FILE : " ${srcFile})
  else("${srcFile}" MATCHES "${TEST_REGEX_ST}")
    set(SRC_FILE ${SRC_FILE} ${srcFile})
    message(STATUS "ADD SRC FILE : " ${srcFile})
  endif("${srcFile}" MATCHES "${TEST_REGEX_ST}")
endforeach(srcFile)

# Add subproject
# add_subdirectory(thirdparty/gtest)

set(INCLUDE_DIRS .)
set(LINK_DIRS )

# Add gtest
if (BUILD_WITH_GTEST)
  set(INCLUDE_DIRS ${INCLUDE_DIRS}  ${PROJECT_THIRD_PARTY_DIR}/gtest/googletest/include/)
  set(LINK_DIRS ${LINK_DIRS} ${PROJECT_THIRD_PARTY_DIR}/gtest/googlemock/gtest)
endif (BUILD_WITH_GTEST)

include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})

# Compiling arguments
add_definitions("-Wno-unused-result -std=c++11 -Wsign-compare -g -fwrapv -Wall")
#add_definitions("-Wall -Xlinker -export-dynamic -fstack-protector-all")

if (BUILD_SHARED_LIBS)
  set(IS_BUILD_SHARED_LIBS_DEFAULT ON)
else (BUILD_SHARED_LIBS)
  set(IS_BUILD_SHARED_LIBS_DEFAULT OFF)
endif (BUILD_SHARED_LIBS)

option(PROJECT_BUILD_SHARED_LIBS "Build Shared Libraries" ${IS_BUILD_SHARED_LIBS_DEFAULT})

if (PROJECT_BUILD_SHARED_LIBS)
  set(PROJECT_SHARED_OR_STATIC "SHARED")
else (PROJECT_BUILD_SHARED_LIBS)
  set(PROJECT_SHARED_OR_STATIC "STATIC")
endif (PROJECT_BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} ${PROJECT_SHARED_OR_STATIC} ${SRC_FILE})

if (BUILD_WITH_GTEST)
  # Make testing program.
  set(TESTING_PROGRAM_NAME testing)
  add_executable(${TESTING_PROGRAM_NAME} ${TESTING_FILE})
  set(PUB_LIBRARIES libgtest.a pthread dl util m)
  target_link_libraries(${TESTING_PROGRAM_NAME} ${PUB_LIBRARIES} ${PROJECT_NAME})
endif (BUILD_WITH_GTEST)
