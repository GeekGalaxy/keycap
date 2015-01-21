#!/bin/sh

g++ -static -std=c++11 main.cpp -o keycap.exe
strip keycap.exe
upx keycap.exe

