#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

/* The I/O ports */
#define FRAMEBUFFER          0x000B8000
#define FB_COMMAND_PORT      0x3D4
#define FB_DATA_PORT         0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15


#define BLACK 0
#define WHITE 15


void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void fb_move_cursor(unsigned short pos);

int write(char *buf, unsigned int len);

#endif
