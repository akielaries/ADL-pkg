#!/usr/bin/sh

# test all modules together with googletest. produce ONE .info coverage
# file for the whole test suite. 
g++ -std=c++2a -Wno-unused-result -Wparentheses -Wsign-compare -DNDEBUG -g -O3 -Wall --coverage \
    arith/t_arith.cpp ../modules/arithmetic/arith.cpp \
    calc/t_calc.cpp ../modules/calculus/deriv.cpp \
    nt/t_cipher.cpp ../modules/nt/cipher.cpp \
    nt/t_rc4.cpp ../modules/nt/rc4.cpp \
    nt/t_primes.cpp ../modules/nt/primes.cpp \
    nt/t_factorization.cpp ../modules/nt/factorization.cpp \
    nt/t_logarithms.cpp ../modules/nt/logarithms.cpp \
    t_threadpool.cpp \
    -lgtest -lgtest_main -o openMTPK_tests -fprofile-arcs -ftest-coverage -fPIC

# run compiled binary
./openMTPK_tests

#number_theory/t_rc4.cpp ../modules/number_theory/rc4.cpp \
# generate lcov files
lcov --directory . --capture --output-file lcov.info
# move lcov file to .coverage
mv lcov.info ../.coverage

# cd into root directory and run gcovr from here
cd ../ && gcovr --xml-pretty >> lcov.xml && mv lcov.xml .coverage/

