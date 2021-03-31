#!/bin/bash

# get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd ${DIR}

# install cmake
VERSION_CMAKE="3.17.2"
wget https://github.com/Kitware/CMake/releases/download/v${VERSION_CMAKE}/cmake-${VERSION_CMAKE}-Linux-x86_64.tar.gz -O - | tar xvz 
mv cmake-${VERSION_CMAKE}-Linux-x86_64 ${DIR}/../third-party-libs/cmake

# install gtest
PATH=${DIR}/../third-party-libs/cmake/bin:${PATH}
VERSION_GTEST="1.10.0"
wget https://github.com/google/googletest/archive/release-${VERSION_GTEST}.tar.gz -O - | tar xvz
cd googletest-release-${VERSION_GTEST}/
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX=${DIR}/../third-party-libs/gtest ../
make -j && make install
cd ${DIR}
rm -rf googletest-release-${VERSION_GTEST}/
