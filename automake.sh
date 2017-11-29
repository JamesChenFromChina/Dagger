#!/bin/sh

if test ! -e SysLibInclude; then
    ln -s /usr/include ./SysLibInclude
fi


if test ! -e SysLocLibInclude; then
    ln -s /usr/local/include ./SysLocLibInclude
fi
PROJECT_HOME=`pwd`

if test ! -e thirdparty; then
    mkdir thirdparty
fi

cd thirdparty


if [ ${2}x = "gtest"x ]
then
    # Check that gmock is present.  Usually it is already there since the
    # directory is set up as an SVN external.
    if test ! -e gtest; then
        echo "Google Mock not present.  Fetching gmock-1.7.0 from the web..."
        curl $curlopts -L -O https://codeload.github.com/google/googletest/zip/release-1.8.0
        unzip -q release-1.8.0
        rm release-1.8.0
        mv googletest-release-1.8.0 gtest
        cd gtest
        cmake .
        make
    fi
fi

cd ${PROJECT_HOME}

ProjectRootDir=`pwd`
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

if [ ${2}x = "gtest"x ]
then
    cmake -DCMAKE_BUILD_TYPE={1} -DBUILD_WITH_GTEST=1 ..
    make
    ./testing
else
    cmake -DCMAKE_BUILD_TYPE={1} ..
    make
fi

cd ..
