# create third-party-libs
mkdir -p ../third-party-libs

# install cmake
VERSION_CMAKE="3.17.2"
wget https://github.com/Kitware/CMake/releases/download/v3.17.2/cmake-${VERSION_CMAKE}-Linux-x86_64.tar.gz
tar xvf cmake-${VERSION_CMAKE}-Linux-x86_64.tar.gz -C ../third-party-libs/
mv ../third-party-libs/cmake-${VERSION_CMAKE}-Linux-x86_64 ../third-party-libs/cmake
rm -f cmake-${VERSION_CMAKE}-Linux-x86_64.tar.gz

# install gtest
PATH=${PWD}/../third-party-libs/cmake/bin:${PATH}
VERSION_GTEST="1.10.0"
wget https://github.com/google/googletest/archive/release-${VERSION_GTEST}.tar.gz
tar xvf release-${VERSION_GTEST}.tar.gz
cd googletest-release-${VERSION_GTEST}/
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/leetcode/third-party-libs/gtest ../
make -j && make install
cd ../../
rm -rf xvf release-${VERSION_GTEST}.tar.gz googletest-release-${VERSION_GTEST}/