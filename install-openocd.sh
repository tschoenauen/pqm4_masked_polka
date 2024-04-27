#! /bin/bash

TARGET_CLONE=~/mytools
INSTALL_DIR="$HOME/.local"

OPENOCD_GIT=https://github.com/openocd-org/openocd

mkdir -p $TARGET_CLONE
mkdir -p $INSTALL_DIR

# clone git 
(cd $TARGET_CLONE && git clone $OPENOCD_GIT)

# make install
echo "INSTALL into $INSTALL_DIR"
(cd $TARGET_CLONE/openocd && ./bootstrap && ./configure --prefix=$INSTALL_DIR && make -j 40 && make install)
