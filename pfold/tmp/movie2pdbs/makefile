all: ../bin/movie2pdbs.linux ../bin/movie2Freq.linux

../bin/movie2pdbs.linux: movie.o movie2pdbs.o
	g++ -O3 movie.o movie2pdbs.o -o ../bin/movie2pdbs.linux

../bin/movie2Freq.linux: movie.o movie2Freq.o
	g++ -O3 movie.o movie2Freq.o -o ../bin/movie2Freq.linux

movie2Freq.o: movie2Freq.cpp
	g++ -c movie2Freq.cpp

movie.o: movie.cpp movie.h
	g++ -c movie.cpp 

movie2pdbs.o: movie2pdbs.cpp
	g++ -c movie2pdbs.cpp

clean:
	rm -rf movie.o movie2pdbs.o movie2Freq.o
