all: lib test

lib:
	g++ -fPIC -shared int.cpp -o libmylib.so

test: test.cpp
	g++ test.cpp -o test.out \
    -lgtest -lgtest_main -pthread \
    -lmylib -L. \
    -Wl,-rpath=.
 
clean:
	rm -f test.out libmylib.so