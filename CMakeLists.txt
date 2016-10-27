
cmake_minimum_required(VERSION 2.8.11)

project(Dagger)

add_subdirectory(thirdparty/gmock)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

set(PROJECT_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

include_directories(Dagger ${PROJECT_THIRD_PARTY_DIR}/gmock/gtest/include/)

aux_source_directory(src SRC_DIR)
aux_source_directory(utility UTIL_DIR)

set(SRC_LIST ${SRC_DIR} ${UTIL_DIR})

link_directories(${PROJECT_THIRD_PARTY_DIR}/gmock/gtest)

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

add_definitions("-Wno-unused-result -std=c++11 -Wsign-compare -g -fwrapv -Wall")
#add_definitions("-Wall -Xlinker -export-dynamic -fstack-protector-all")

#add_library(Dagger SHARED ${SRC_FILE})
add_library(Dagger ${SRC_FILE})

add_executable(dagger_testing ${TESTING_FILE})

set(PUB_LIBRARIES libgtest.a pthread dl util m)
target_link_libraries(dagger_testing ${PUB_LIBRARIES})