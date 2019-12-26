# Implementation of Logistic Regression

I implemented the algorithms in *C++17* and plotted the histograms with the help of *PGFPlots*.

## Usage

This program is tested (compilable and executable) in the environment:
- **Kernel**: Archlinux 5.4.6
- **g++ (GCC)**: 9.2.0
- **CPU**: Intel i7-9700K

To compile the program,

~~~bash
cmake . && cmake --build .
~~~

And to run the program,

~~~bash
./problem7 data/hw3_train.dat data/hw3_test.dat
# or
./problem8 data/hw3_train.dat data/hw3_test.dat
~~~

Both the above program will output to STDOUT in CSV format.
