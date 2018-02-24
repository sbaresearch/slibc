# Introduction
This library provides an implementation of the bounds-checking C functions 
(as specified in Annex K of the current C standard, a.k.a. C11) for use with
the GNU C library. 

These functions lower the risk of introducing security vulnerabilities
such as buffer overflows and format string vulnerabilities into your code by providing 
clear and easy-to-use interfaces. For each C function a secure alternate function ending
in a "_s" postfix is provided (e.g., strcpy_s). Use of these functions is recommended 
by security experts and secure coding standards (CERT Secure Coding Standard C). 

This library consists of
* a thread-safe implementation of all functions specified in the ISO Standard (except widechar functions)
* API documentation for all functions
* test cases for all functions
* overloaded C++ template functions for easier use when compiling with g++ 


# How to compile the library
1. Compile the slibc libary by typing "make". 
   Slibc is compiled as a shared library (libslibc.so). To link with the shared library, add -lslibc to your linker step.

2. Optionally run all tests by executing make test. 


# Use SLIBC with your program
1. Use the new _s functions in your code:

    ```#include <string.h>
    int main(int argc, char *argv[])
    {
            char dest[10];
            strcpy_s(dest, sizeof(dest), argv[0]);
    }

2. When compiling include the SLIBC header directory (include/slibc) in your
   compiler's include path (e.g., add -I~/slibc/include/slibc). Remember 
   that Annex K adds functions to the standard C library by extending 
   existing header files. SLIBC makes the fact that it's a third-party library 
   (instead of being part of GLIBC) as transparent as possible to your program. 
   To use strcpy_s, simply include string.h in your program. It is important 
   that your compiler searches in the slibc header directory first.

3. Link your program to Slibc. Slibc is built as a shared library. 
   Add -lslibc to your linking step. 
   Additionally, you might have to add the location of slibc's so-files to your Linker 
   search path by adding -L (e.g., -L../src/).

4. Run your program. If the Slibc shared object file cannot be found, you have to adjust 
   the environment variable LD_LIBRARY_PATH. 


# Directory layout
* "include/slibc" contains the public header files
* "src/" contains the implementation
* "tests_slibc/" contains our c++ based test-suite for slibc
* "tests_ow/" contains the open watcom tests.