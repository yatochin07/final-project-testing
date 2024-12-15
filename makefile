CXX = g++
CXXFLAGS = -std=c++14 -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = game

# Target default: mengkompilasi dan menghubungkan
all: $(EXEC)

$(EXEC): $(OBJS)
    $(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Kompilasi file .cpp menjadi .o
.cpp.o:
    $(CXX) $(CXXFLAGS) -c $<

# Menghapus file objek dan eksekusi
clean:
    rm -f $(OBJS) $(EXEC)


g++ -std=c++14 -Wall -I/usr/include/SFML -L/usr/lib64 -lsfml-graphics -lsfml-window -lsfml-system main.cpp -o game