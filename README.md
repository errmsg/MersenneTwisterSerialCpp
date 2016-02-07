# MersenneTwisterSerialCpp
Classic Mersenne twister algorithm for pseudorandom number generator (PRNG). It is serial, meaning that no parallelization is involved.
It is based on the code written by Takuji Nishimura and Makoto Matsumoto. Code is initially writing in C and ported to C++ (by me). Algorithm is 64 bit. See "mt_serial_h" for more.

## Installation
$ cd to/path/that/you/wish
$ git clone https://github.com/errmsg/MersenneTwisterSerialCpp.git


## Dependencies
* C++ STL
* Catch (included)

## Compilation
CMake is used to generate make files. It is strongly advised to run CMake in *build* directory.
When CMake is done generating make files, you can use make to compile the sources files. After that
you can run the executables (as shown below).


   $ cd build
   $ cmake -G "Unix Makefiles" ..
   $ make
   $ ./MersenneTwisterSerialCppTest (initial seed) (number of outputs)
   $ ./MersenneTwisterSerialCppTestWithCatch 


Both **initial seed** and **number of outputs** are unsigned integers.

## Testing
Cacth is used for testing. See *tests*. Test files are compiled with CMake.

**IMPORTANT NOTE** OpenCL part of the repo is tested only in OS X.

## Tasks
- [x] Porting algorithm to C++
- [x] Testing for Mersenne twister via [catch](https://github.com/philsquared/Catch) framework (tests/catchTest.cpp)
- [x] OpenCL basic example (opencl/times_two.cpp)
- [x] CMake integration
- [ ] Mersenne twister algorithm parallelization (with OpenCL)

## Notes
I will probably move the parallelized algorithm to another repo. I'll post the link when I'm done.

## License
MIT
