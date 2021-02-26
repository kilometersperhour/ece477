TARGET=lab02a
OBJS=pwm_uniform.o main.o
CFLAGS=-g -Wall

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS}

clean:
	rm -f ${TARGET} ${OBJS} 

pwm_uniform.o: pwm_uniform.h
main.o: pwm_uniform.o
