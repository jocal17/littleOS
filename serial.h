#ifndef SERIAL_H
#define SERIAL_H

#include "io.h"
#include "stdint.h"

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
    * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
    * order, but they start at different values.
    */

#define COM1 0x3F8 /* COM1 base port */

#define S_DATA(base) (base)
#define S_INTERRUPT(base) (base + 1)
#define S_FIFO_COMMAND(base) (base + 2)
#define S_LINE_COMMAND(base) (base + 3)
#define S_MODEM_COMMAND(base) (base + 4)
#define S_LINE_STATUS(base) (base + 5)

/* The I/O port commands */

/* _LINE_ENABLE_DLAB:
    * Tells the serial port to expect first the highest 8 bits on the data port,
    * then the lowest 8 bits will follow
    */
#define LINE_ENABLE_DLAB 0x80

/** serial_configure_baud_rate:
    *  Sets the speed of the data being sent. The default speed of a serial
    *  port is 115200 bits/s. The argument is a divisor of that number, hence
    *  the resulting speed becomes (115200 / divisor) bits/s.
    *
    *  @param com      The COM port to configure
    *  @param divisor  The divisor
    */

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */

/* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */

int serial_is_transmit_fifo_empty(unsigned int com);

void serial_init(int com);

void serial_write(unsigned short com, unsigned char data);

#endif
