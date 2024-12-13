# Nama kompilator dan flag
CXX = g++
CXXFLAGS = -std=c++17 -I./TIC-TAC-TOE -I./SUDOKU -I./SUIT -I./TTS

# Nama file output
TARGET = game_program

# Daftar file sumber (semua .cpp dalam subfolder)
SOURCES = main.cpp \
          TIC-TAC-TOE/game1.cpp \
          SUDOKU/game2.cpp \
          SUIT/game3.cpp \
          TTS/game4.cpp

# Daftar file objek yang dihasilkan
OBJECTS = $(SOURCES:.cpp=.o)

# Aturan untuk membangun target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Aturan untuk mengompilasi file .cpp menjadi file objek .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Aturan untuk membersihkan file objek dan target
clean:
	rm -f $(OBJECTS) $(TARGET)