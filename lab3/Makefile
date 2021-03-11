TARGET=lab3a
#OBJS=pwm_uniform.o main.o
OBJS=main.o
CFLAGS=-g -Wall

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} -lwiringPi

clean:
	rm -f ${TARGET} ${OBJS} 

#pwm_gaugelike.o: pwm_gaugelike.h
#main.o: pwm_gaugelike.o
