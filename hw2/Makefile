.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++17 -O2 -Wall -Iinc

OBJS=DataGenerator.o
TARGET=decision_stump

%.o: src/%.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

$(TARGET): $(TARGET:=.o) $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $^

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET:=.o) $(OBJS)
