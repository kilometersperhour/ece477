TARGET=lab5a
#OBJS=picode.o
OBJS=avrcode.o
CFLAGS=-g -Wall

${TARGET}: ${OBJS}
	#${CC} -g -o ${TARGET} ${OBJS} -lwiringPi
	${CC} -g -o ${TARGET} ${OBJS}

clean:
	rm -f ${TARGET} ${OBJS} 
