#!/bin/bash

echo "lauching compiler"

#rm -rf build/
#mkdir build/
cd build/

cmake -G "Unix Makefiles" ..
make
make install DESTDIR=../install
cd ..

