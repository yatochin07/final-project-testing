#!/bin/bash

# Memeriksa apakah file sumber ada
if [ ! -f main.cpp ]; then
    echo "File main.cpp tidak ditemukan!"
    exit 1
fi

# Menggunakan pkg-config untuk mendapatkan flag kompilasi dan pustaka GTK
CFLAGS=$(pkg-config --cflags gtk+-3.0)
LIBS=$(pkg-config --libs gtk+-3.0)

# Mengompilasi program menggunakan g++
g++ -g main.cpp -o game_suit $CFLAGS $LIBS