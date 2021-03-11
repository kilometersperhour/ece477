TARGET=lab2a
#OBJS=pwm_uniform.o main.o
OBJS=main.o
CFLAGS=-g -Wall

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} -lwiringPi

clean:
	rm -f ${TARGET} ${OBJS} 

#pwm_uniform.o: pwm_uniform.h
#main.o: pwm_uniform.o
