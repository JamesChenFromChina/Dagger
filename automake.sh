#!/bin/bash

function download_from_git
{
    DOWNLOAD_PATH=$1
    curl $curlopts -kLo zipfile.zip ${DOWNLOAD_PATH}
    unzip -q zipfile.zip
    rm zipfile.zip
}

function mk_third_party
{
    if test ! -e thirdparty; then
        mkdir thirdparty
    fi
}

function print_usage
{
    echo "Usage:"
    echo "-g compile testing program"
    echo "-d compile debug version"
    echo "-d compile release version"
}

if test ! -e SysLibInclude; then
    ln -s /usr/include ./SysLibInclude
fi

if test ! -e SysLocLibInclude; then
    ln -s /usr/local/include ./SysLocLibInclude
fi

PROJECT_HOME=`pwd`

CMAKE_ARGS=""

while getopts "tdrh" arg
do
    case $arg in
        t)
          echo "Compile testing program"
          CMAKE_ARGS="${CMAKE_ARGS} -DBUILD_WITH_GTEST=1"
          # Check that gmock is present.  Usually it is already there since the
          # directory is set up as an SVN external.
          mk_third_party
          cd thirdparty
          if test ! -e gtest; then
              echo "Google Mock not present. Fetching gmock-1.7.0 from the web..."
              download_from_git https://codeload.github.com/google/googletest/zip/release-1.8.0;
              mv googletest-release-1.8.0 gtest
              cd gtest
              cmake .
              make
          fi
          cd ${PROJECT_HOME}
          ;;
        d)
          echo "Compile debug version"
          CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_BUILD_TYPE=debug"
          ;;
        r)
          echo "Compile release version"
          CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_BUILD_TYPE=release"
          ;;
        h)
          print_usage
          exit 0;
          ;;
        ?)
          print_usage
          exit 0;
          ;;
     esac
done

cd ${PROJECT_HOME}

buildDir="build"

if [ ${1}x = "clean"x ]
then
    echo "Removeing generated files..."
    git clean -xdf
    exit 0
fi

if test ! -e build; then
    mkdir build
fi
cd build

echo "Run: cmake  ${CMAKE_ARGS} .."
cmake ${CMAKE_ARGS} ..
make

if test -e testing; then
    ./testing
fi

cd ${PROJECT_HOME}

