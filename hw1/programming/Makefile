.PHONY: all clean exp1

CC=g++
CFLAGS=-std=c++11 -O2
TARGET=pla pocket pocket2

all: $(TARGET)

pla: src/pla.cpp
	$(CC) -o $@ $< $(CFLAGS)

pocket: src/pocket.cpp
	$(CC) -o $@ $< $(CFLAGS)

pocket2: src/pocket.cpp
	$(CC) -o $@ $< $(CFLAGS) -DRETURNW

EXP1_CSV=exp1_records.csv
EXP1_PNG=exp1_histogram.png
EXP2_CSV=exp2_records.csv
EXP2_PNG=exp2_histogram.png
EXP3_CSV=exp3_records.csv
EXP3_PNG=exp3_histogram.png

exp1:
	./pla 777 data/hw1_6_train.dat > $(EXP1_CSV) && python scripts/plot_update_times_hist.py $(EXP1_CSV) $(EXP1_PNG)

exp2:
	./pocket 777 data/hw1_7_train.dat data/hw1_7_test.dat > $(EXP2_CSV) && python scripts/plot_g_error_rate_hist.py $(EXP2_CSV) $(EXP2_PNG)

exp3:
	./pocket2 777 data/hw1_7_train.dat data/hw1_7_test.dat > $(EXP3_CSV) && python scripts/plot_w_error_rate_hist.py $(EXP3_CSV) $(EXP3_PNG)

cleanall: clean cleanexp

clean:
	rm -f $(TARGET)

cleanexp:
	rm -f $(EXP1_CSV) $(EXP1_PNG) $(EXP2_CSV) $(EXP2_PNG) $(EXP3_CSV) $(EXP3_PNG)
