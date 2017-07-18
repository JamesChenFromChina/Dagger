#!/bin/sh

ProjectRootDir=`pwd`
buildDir="build"

./DevMode.sh

MakeBuildDir()
{
    currentDir=${buildDir}"/"${1}
    echo "Make build directory ${currentDir}"

    if [ ! -e ${currentDir} ]
    then
       mkdir -p ${currentDir}
    fi

    cd ${currentDir}
    echo "cd ${currentDir}"
    cmake -DCMAKE_BUILD_TYPE=${1} ../../
    make
    cd ${ProjectRootDir}
}

if [ ${1}x = "clean"x ]
then
    echo "Removeing generated files..."
    rm -rf build
    exit 0
fi

MakeBuildDir Debug
MakeBuildDir Release
