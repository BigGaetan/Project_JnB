
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wfatal-errors -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SRCS = main.cpp JnB.cpp Enemy.cpp Bullet.cpp carte.cpp musique.cpp  

# Header files
HDRS = JnB.h carte.h Enemy.h Bullet.h musique.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = test_sfml


# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp $(HDRS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


# Clean rule
clean:
	rm -f $(OBJS) $(TARGET) 
# pour ajouter de fichier écrire  main.cpp file1.cpp file2.cpp newfile.cpp
