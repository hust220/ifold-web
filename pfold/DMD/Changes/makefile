CC = gcc 
OFLAG = -O2

dmd-en.linux: phipsi.o hydrogenbond.o bcp.o make_system.o search.o controls.o cluster.o corr_func.o movie.o bonds.o rms.o
	${CC} ${OFLAG} -o dmd-en.linux -lm phipsi.o hydrogenbond.o bcp.o make_system.o search.o controls.o cluster.o movie.o bonds.o rms.o corr_func.o 

phipsi.o:phipsi.c
	${CC} -c ${OFLAG} phipsi.c

hydrogenbond.o:hydrogenbond.c hydrogenbond.h
	${CC} -c ${OFLAG} hydrogenbond.c

bcp.o: bcp.c bcp.h hydrogenbond.h make_system.h controls.h cluster.h movie.h search.h bonds.h rms.h corr_func.h
	${CC} -c ${OFLAG} bcp.c

make_system.o: make_system.c bcp.h make_system.h controls.h cluster.h search.h movie.h bonds.h rms.h corr_func.h  
	${CC} -c ${OFLAG} make_system.c

search.o: bcp.h controls.h search.h search.c
	${CC} -c ${OFLAG} search.c

controls.o: controls.c bcp.h controls.h cluster.h
	${CC} -c ${OFLAG} controls.c

cluster.o: cluster.c bcp.h bonds.h cluster.h controls.h rms.h
	${CC} -c ${OFLAG} cluster.c

movie.o: movie.c bcp.h controls.h rms.h bonds.h make_system.h
	${CC} -c ${OFLAG} movie.c

bonds.o: bonds.c bonds.h 
	${CC} -c ${OFLAG} bonds.c

rms.o: rms.c rms.h bcp.h controls.h search.h
	${CC} -c ${OFLAG} rms.c

corr_func.o: corr_func.c bcp.h corr_func.h controls.h bonds.h 
	${CC} -c ${OFLAG} corr_func.c


clean:
	rm -rf *.o
