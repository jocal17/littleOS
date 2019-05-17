/*
 * This file contains the code for writing to the serial port.
 * There are four ports each with twelve registers. However,
 * they are mapped to only eight distinct addresses. The register
 * being addressed depends on whether we are reading or writing
 * and whether the Divisor Latch Access Bit is set. The eighth
 * bit of the Line Control register functions as the DLAB.
 */

#include "serial.h"
#include "io.h"

void serial_init(int com) {
        outb(LINE_CONTROL(com), 0x80);   // Set DLAB.
        outb(BASE(com), 0x03);           // With DLAB set, offset 0 is the Divisor Latch Low Byte.
        UNSET(com);                      // Unset the DLAB.
        outb(INTERRUPT(com), 0x00);      // Divisor Latch High Byte.
        outb(LINE_CONTROL(com), 0x03);   // Set the line protocol.
        outb(FIFO_CONTROL(com), 0xC7);   // Enable FIFO and configures the queue size to 14 bytes.
        outb(MODEM_CONTROL(com), 0x03);  // RTS and DSR set.
}

// To prevent writing to a full buffer.
int serial_is_transmit_fifo_empty(unsigned int com) {
        return inb(LINE_STATUS(com)) & 0x20;
}

void serial_write(unsigned short com, unsigned char data) {
        while (!serial_is_transmit_fifo_empty(com));
        outb(BASE(com), data);
}

