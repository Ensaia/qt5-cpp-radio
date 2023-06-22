#!/bin/bash
DIST_DIR=dist/miraath-linux
BUILD_DIR=build
ROOT_DIR=root

BIN_DIR=$ROOT_DIR/usr/bin
LIB_DIR=$ROOT_DIR/usr/lib

mkdir -p $DIST_DIR && cd $DIST_DIR
mkdir -p $BIN_DIR $LIB_DIR $BUILD_DIR

pushd $BUILD_DIR
$QTDIR/bin/qmake \
    -spec linux-g++ \
    "CONFIG += release" \
    ../../../Miraath.pro

make qmake_all
pushd gallery-core && make && make install ; popd
pushd gallery-desktop && make && make install ; popd
popd
