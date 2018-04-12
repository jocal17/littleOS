#include "serial.h"
#include "io.h"

void serial_init(int com) {
    outb(com + INTERRUPT(com), 0x00);       // Disable all interrupts
    outb(com + LINE_COMMAND(com), 0x80);    // Enable DLAB (set baud rate divisor)
    outb(com + DATA(com), 0x03);            // Set divisor to 3 (lo byte) 38400 baud
    outb(com + INTERRUPT(com), 0x00);       //                  (hi byte)
    outb(com + LINE_COMMAND(com), 0x03);    // 8 bits, no parity, one stop bit
    outb(com + FIFO_COMMAND(com), 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(com + MODEM_COMMAND(com), 0x0B);   // IRQs enabled, RTS/DSR set
}

int serial_is_transmit_fifo_empty(unsigned int com) {
    /* 0x20 = 0010 0000 */
    return inb(LINE_STATUS(com)) & 0x20;
}

void serial_write(unsigned short com, unsigned char data) {
    while (!serial_is_transmit_fifo_empty(com)) {

    }
    outb(DATA(com), data);
}
