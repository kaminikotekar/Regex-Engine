CC = gcc
CFLAGS = -I include
IDIR = src
ODIR = build
TARGET = bin/run/engine
SOURCEF = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

execute: build
	$(TARGET) run

test: build
	$(TARGET) test

build: $(SOURCEF)
	@echo "Linking and compiling ....."
	$(CC) $^ -o $(TARGET)

$(ODIR)/%.o: $(IDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -f $(ODIR)/*.o bin/run/NFA data/raw/regex.log

.PHONY: clean



