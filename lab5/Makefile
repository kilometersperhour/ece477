TARGET=lab5a
OBJS=picode.o
CFLAGS=-g -Wall

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} -lwiringPi

clean:
	rm -f ${TARGET} ${OBJS} 
