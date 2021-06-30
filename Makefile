CC=gcc
AR=ar
#CC=nvcc

#CFLAGS=  -D__CUDA__
CFLAGS=  

all:dct idct sn

dct: dct.c libutility.a
	${CC}  ${CFLAGS} -o dct dct.c -lm -L./  -lutility

idct: idct.c libutility.a
	${CC}  ${CFLAGS} -o idct idct.c -lm -L./ -lutility

sn: sn.c libutility.a
	${CC}  ${CFLAGS} -o sn sn.c -lm -L./ -lutility

 libutility.a: utility.o
	${AR}  r libutility.a utility.o 

 utility.o: utility.c
	${CC}  ${CFLAGS} -c utility.c 


clean:
	rm -f dct idct sn *.o
