# Compiler
CC = ccache gcc
# Compiler Flags:
# -Wall: Aktiviert alle Warnungen
# -Wextra: Aktiviert zusätzliche Warnungen
INCLUDES = -I. -Iinclude
# Holt die Compiler-Flags von externen Paketen
PKG_CFLAGS = $(shell pkg-config --cflags glib-2.0 gtk4 libadwaita-1)
# linker config
# Holt die Linker-Flags von externen Paketen
PKG_LIBS = $(shell pkg-config --libs glib-2.0 gtk4 libadwaita-1)

# Zusammengefasste Compiler Flags für die Kompilierung aller .c Dateien
CFLAGS = -Wall -Wextra -fPIC $(PKG_CFLAGS) $(INCLUDES)
# Linker Flags für das endgültige Programm
LIBS = $(PKG_LIBS)

# Name des fertigen Programms
TARGET = esnap

# Quell- und Objektdateien
SRCS = $(shell find . -name '*.c')
OBJS = $(SRCS:.c=.o)
HEADERS = $(shell find . -name '*.h')

# Standard-Ziel: Erstellt das Programm
all: $(TARGET)

# Linken: Erstellt das Zielprogramm aus den Objektdateien
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

# Kompilieren: Erstellt Objektdateien aus den Quell-Dateien
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Bereinigen: Entfernt das Zielprogramm und alle Objektdateien
clean:
	rm -f $(TARGET) $(OBJS)
