# Implementation of Decision Stump Algorithm

I implemented the algorithm in *C++17* and plotted the histograms with the help of *PGFPlots*.
But the latter is not included here.

## Usage

This program is tested (compilable and executable) in the environment:
- **Kernel**: Archlinux 5.3.13
- **g++ (GCC)**: 9.2.0
- **CPU**: Intel i7-9700K

To compile the program, simply

~~~bash
cmake . && cmake --build .
~~~

After compilation, a program named *decision_stump* will be generated.
Then you can run the experiment in problem 7 with

~~~bash
./decision_stump 20
~~~

And run the experiment in problem 8 with

~~~bash
./decision_stump 2000
~~~
