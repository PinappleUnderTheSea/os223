#!/bin/bash

rm -r build
mkdir build
cd build
cmake ..
make -j
make install
pkill dde-dock
dde-dock