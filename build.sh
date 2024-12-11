#!/bin/bash

# Memeriksa apakah file sumber ada
if [ ! -f main.cpp ]; then
    echo "File main.cpp tidak ditemukan!"
    exit 1
fi

# Menggunakan pkgconf untuk mendapatkan flag kompilasi dan pustaka GTK
CFLAGS=$(pkgconf gtk+-3.0 --cflags)
LIBS=$(pkgconf gtk+-3.0 --libs)

# Mengompilasi program menggunakan g++
g++ -g main.cpp -o game_suit $CFLAGS $LIBS