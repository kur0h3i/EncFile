
# Configuracion Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Nombre del ejecutable
TARGET = encfile

# Archivos fuente
SRC = main.cpp 

# Reglas de compilacion
all: 
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Ejecucion
run: all
	./$(TARGET)	

# Limpieza de archivos compilados
clean:
	rm -f $(TARGET) 
