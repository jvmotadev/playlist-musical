# Makefile para compilar o projeto da playlist

# Compilador C
CC = gcc

# Flags de compilação: -g para debug, -Wall para todos os warnings
CFLAGS = -g -Wall

# Arquivos fonte
SOURCES = main.c playlist.c

# Arquivos objeto
OBJECTS = $(SOURCES:.c=.o)

# Nome do executável final
TARGET = player

# Regra principal: compila tudo
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar cada arquivo .c em um .o
%.o: %.c playlist.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJECTS) $(TARGET)