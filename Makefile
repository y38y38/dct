CC=gcc
#CC=nvcc

#CFLAGS=  -D__CUDA__
CFLAGS=  

dct: dct.c
	${CC}  ${CFLAGS} -o dct dct.c -lm
clean:
	rm -f dct
