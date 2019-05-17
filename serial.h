
#ifndef SERIAL_H
#define SERIAL_H

#include "io.h"

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
    * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
    * order, but they start at different values.
    */

#define COM1                0x3F8      /* COM1 base port */

#define BASE(base)          (base)
#define INTERRUPT(base)     (base + 1)
#define FIFO_CONTROL(base)  (base + 2)
#define LINE_CONTROL(base)  (base + 3)
#define MODEM_CONTROL(base) (base + 4)
#define LINE_STATUS(base)   (base + 5)

#define UNSET(port) outb(LINE_CONTROL(port), inb(port) & 0x7F)


int serial_is_transmit_fifo_empty(unsigned int com);

void serial_init(int com);

void serial_write(unsigned short com, unsigned char data);


#endif
