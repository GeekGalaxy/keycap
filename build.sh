#!/bin/sh

g++ -static -std=c++11 -Wall -Wextra -Werror \
-Weffc++ -pedantic-errors main.cpp -o keycap.exe
strip keycap.exe
upx keycap.exe

