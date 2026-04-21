g++ test.cpp -o test.out \
    -lgtest -lgtest_main -pthread \
    -lmylib -L. \
    -Wl,-rpath=.
 