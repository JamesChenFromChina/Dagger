#!/bin/sh

ln -s /usr/include ./SysLibInclude
ln -s /usr/local/include ./SysLocLibInclude

if test ! -e thirdparty; then
    mkdir thirdparty
fi

# Check that gmock is present.  Usually it is already there since the
# directory is set up as an SVN external.
if test ! -e thirdparty/gmock; then
    echo "Google Mock not present.  Fetching gmock-1.7.0 from the web..."
    curl $curlopts -L -O https://github.com/google/googlemock/archive/release-1.7.0.zip
    unzip -q release-1.7.0.zip
    rm release-1.7.0.zip
    mv googlemock-release-1.7.0 thirdparty/gmock

    curl $curlopts -L -O https://github.com/google/googletest/archive/release-1.7.0.zip
    unzip -q release-1.7.0.zip
    rm release-1.7.0.zip
    mv googletest-release-1.7.0 thirdparty/gmock/gtest
fi


cmake -DCMAKE_BUILD_TYPE=Debug .

gtags

