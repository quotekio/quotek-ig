#!/bin/bash

rm -rf CMakeFiles
rm -rf CMakeCache.txt
rm Makefile
cmake .
make

