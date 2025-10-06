
# Configuracion Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lstdc++fs

# Nombre del ejecutable
TARGET = encfile

# Archivos fuente
SRC = main.cpp \
	src/User.cpp 

# Reglas de compilacion
all: 
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Ejecucion
run: all
	./$(TARGET)	

# Limpieza de archivos compilados
clean:
	rm -f $(TARGET) 
