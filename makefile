cmake_minimum_required(VERSION 3.10)
project(TicTacToeSFML)

# Mengatur standar C++
set(CMAKE_CXX_STANDARD 11)

# Temukan paket SFML
find_package(SFML 2.5 REQUIRED graphics window system)

# Tentukan file sumber
set(SOURCES src/main.cpp)

# Buat executable
add_executable(TicTacToeSFML ${SOURCES})

# Link dengan SFML
target_link_libraries(TicTacToeSFML sfml-graphics sfml-window sfml-system)