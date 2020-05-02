# set PATH and LD_LIBRARY_PATH
ABS_PATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
echo "Please set PATH and LD_LIBRARY_PATH by the following commands:"
echo "export PATH=${ABS_PATH}/../third-party-libs/cmake/bin:\${PATH}"
echo "export LD_LIBRARY_PATH=${ABS_PATH}/../third-party-libs/gtest/bin:\${LD_LIBRARY_PATH}"