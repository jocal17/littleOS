#include "framebuffer.h"
#include "io.h"

static int position = 0;

void fb_write_cell(unsigned int i, char c, unsigned char bg, unsigned char fg) {
    volatile char *fb = (volatile char *) FRAMEBUFFER;
    fb[i*2] = c;
    fb[i*2+1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}


void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

int fb_write(char *buf, unsigned int len) {
    char c;
    for (unsigned int i = 0; i < len; i++) {
        c = buf[i];
        fb_write_cell(i, c, BLACK, WHITE);
        position +=1;
        fb_move_cursor(position);
    }

    return len;
}
