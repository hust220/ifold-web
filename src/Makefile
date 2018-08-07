all: ../bin/genDMD-TXT.linux ../bin/movie2pdbs.linux ../bin/pdb2nat.linux ../bin/movie2freqs.linux

CC = g++
OFLAG = -O3
IFLAG = -I../include

../bin/genDMD-TXT.linux: temp.o ran1.o gasdev.o
	${CC} ${OFLAG} -o ../bin/genDMD-TXT.linux temp.o ran1.o gasdev.o

genDMD-TXT.o: genDMD-TXT.cpp
	${CC} ${IFLAG} ${OFLAG} -c genDMD-TXT.cpp

temp.o: temp.cpp
	${CC} ${IFLAG} ${OFLAG} -c temp.cpp

ran1.o: ran1.c
	${CC} ${IFLAG} ${OFLAG} -c ran1.c

gasdev.o: gasdev.c
	${CC} ${IFLAG} ${OFLAG} -c gasdev.c

../bin/movie2pdbs.linux: movie.o movie2pdbs.o
	${CC} ${IFLAG} ${OFLAG} -o ../bin/movie2pdbs.linux movie.o movie2pdbs.o

../bin/movie2freqs.linux: movie.o movie2Freq.o
	${CC} ${IFLAG} ${OFLAG} -o ../bin/movie2freqs.linux movie.o movie2Freq.o

movie.o: movie.cpp
	${CC} ${IFLAG} ${OFLAG} -c movie.cpp

movie2pdbs.o: movie2pdbs.cpp
	${CC} ${IFLAG} ${OFLAG} -c movie2pdbs.cpp

movie2Freq.o: movie2Freq.cpp
	${CC} ${IFLAG} ${OFLAG} -c movie2Freq.cpp

../bin/pdb2nat.linux: pdb2nat.o
	${CC} ${OFLAG} -o ../bin/pdb2nat.linux pdb2nat.o

pdb2nat.o: pdb2nat.cpp
	${CC} ${IFLAG} ${OFLAG} -c pdb2nat.cpp

clean:
	rm -rf *.o
