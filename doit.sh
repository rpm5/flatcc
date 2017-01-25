#!/bin/bash

set -e

topdir=$(pwd)

ln -sf build.cfg.make scripts/build.cfg

# +++ scripts/cleanall.sh
echo "removing build products"
rm -rf build
rm -rf release
rm -f bin/flatcc*
rm -f bin/bfbs2json*
rm -f lib/libflatcc*
[ -d bin ] && rmdir bin
[ -d lib ] && rmdir lib
# --- scripts/cleanall.sh

# +++ scripts/initbuild.sh [$1=make]
FLATCC_BUILD_GEN="Unix Makefiles"
#FLATCC_BUILD_CMD="make VERBOSE=1"
FLATCC_BUILD_CMD="make -j"

echo "initializing build for CMake $FLATCC_BUILD_GEN ($FLATCC_BUILD_CMD)"

DIRS="Debug Release"

for DIR in $DIRS; do
  cd "${topdir}"
  rm -rf "build/$DIR"
  mkdir -p "build/$DIR"
  cd "build/$DIR"
  cmake -G "$FLATCC_BUILD_GEN" -DCMAKE_BUILD_TYPE="$DIR" \
	-DCMAKE_C_FLAGS:STRING="-O2 -g" \
	-DCMAKE_C_FLAGS_RELEASE:STRING="-DNDEBUG" \
	-DCMAKE_CXX_FLAGS_RELEASE:STRING="-DNDEBUG" \
	-DCMAKE_Fortran_FLAGS_RELEASE:STRING="-DNDEBUG" \
	-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
	-DCMAKE_INSTALL_PREFIX:PATH=/usr \
	-DINCLUDE_INSTALL_DIR:PATH=/usr/include \
	-DLIB_INSTALL_DIR:PATH=/usr/lib64 \
	-DSYSCONF_INSTALL_DIR:PATH=/etc \
	-DSHARE_INSTALL_PREFIX:PATH=/usr/share \
	-DLIB_SUFFIX=64 \
	-DBUILD_SHARED_LIBS:BOOL=ON \
    -DFLATCC_PORTABLE=OFF \
    -DFLATCC_RTONLY=OFF \
    -DFLATCC_INSTALL=ON \
    -DFLATCC_TEST=ON \
    -DFLATCC_COVERAGE=OFF \
    -DFLATCC_DEBUG_VERIFY=OFF \
    -DFLATCC_REFLECTION=ON \
    -DFLATCC_NATIVE_OPTIM=OFF \
    -DFLATCC_FAST_DOUBLE=OFF \
    -DFLATCC_ALLOW_PEDANTIC=OFF \
    -DFLATCC_ALLOW_WERROR=OFF \
    -DFLATCC_ALLOW_WSUGGEST_CONST=OFF \
    -DFLATCC_ALLOW_WSUGGEST_PURE=OFF \
    -DFLATCC_ALLOW_WSUGGEST_NORETURN=OFF \
    -DFLATCC_ALLOW_SANITIZE_ADDRESS=OFF \
    -DFLATCC_IGNORE_CONST_COND=OFF \
	../..
  cd "${topdir}"
done
# --- scripts/initbuild.sh

# +++ scripts/build.sh
mkdir -p bin && rm -f bin/flatcc{,_d}
mkdir -p lib && {
  rm -f lib/libflatcc{,_d}.*
  rm -f lib/libflatccrt{,_d}.*
}

for DIR in $DIRS; do
  echo "===> $DIR: building " 1>&2
  cd "build/$DIR" && $FLATCC_BUILD_CMD
  cd "${topdir}"
done
# --- scripts/build.sh

# +++ scripts/test.sh
for DIR in $DIRS; do
  echo "===> $DIR: testing" 1>&2
  cd "build/$DIR" && ctest "$topdir"
  cd "${topdir}"
done
# --- scripts/test.sh

DIR=Release
echo "===> $DIR: load_test"
build/$DIR/test/load_test/load_test
echo "----"

# +++ scripts/benchmark.sh
# +++ test/benchmark/benchall.sh
cd test/benchmark && {
  BENCHDIRS="benchraw benchflatc benchflatcc benchflatccjson"
  for DIR in $BENCHDIRS; do
    echo "===> $DIR: building and benchmarking ..."
    "$DIR"/run.sh
  done
}
cd "${topdir}"
# --- test/benchmark/benchall.sh
# --- scripts/benchmark.sh

cd build/Release
sudo make install
cd "${topdir}"

