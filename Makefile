CC = gcc
CFLAGS = -Wall -std=c99

TARGET = showFDtables

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) process.c -o $@
