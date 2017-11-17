all: matrix

matrix: Matrix.o matlab.o test.o
	g++ Matrix.o matlab.o test.o -o matrix

CMatrix.o: Matrix.cpp
	g++ -c Matrix.cpp

CMatrix.o: matlab.cpp
	g++ -c matlab.cpp

CMatrix.o: test.cpp
	g++ -c test.cpp

