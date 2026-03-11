CC = gcc
CFLAGS = -Wall -std=c99

TARGET = showFDtables

all: $(TARGET)

$(TARGET): process.c
	$(CC) $(CFLAGS) process.c -o $@
