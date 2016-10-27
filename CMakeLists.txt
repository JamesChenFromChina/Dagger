
cmake_minimum_required(VERSION 2.8.12)
project(Dagger)

# Parameter Setting
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

set(PROJECT_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# Get all source file
aux_source_directory(src SRC_DIR)
aux_source_directory(utility UTIL_DIR)

# Separate testing file from program source file.
set(SRC_LIST ${SRC_DIR} ${UTIL_DIR})
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
add_subdirectory(thirdparty/gmock)

# Compiling arguments
include_directories(Dagger ${PROJECT_THIRD_PARTY_DIR}/gmock/gtest/include/)
link_directories(${PROJECT_THIRD_PARTY_DIR}/gmock/gtest)
add_definitions("-Wno-unused-result -std=c++11 -Wsign-compare -g -fwrapv -Wall")
#add_definitions("-Wall -Xlinker -export-dynamic -fstack-protector-all")

# Make libdagger.so or libdagger.a
#add_library(Dagger SHARED ${SRC_FILE})

if (BUILD_SHARED_LIBS)
  set(Dagger_BUILD_SHARED_LIBS_DEFAULT ON)
else (BUILD_SHARED_LIBS)
  set(Dagger_BUILD_SHARED_LIBS_DEFAULT OFF)
endif (BUILD_SHARED_LIBS)

option(Dagger_BUILD_SHARED_LIBS "Build Shared Libraries" ${Dagger_BUILD_SHARED_LIBS_DEFAULT})

if (Dagger_BUILD_SHARED_LIBS)
  set(Dagger_SHARED_OR_STATIC "SHARED")
else (Dagger_BUILD_SHARED_LIBS)
  set(Dagger_SHARED_OR_STATIC "STATIC")
endif (Dagger_BUILD_SHARED_LIBS)

add_library(Dagger ${Dagger_SHARED_OR_STATIC} ${SRC_FILE})

# Make testing program.
add_executable(dagger_testing ${TESTING_FILE})
set(PUB_LIBRARIES libgtest.a pthread dl util m)
target_link_libraries(dagger_testing ${PUB_LIBRARIES})