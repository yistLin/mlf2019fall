.PHONY: all clean exp

CC=g++
CFLAGS=-std=c++11 -O2

TARGET=pla

all: $(TARGET)

$(TARGET): src/$(TARGET:=.cpp)
	$(CC) -o $@ $^ $(CFLAGS)

EXP1_CSV=exp1_records.csv
EXP1_PNG=exp1_histogram.png
EXP1_OUT=$(EXP1_*)

exp1:
	./pla < data/hw1_6_train.dat > $(EXP1_CSV) && python scripts/plot_histogram.py $(EXP1_CSV) $(EXP1_PNG)

clean:
	rm -f $(TARGET) $(EXP1_CSV) $(EXP1_PNG)
