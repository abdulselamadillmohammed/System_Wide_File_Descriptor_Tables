CC = gcc
CFLAGS = -Wall -std=c99

TARGET = showFDtables

SRC = main.c parser.c table.c proc.c output.c
OBJ = $(SRC:.c=.o)

HEADERS = parser.h table.h proc.h output.h

# Default
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: dist
dist:
	tar -czf showFDtables.tar.gz $(SRC) $(HEADERS) Makefile README.md

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET) showFDtables.tar.gz

.PHONY: help
help:
	@echo "Available commands:"
	@echo "make       - build the project"
	@echo "make clean - remove object files and executable"
	@echo "make dist  - package source files"
	@echo "make help  - show this message"