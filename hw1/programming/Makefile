.PHONY: all clean exp

CC=g++
CFLAGS=-std=c++11 -O2
TARGET=pla

all: $(TARGET)

$(TARGET): src/$(TARGET:=.cpp)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(TARGET)
