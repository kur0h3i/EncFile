# Configuracion Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lssl -lcrypto

# Directorios
BIN_DIR = bin
TARGET = $(BIN_DIR)/encfile

# Archivos fuente
SRC = main.cpp src/User.cpp src/Vault.cpp

# Reglas de compilacion
all: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Crear directorio bin si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Ejecucion
run: all
	./$(TARGET)

# Limpieza de archivos compilados
clean:
	rm -rf $(BIN_DIR)