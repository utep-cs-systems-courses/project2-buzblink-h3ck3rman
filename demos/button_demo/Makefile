# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf 

#additional rules for files
button.elf: ${COMMON_OBJECTS} stateMachines.o wdInterruptHandler.o p1_interrupt_handler.o led.o buzzer.o switches.o toyMain.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: button.elf
	msp430loader.sh button.elf

clean:
	rm -f *.o *.elf

buttonMain.o: led.h buzzer.h switches.h stateMachines.h

switches.o: switches.h led.h

buzzer.o: buzzer.h

stateMachines: led.h buzzer stateMachines.h

wdInterruptHandler.o: stateMachines.h

led.o: led.h
