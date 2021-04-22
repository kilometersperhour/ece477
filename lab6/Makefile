TARGET=lab6a
OBJS=picode.o
#OBJS=avrcode.o
CFLAGS=-g -Wall

${TARGET}: ${OBJS}
	${CC} -g -o ${TARGET} ${OBJS} -lwiringPi

clean:
	rm -f ${TARGET} ${OBJS} 
