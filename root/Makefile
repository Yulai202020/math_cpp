all: lib test

lib: lib_newton # defualt

chords:
	g++ -fPIC -shared chord_method.cpp -o libmylib.so

newton:
	g++ -fPIC -shared newton_method.cpp -o libmylib.so

binary:
	g++ -fPIC -shared binary_method.cpp -o libmylib.so

test: test.cpp
	g++ test.cpp -o test.out \
    -lgtest -lgtest_main -pthread \
    -lmylib -L. \
    -Wl,-rpath=.
 
clean:
	rm -f test.out libmylib.so