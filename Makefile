#CC=gcc
CC=nvcc

dct: dct.cu
	${CC}  -o dct dct.cu -lm
clean:
	rm -f dct
