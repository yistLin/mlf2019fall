# Implementation of PLA and Pocket Algorithm

I implemented the algorithms in *C++*, and plotted the results with *Python* using *matplotlib*.

## Usage

### Compile the Program

To compile the program, type

~~~bash
make
~~~

After compilation, 3 program `pla`, `pocket` and `pocket2` will be generated.

### Run the Experiments

To run the program and plot the result, just type

~~~bash
make exp1 && make exp2 && make exp3
~~~

This will produce 3 CSVs and 3 PNGs.
They are `exp1_records.csv`, `exp2_records.csv`, `exp3_records.csv` and `exp1_histogram.png`, `exp2_histogram.png`, `exp3_histogram.png`.

### Clean Out

Simply type

~~~bash
make cleanall
~~~

to clean everything including executables and the results of experiments.
